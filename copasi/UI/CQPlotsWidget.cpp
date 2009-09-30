// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPlotsWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/08/10 15:15:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>
#include <QClipboard>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"

#include "CQPlotsWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

/*
 *  Constructs a CQPlotsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQPlotsWidget::CQPlotsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpPlotDM = new CQPlotDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(COL_NAME_PLOTS);

  mpTblPlots->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblPlots->verticalHeader()->hide();
  mpTblPlots->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  setFramework(mFramework);

  // Connect the table widget
  connect(mpPlotDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpPlotDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPlotsWidget::~CQPlotsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpPlotDM);
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQPlotsWidget::languageChange()
{
  retranslateUi(this);
}

void CQPlotsWidget::slotBtnDeleteClicked()
{
  if (mpTblPlots->hasFocus())
    {deleteSelectedPlots();}
}

void CQPlotsWidget::deleteSelectedPlots()
{
  QModelIndexList selRows = mpTblPlots->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpProxyModel->mapToSource(*i));}

  mpPlotDM->removeRows(mappedSelRows);
}

void CQPlotsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Plots?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpPlotDM->clear();
    }
}

bool CQPlotsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  enterProtected();
  return true;
}

bool CQPlotsWidget::leave()
{
  return true;
}

bool CQPlotsWidget::enterProtected()
{
  mpProxyModel->setSourceModel(mpPlotDM);
  //Set Model for the TableView
  mpTblPlots->setModel(NULL);
  mpTblPlots->setModel(mpProxyModel);
  mpTblPlots->resizeColumnsToContents();
  setFramework(mFramework);

  return true;
}

void CQPlotsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblPlots->resizeColumnsToContents();
  setFramework(mFramework);
}

void CQPlotsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpPlotDM->isDefaultRow(index))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (!pDataModel->getModel())
    return;

  CPlotSpecification *pPS = static_cast<CPlotSpecification *>(pDataModel->getPlotDefinitionList()->operator[](index.row()));
  const std::string key = static_cast<CCopasiParameter *>(pPS)->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQPlotsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && ev->modifiers() & Qt::ControlModifier)
    {
      QModelIndexList selRows = mpTblPlots->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpPlotDM->columnCount(); ++x)
            {
              if (!mpTblPlots->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpPlotDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQPlotsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|No Name", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

void CQPlotsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}