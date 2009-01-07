// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.cpp,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 19:43:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <q3table.h>
#include <qlabel.h>

#ifdef SunOS
#include <ieeefp.h>
#else
#include <math.h>
#endif

#include "copasi.h"

#include "CQArrayAnnotationsWidget.h"
#include "qtUtilities.h"

#include "parametertable.h" //for color table item
#include <iostream>

#include "copasi/UI/CQBarChart.h"
//#include "copasi/mathematics.h"

CQArrayAnnotationsWidget::CQArrayAnnotationsWidget(QWidget* parent, const char* name, Qt::WFlags fl,
    bool barChart, bool slider)
    : Q3VBox(parent, name, fl),
    mpPlot3d(NULL),
    mpColorScale(NULL)
{
  mWithBarChart = barChart;
  mUseSliders = slider;
  mBarChartFilled = false;

  mpHBoxSelection = new Q3HBox(this);
  mpHBoxSelection->setSpacing(4);
  mpHBoxSelection->setMargin(4);

  mpSelectionTable = new Q3Table(mpHBoxSelection);
  mpSelectionTable->verticalHeader()->hide();
  mpSelectionTable->setLeftMargin(0);
  mpSelectionTable->horizontalHeader()->hide();
  mpSelectionTable->setTopMargin(0);
  mpSelectionTable->setNumCols(2);
  mpSelectionTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  mpSelectionTable->setColumnMovingEnabled(false);
  mpSelectionTable->setRowMovingEnabled(false);
  mpSelectionTable->verticalHeader()->setResizeEnabled(false);

  mpButton = new QPushButton(mpHBoxSelection);
  mpButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mpButton->setText("Bars");

  mpHBoxSelection->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  mpHBoxContents = new Q3HBox(this);
  mpStack = new Q3WidgetStack(mpHBoxContents);
  mpContentTable = new Q3Table(mpStack);
  mpContentTable->setReadOnly(true);
  mpContentTable->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  mpStack->addWidget(mpContentTable, 0);

  mpContentTable->setColumnMovingEnabled(false);
  mpContentTable->setRowMovingEnabled(false);
  mpContentTable->horizontalHeader()->setTracking(true);
  mpContentTable->verticalHeader()->setResizeEnabled(false);

  //   if (showBarChart)
  //     {
  //       mpPlot3d = new CQBarChart(mpStack);
  //       mpPlot3d->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  //       if (slider) mpPlot3d->activateSlider();
  //       mpStack->addWidget(mpPlot3d, 1);
  //       if (barChartFirst)
  //         {
  //           setFocusOnBars();
  //           mpStack->raiseWidget(1);
  //           mpButton->setText("table");
  //}
  //       else
  //         mpButton->setText("bars");
  //}

  connect(mpContentTable, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(tableDoubleClicked()));
  connect(mpButton, SIGNAL(clicked()), this, SLOT(changeContents()));
  connect(mpSelectionTable, SIGNAL(valueChanged(int, int)),
          this, SLOT(selectionTableChanged(int, int)));
  connect(mpContentTable->horizontalHeader(), SIGNAL(sizeChange(int, int, int)), this, SLOT(setColumnSize(int, int, int)));
}

CQArrayAnnotationsWidget::~CQArrayAnnotationsWidget()
{
  if (mpColorScale)
    delete mpColorScale;
}

void CQArrayAnnotationsWidget::setColorCoding(CColorScale * cs)
{
  if (cs && cs->isUsed())
    {
      cs = NULL; //don´t accept a scaler that is already used
      // std::cout << "tried to use a color scale several times!" << std::endl;
    }
  if (mpColorScale)
    delete mpColorScale;
  mpColorScale = cs;
  if (cs) cs->setIsUsed(true);
}

void CQArrayAnnotationsWidget::setArrayAnnotation(const CArrayAnnotation * pArray)
{
  mpArray = pArray;

  if (!mpArray)
    {
      clearWidget();
      return;
    }

  //std::cout << *mpArray;

  CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());

  if (mpArray->dimensionality() == 0)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      fillTable();
    }
  else if (mpArray->dimensionality() == 1)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      mpSelectionTable->setNumRows(1);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->adjustColumn(0);
      mpSelectionTable->adjustColumn(1);

      fillTable(0, index);
    }
  else if (mpArray->dimensionality() == 2)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      mpSelectionTable->setNumRows(2);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->setText(1, 0, "Columns: ");
      mpSelectionTable->setText(1, 1, FROM_UTF8(mpArray->getDimensionDescription(1)));
      mpSelectionTable->adjustColumn(0);
      mpSelectionTable->adjustColumn(1);

      fillTable(0, 1, index);
    }
  else
    {
      initSelectionTable();
      fillTable(0, 1, index);
    }
}

