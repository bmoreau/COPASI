/****************************************************************************
 ** Form implementation generated from reading ui file '.\ScanItemWidget.ui'
 **
 ** Created: Thu May 22 10:43:21 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "ScanItemWidget.h"
#include "ScanWidget.h"
#include <qvariant.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "utilities/CMethodParameterList.h" 
/*
 *  Constructs a ScanItemWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanItemWidget::ScanItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("ScanItemWidget");
  ScanItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanItemWidgetLayout");

  layout18 = new QVBoxLayout(0, 0, 6, "layout18");

  layout15 = new QHBoxLayout(0, 0, 6, "layout15");

  TextLabel1 = new QLabel(this, "TextLabel1");
  layout15->addWidget(TextLabel1);
  QSpacerItem* spacer = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout15->addItem(spacer);

  mMin = new ScanLineEdit(this, "mMin");
  mMin->setFrameShape(ScanLineEdit::LineEditPanel);
  mMin->setFrameShadow(ScanLineEdit::Sunken);
  layout15->addWidget(mMin);
  layout18->addLayout(layout15);

  layout16 = new QHBoxLayout(0, 0, 6, "layout16");

  TextLabel2 = new QLabel(this, "TextLabel2");
  layout16->addWidget(TextLabel2);
  QSpacerItem* spacer_2 = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout16->addItem(spacer_2);

  mMax = new ScanLineEdit(this, "mMax");
  layout16->addWidget(mMax);
  layout18->addLayout(layout16);

  layout17 = new QHBoxLayout(0, 0, 6, "layout17");

  TextLabel3 = new QLabel(this, "TextLabel3");
  layout17->addWidget(TextLabel3);
  QSpacerItem* spacer_3 = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout17->addItem(spacer_3);

  mDensity = new ScanLineEdit(this, "mDensity");
  mDensity->setFrameShape(ScanLineEdit::LineEditPanel);
  mDensity->setFrameShadow(ScanLineEdit::Sunken);
  layout17->addWidget(mDensity);
  layout18->addLayout(layout17);

  ScanItemWidgetLayout->addLayout(layout18, 0, 0);

  layout21 = new QVBoxLayout(0, 0, 6, "layout21");

  mLogarithmic = new ScanCheckBox(this, "bLogarithmic");
  layout21->addWidget(mLogarithmic);

  mIndependent = new ScanCheckBox(this, "mIndependent");
  layout21->addWidget(mIndependent);

  ScanItemWidgetLayout->addLayout(layout21, 1, 0);

  buttonGroup = new QButtonGroup(this, "buttonGroup");
  buttonGroup->setFrameShape(QButtonGroup::GroupBoxPanel);
  buttonGroup->setFrameShadow(QButtonGroup::Sunken);
  buttonGroup->setLineWidth(2);
  buttonGroup->setExclusive(TRUE);
  buttonGroup->setColumnLayout(0, Qt::Vertical);
  buttonGroup->layout()->setSpacing(6);
  buttonGroup->layout()->setMargin(11);
  buttonGroupLayout = new QGridLayout(buttonGroup->layout());
  buttonGroupLayout->setAlignment(Qt::AlignTop);

  layout19 = new QVBoxLayout(0, 0, 6, "layout19");

  mRegularGridRadio = new ScanRadioButton(buttonGroup, "mRegularGridRadio");
  layout19->addWidget(mRegularGridRadio);

  randomeLabel = new QLabel(buttonGroup, "randomeLabel");
  randomeLabel->setFrameShadow(QLabel::Sunken);
  layout19->addWidget(randomeLabel);

  buttonGroupLayout->addMultiCellLayout(layout19, 0, 0, 0, 1);

  layout20 = new QVBoxLayout(0, 0, 6, "layout20");

  mUniformRadio = new ScanRadioButton(buttonGroup, "mUniformRadio");
  layout20->addWidget(mUniformRadio);

  mGaussianRadio = new ScanRadioButton(buttonGroup, "mNormalRadio");
  layout20->addWidget(mGaussianRadio);

  mPosGaussianRadio = new ScanRadioButton(buttonGroup, "mPosGaussianRadio");
  layout20->addWidget(mPosGaussianRadio);

  buttonGroupLayout->addLayout(layout20, 1, 1);
  QSpacerItem* spacer_4 = new QSpacerItem(20, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);
  buttonGroupLayout->addItem(spacer_4, 1, 0);

  ScanItemWidgetLayout->addMultiCellWidget(buttonGroup, 0, 1, 1, 1);
  languageChange();
  resize(QSize(320, 162).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(mMin, mMax);
  setTabOrder(mMax, mDensity);
  setTabOrder(mDensity, mIndependent);
  setTabOrder(mIndependent, mLogarithmic);
  setTabOrder(mLogarithmic, mRegularGridRadio);
  setTabOrder(mRegularGridRadio, mUniformRadio);
  setTabOrder(mUniformRadio, mGaussianRadio);
  setTabOrder(mGaussianRadio, mPosGaussianRadio);

  pParameter = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScanItemWidget::~ScanItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void ScanItemWidget::ResetData()
{
  // clear the values of the variables
  mMax->setText("2.0");
  mMin->setText("1.0");
  mDensity->setText("2");
  mLogarithmic->setChecked(FALSE);
  mIndependent->setChecked(TRUE);
  mRegularGridRadio->setChecked(1);
  mGaussianRadio->setChecked(0);
  mUniformRadio->setChecked(0);
  mPosGaussianRadio->setChecked(0);
}

void ScanItemWidget::InitializeParameterList()
{
  //name value type
  pParameter->add("max", mMax->text().toDouble(), CParameter::DOUBLE);
  /*
    pParameter("min", mMin->setText("1.0");
    pParameter("incr", mDensity->setText("2");
    pParameter("log", mLogarithmic->setChecked(FALSE);
    pParameter("Indp", mIndependent->setChecked(TRUE);
    pParameter("gridType", 
    pParameter("value", 0, 
    pParameter(mRegularGridRadio->setChecked(1);
    pParameter(mGaussianRadio->setChecked(0);
    pParameter(mUniformRadio->setChecked(0);
    pParameter(mPosGaussianRadio->setChecked(0);
   
   ->add();
  */
}

void ScanItemWidget::loadObject()
{
  if (!pParameter)
    return;
  ResetData();
  InitializeParameterList();

  int i = 0;
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScanItemWidget::languageChange()
{
  setCaption(tr("ScanItemWidget"));
  TextLabel3->setText(tr("Density"));
  TextLabel2->setText(tr("Max"));
  TextLabel1->setText(tr("Min"));
  mDensity->setText(QString::null);
  mIndependent->setText(tr("          Master"));
  mLogarithmic->setText(tr("          Logarithmic"));
  buttonGroup->setTitle(QString::null);
  mGaussianRadio->setText(tr("Normal"));
  mUniformRadio->setText(tr("Uniform"));
  mPosGaussianRadio->setText(tr("Pos. Normal"));
  mRegularGridRadio->setText(tr("Regular Grid"));
  randomeLabel->setText(tr("Random"));
}
