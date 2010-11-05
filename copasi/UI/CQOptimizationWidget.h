// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
//   $Revision: 1.20.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/11/05 12:24:33 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

#include "ui_CQOptimizationWidget.h"

class CQFittingItemWidget;

#include <QVBoxLayout>
#include <QHBoxLayout>

class CQOptimizationWidget : public TaskWidget, public Ui::CQOptimizationWidget
{
  Q_OBJECT

public:
  CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
  ~CQOptimizationWidget();

  virtual bool runTask();
  bool isSteadyState();

public slots:
  void slotParameterNumberChanged(int number);
  void slotConstraintNumberChanged(int number);
  virtual void slotEditExpression();

protected:
  CQFittingItemWidget * mpCurrentList;
  QColor mChangedColor;
  QColor mSavedColor;
  bool mTypeChanged;

  std::map< std::string, C_INT32 > mSubtaskMap;

  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();

  void slotPageChange(QWidget * currentPage);
  void slotExpressionValid(bool valid);
  void slotSubtaskChanged(const QString & subtask);

private:
  void init();
  void destroy();
};

#endif // CQOPTIMIZATIONWIDGET_H