void CQArrayAnnotationsWidget::initSelectionTable()
{
  mpSelectionTable->setReadOnly(false);
  mpSelectionTable->setColumnReadOnly(0, true);
  mpSelectionTable->setColumnReadOnly(1, false);

  C_INT32 i, imax = mpArray->dimensionality();
  mpSelectionTable->setNumRows(0);
  mpSelectionTable->setNumRows(imax);

  for (i = 0; i < imax; ++i)
    {
      mpSelectionTable->setText(i, 0, FROM_UTF8(mpArray->getDimensionDescription(i)));

      //combo box
      QStringList combolist;
      vectorOfStrings2QStringList(mpArray->getAnnotationsString(i), combolist);
      combolist.prepend("In columns");
      combolist.prepend("In rows");

      mpSelectionTable->setItem(i, 1, new Q3ComboTableItem(mpSelectionTable, combolist));
      //mpSelectionTable->adjustRow(i);

      //set first combobox to "In rows", second to "In columns" and all other to the
      //first object in the annotations list
      if (i < 2)
        setCurrentItem(i, i);
      else
        setCurrentItem(i, 2);
    }

  mpSelectionTable->adjustColumn(0);
  //mpSelectionTable->adjustColumn(1);

  //store the active item of all combo boxes
  storeCurrentCombos();
}

void CQArrayAnnotationsWidget::storeCurrentCombos()
{
  C_INT32 i, imax = mpArray->dimensionality();
  combos.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      C_INT32 tmp = currentItem(i);
      if (tmp >= 2)
        combos[i] = 2;
      else
        combos[i] = tmp;
    }
}

void CQArrayAnnotationsWidget::clearWidget()
{
  //mpSelectionTable->setNumCols(2);
  mpSelectionTable->setNumRows(0);
  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);

  if (mWithBarChart && mBarChartFilled)
    {
      if (mpPlot3d)
        mpPlot3d->emptyPlot();
      mBarChartFilled = false;
    }
}

void CQArrayAnnotationsWidget::setLegendEnabled(bool b)
{
  if (b)
    mpSelectionTable->show();
  else
    mpSelectionTable->hide();
}

C_INT32 CQArrayAnnotationsWidget::currentItem(C_INT32 row)
{
  Q3ComboTableItem * item = dynamic_cast<Q3ComboTableItem*>
                            (mpSelectionTable->item(row, 1));

  if (!item) return - 1;

  return item->currentItem();
}

void CQArrayAnnotationsWidget::setCurrentItem(C_INT32 row, C_INT32 index)
{
  storeCurrentCombos();
  Q3ComboTableItem * item = dynamic_cast<Q3ComboTableItem*>
                            (mpSelectionTable->item(row, 1));

  if (!item) return;

  item->setCurrentItem(index);
}

//slot
void CQArrayAnnotationsWidget::selectionTableChanged(int row, int col)
{
  if (col != 1) return;

  C_INT32 newValue = currentItem(row);

  //no combobox
  if (-1 == newValue) goto finish;

  //no change
  if (newValue == combos[row]) goto finish;

  //neither "row" nor "column"
  if ((newValue >= 2) && (combos[row] >= 2)) goto finish;

  if (newValue == 0) //new value is "row"
    {
      //find out which line was "row" before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] == 0)
          setCurrentItem(i, combos[row]);
    }

  if (newValue == 1) //new value is "column"
    {
      //find out which line was "col" before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] == 1)
          setCurrentItem(i, combos[row]);
    }

  if (newValue >= 2) //new value is neither "col" nor "row"
    {
      //find a line which was neither "col" nor "row"  before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] >= 2)
          {
            setCurrentItem(i, combos[row]);
            break;
          }
    }

finish:
  //call fillTable()
  {
    CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());
    C_INT32 rowindex = 0, colindex = 0;
    C_INT32 i, imax = mpArray->dimensionality();
    for (i = 0; i < imax; ++i)
      {
        C_INT32 tmp = currentItem(i);

        //set index
        if (tmp < 2)  //row or column
          index[i] = 0;
        else
          index[i] = tmp - 2;

        //set rowindex
        if (0 == tmp)
          rowindex = i;

        //set colindex
        if (1 == tmp)
          colindex = i;
      }

    fillTable(rowindex, colindex, index);
  }

  storeCurrentCombos();
}

void CQArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
    CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  mpContentTable->setNumCols(mpArray->size()[colIndex]);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(rowIndex);
  std::vector<std::string> coldescr = mpArray->getAnnotationsString(colIndex);

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];
  unsigned C_INT32 j, jmax = mpArray->size()[colIndex];

  //annotations
  for (i = 0; i < imax; ++i)
    {
      mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
    }

  for (j = 0; j < jmax; ++j)
    {
      // :TODO: This is a hack we need a smarter way possibly using getObjctDisplayName.
      mpContentTable->horizontalHeader()->setLabel(j, FROM_UTF8(coldescr[j]).replace("; {", "\n{"));
    }

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            index[rowIndex] = i;
            index[colIndex] = j;
            mpColorScale->passValue((*mpArray->array())[index]);
          }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        index[rowIndex] = i;
        index[colIndex] = j;

        if (!mpColorScale)
          {
            mpContentTable->setText(i, j, QString::number((*mpArray->array())[index]));
          }
        else
          {
            C_FLOAT64 number = (*mpArray->array())[index];
            QColor color = mpColorScale->getColor(number);
            mpContentTable->setItem(i, j, new ColorTableItem(mpContentTable, Q3TableItem::Never, color,
                                    QString::number(number)));
          }
      }

  mRowIndex = rowIndex;
  mColIndex = colIndex;
  mIndex = index;

  mOneDimensional = false;
  if (mpStack->id(mpStack->visibleWidget()) == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex,
    CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());

  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  mpContentTable->horizontalHeader()->setLabel(0, "");

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        {
          index[rowIndex] = i;
          mpColorScale->passValue((*mpArray->array())[index]);
        }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents and annotations
  const std::vector<std::string> & rowdescr = mpArray->getAnnotationsString(rowIndex);
  for (i = 0; i < imax; ++i)
    {
      index[rowIndex] = i;
      mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
      if (!mpColorScale)
        {
          mpContentTable->setText(i, 0, QString::number((*mpArray->array())[index]));
        }
      else
        {
          C_FLOAT64 number = (*mpArray->array())[index];
          QColor color = mpColorScale->getColor(number);
          mpContentTable->setItem(i, 0, new ColorTableItem(mpContentTable, Q3TableItem::Never, color,
                                  QString::number(number)));
        }
    }

  mRowIndex = rowIndex;
  mColIndex = 1;
  mIndex = index;

  mOneDimensional = true;

  if (mpStack->id(mpStack->visibleWidget()) == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable()
{
  if (!mpArray) return;

  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);
  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(1);

  mpContentTable->horizontalHeader()->setLabel(0, "");
  mpContentTable->verticalHeader()->setLabel(0, "");

  CCopasiAbstractArray::index_type index; index.resize(0);
  //mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
  mpContentTable->setText(0, 0, QString::number((*mpArray->array())[index]));
}

void CQArrayAnnotationsWidget::changeContents()
{

  if (mpStack->id(mpStack->visibleWidget()) == 0)
    switchToBarChart();
  else
    switchToTable();
}

void CQArrayAnnotationsWidget:: enableBarChart(bool enable)
{
  if (mWithBarChart)
    {
      if (enable)
        {
          mpButton->setEnabled(true);
        }
      else
        {
          if (mpStack->id(mpStack->visibleWidget()) == 1)
            switchToTable();
          //mpStack->raiseWidget(0);
          mpButton->setEnabled(false);
        }
    }
}

void CQArrayAnnotationsWidget::switchToTable()
{
  mpStack->raiseWidget(0);
  if (mWithBarChart)
    {
      mpButton->setText("Bars");
      setFocusOnTable();
    }
}

void CQArrayAnnotationsWidget::switchToBarChart()
{

  if (mWithBarChart)
    {
      if (!mpPlot3d)
        createBarChart();

      setFocusOnBars();

      if (!mBarChartFilled)
        fillBarChart();

      mpStack->raiseWidget(1);
      mpButton->setText("Table");
    }
}

