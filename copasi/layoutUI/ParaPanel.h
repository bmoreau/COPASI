// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/06/04 13:28:16 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'ParaPanel.ui'
 **
 ** Created: Mo Jun 4 10:59:30 2007
 **      by: The User Interface Compiler ($Id: ParaPanel.h,v 1.1 2007/06/04 13:28:16 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef PARAPANEL_H
#define PARAPANEL_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QSpinBox;
class QButtonGroup;
class QRadioButton;
class QSlider;

class ParaPanel : public QWidget
  {
    Q_OBJECT

  public:
    ParaPanel(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParaPanel();

    QLabel* paraLabel;
    QLabel* frameRateLabel;
    QSpinBox* spinBox1;
    QLabel* schedModeLabel;
    QButtonGroup* scalingButtonGroup;
    QRadioButton* individScalButton;
    QRadioButton* globalScalButton;
    QLabel* animModeLabel;
    QSlider* stepSlider;

  public slots:
    virtual void stepSlider_valueChanged(int);

  protected:
    QVBoxLayout* ParaPanelLayout;
    QHBoxLayout* layout1;
    QHBoxLayout* layout3;
    QVBoxLayout* layout2;

  protected slots:
    virtual void languageChange();
  };

#endif // PARAPANEL_H
