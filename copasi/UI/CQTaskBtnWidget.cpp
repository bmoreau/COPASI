// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:56 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTaskBtnWidget.h"

CQTaskBtnWidget::CQTaskBtnWidget(QWidget* parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
  setupUi(this);
}

CQTaskBtnWidget::~CQTaskBtnWidget()
{
  // TODO Auto-generated destructor stub
}

void CQTaskBtnWidget::languageChange()
{
  retranslateUi(this);
}