void CQArrayAnnotationsWidget::disableBarChart()
{
  switchToTable();
  mpButton->hide();
}

void CQArrayAnnotationsWidget::disableSlider()
{
  if (mpPlot3d && mpPlot3d->sliderActive())
    {
      mpPlot3d->mpPlot->mpSliderColumn->hide();
      mpPlot3d->mpPlot->mpLabelColumn->clear();
      mpPlot3d->mpPlot->mpSliderRow->hide();
      mpPlot3d->mpPlot->mpLabelRow->clear();
      mpPlot3d->mpPlot->mpSlider = false;
    }
}

void CQArrayAnnotationsWidget::setFocusOnTable()
{
  if (mWithBarChart && mpPlot3d && mpPlot3d->sliderActive())
    {
      int col = mpPlot3d->mpPlot->mpSliderColumn->value();
      int row = mpPlot3d->mpPlot->mpSliderRow->value();

      mpContentTable->clearSelection(true);
      if (col < mpContentTable->numCols())
        {
          if (row < mpContentTable->numRows())
            {
              mpContentTable->setCurrentCell(row, col);
              mpContentTable->ensureCellVisible (mpContentTable->currentRow(), mpContentTable->currentColumn());
              mpContentTable->setFocus();
            }
          else
            {
              mpContentTable->selectColumn(col);
              mpContentTable->setFocus();
            }
        }
      else
        {
          if (row < mpContentTable->numRows())
            {
              mpContentTable->selectRow(row);
              mpContentTable->setFocus();
            }
          else
            {
              mpContentTable->setCurrentCell(-1, -1);
            }
        }
    }
}

void CQArrayAnnotationsWidget::setFocusOnBars()
{
  if (mWithBarChart && mpPlot3d && mpPlot3d->sliderActive())
    {
      int col = mpContentTable->currentColumn();
      int row = mpContentTable->currentRow();

      if (mpContentTable->isRowSelected (row, true))
        {
          mpPlot3d->mpPlot->sliderMoved(-1, row);
          mpPlot3d->mpPlot->mpSliderColumn->setValue(mpContentTable->numCols() + 1);
          mpPlot3d->mpPlot->mpSliderRow->setValue(row);
        }
      else
        if (mpContentTable->isColumnSelected (col, true))
          {
            mpPlot3d->mpPlot->sliderMoved(col, -1);
            mpPlot3d->mpPlot->mpSliderColumn->setValue(col);
            mpPlot3d->mpPlot->mpSliderRow->setValue(mpContentTable->numRows() + 1);
          }
        else
          {
            if (mpContentTable->currentRow() == -1 && mpContentTable->currentColumn() == -1)
              {
                mpPlot3d->mpPlot->mpSliderColumn->setValue(mpContentTable->numCols() + 1);
                mpPlot3d->mpPlot->mpSliderRow->setValue(mpContentTable->numRows() + 1);
              }
            else
              {
                mpPlot3d->mpPlot->sliderMoved(col, row);
                mpPlot3d->mpPlot->mpSliderColumn->setValue(col);
                mpPlot3d->mpPlot->mpSliderRow->setValue(row);
              }
          }
    }
}

void CQArrayAnnotationsWidget::tableDoubleClicked()
{
  if (mpPlot3d && mpPlot3d->sliderActive())
    switchToBarChart();
}

void CQArrayAnnotationsWidget::setColumnSize(int col, int /*size0*/, int /*size*/)
{
  C_INT32 i;
  C_FLOAT64 sum = 0;
  for (i = 0; i <= col; ++i)
    sum += mpContentTable->horizontalHeader()->sectionSize(i);

  C_FLOAT64 newSize = sum / (col + 1);
  if (newSize < 5) newSize = 5;

  for (i = 0; i < mpContentTable->numCols(); i++)
    mpContentTable->setColumnWidth(i, ((int)(newSize*(i + 1))) - ((int)(newSize*i)));

  //mpContentTable->horizontalHeader()->resizeSection(i, newSize);
  mpContentTable->horizontalHeader()->repaint();
  mpContentTable->update();
}

void CQArrayAnnotationsWidget::fillBarChart()
{
  if (!mWithBarChart)
    return;

  if (!mpPlot3d)
    createBarChart();

  mBarChartFilled = true;

  if (!mpArray) return;

  assert(mRowIndex < mIndex.size());
  if (!mOneDimensional)
    assert(mColIndex < mIndex.size());

  mpContentTable->setNumRows(mpArray->size()[mRowIndex]);
  if (mOneDimensional)
    mpContentTable->setNumCols(1);
  else
    mpContentTable->setNumCols(mpArray->size()[mColIndex]);

  mpContentTable->horizontalHeader()->setLabel(0, "");

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(mRowIndex);
  if (!mOneDimensional)
    std::vector<std::string> coldescr = mpArray->getAnnotationsString(mColIndex);

  unsigned C_INT32 i, imax = mpArray->size()[mRowIndex];
  unsigned C_INT32 j, jmax;
  if (mOneDimensional)
    jmax = 1;
  else
    jmax = mpArray->size()[mColIndex];

  if (jmax > 0 && imax > 0)
    {
      //create a new array data, witch holds the hole numeric data
      unsigned C_INT32 columns = jmax;
      unsigned C_INT32 rows = imax;
      data = new double * [columns];
      for (i = 0; i < columns; ++i)
        data[i] = new double[rows];

      //minValue and maxValue help to figure out the min and max value
      mIndex[mRowIndex] = 0;
      if (!mOneDimensional)
        mIndex[mColIndex] = 0;
      double maxValue = (double)(*mpArray->array())[mIndex];
      double minValue = (double)(*mpArray->array())[mIndex];

      //fill array data with values and figure out min/max value
      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            mIndex[mRowIndex] = i;
            if (!mOneDimensional)
              mIndex[mColIndex] = j;
            if (isnan((double)(*mpArray->array())[mIndex]) ||
                !finite((double)(*mpArray->array())[mIndex]))
              {
                data[j][i] = 0;
                if (0 > maxValue) maxValue = 0;
                if (0 < minValue) minValue = 0;
              }
            else
              {
                data[j][i] = (double)(*mpArray->array())[mIndex];
                if ((double)(*mpArray->array())[mIndex] > maxValue)
                  maxValue = (double)(*mpArray->array())[mIndex];
                if ((double)(*mpArray->array())[mIndex] < minValue)
                  minValue = (double)(*mpArray->array())[mIndex];
              }
          }

      //figure out the min/max print section
      double minZ, maxZ;
      if ((minValue < 0) && (maxValue < 0))
        {//(all values < 0)
          minZ = minValue;
          maxZ = 0;
        }
      else
        {
          if ((minValue > 0) && (maxValue > 0))
            {//(all values > 0)
              minZ = 0;
              maxZ = maxValue;
            }
          else
            {//(values <> 0)
              minZ = minValue;
              maxZ = maxValue;
            }
        }

      //fill vector mColor with 100 colors, evenly distributed over relevant print section
      double holeSection = maxZ - minZ;
      double step = holeSection / 99;
      for (i = 0; i < 100; i++)
        {
          mColors.push_back(i);
          mColors[i] = mpColorScale->getColor(minZ + i * step);
        }

      //deliver plot3D contents, colors and annotations
      if ((maxValue == 0) && (minValue == 0))
        {
          // enableBarChart(false);
          // mpPlot3d->emptyPlot();
        }
      else
        {
          mpPlot3d->setPlotTitle(QString(""));
          mpPlot3d->setColors(mColors, minZ, maxZ);
          mColors.erase(mColors.begin(), mColors.end());
          mpPlot3d->showColorLegend(true);

          if (mOneDimensional)
            mpPlot3d->setDescriptions(NULL, &mpArray->getAnnotationsString(mRowIndex));
          else
            mpPlot3d->setDescriptions(&mpArray->getAnnotationsString(mColIndex), &mpArray->getAnnotationsString(mRowIndex));

          mpPlot3d->setData(data, columns, rows, holeSection);
          enableBarChart(true);
        }
    }
}

void CQArrayAnnotationsWidget::createBarChart()
{
  mpPlot3d = new CQBarChart(mpStack);
  mpPlot3d->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  if (mUseSliders) mpPlot3d->activateSlider();
  mpStack->addWidget(mpPlot3d, 1);
  mpButton->setText("Bars");
  mBarChartFilled = false;
}
