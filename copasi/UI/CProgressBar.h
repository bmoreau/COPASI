// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.h,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:55 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#if !defined HANDLER_PROGRESS_BAR
#define HANDLER_PROGRESS_BAR

#include <qdatetime.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QMutex>
#include <QWaitCondition>

#include "utilities/CProcessReport.h"
#include "CQProgressDialog.h"

template < typename > class CVector;
class CQProgressItem;

/**
 *  This is used to call the progress bar code
 *  We do not want to call GUI stuff directly from the CModel.
 */
class CProgressBar : public CQProgressDialog, public CProcessReport
{
  Q_OBJECT
public:
  static CProgressBar * create(QWidget* parent = 0,
                               const char* name = 0,
                               bool modal = false,
                               Qt::WFlags fl = 0);

private:
  CProgressBar(QWidget* parent = 0,
               const char* name = 0,
               bool modal = false,
               Qt::WFlags fl = 0);

public:
  virtual ~CProgressBar();

  /**
   * Report process on item handle. If the return value is false the calling
   * process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool progressItem(const size_t & handle);

  /**
   * Check whether processing shall proceed. If the return value is false
   * the calling process must halt execution and return. This method is
   * provided so that lengthy processing without advances in any of the
   * reporting items can check whether continuation is requested.
   * @param bool continue
   */
  virtual bool proceed();

  /**
   * Reset item handle. This means that the value of the item has changed
   * but not as part of a continuous process. If you run multiple processes
   * call reset between them. If the return value is false the calling
   * process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool resetItem(const size_t & handle);

  /**
   * Indicate that all items are finished reporting. All item handles loose
   * their validity. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  virtual bool finish();

  /**
   * Indicate that item handle is finished reporting. The handle of that
   * item is no longer valid after the call. If the return value is false
   * the calling process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool finishItem(const size_t & handle);

  /**
   * Set the name of the process.
   * @param const std::string & name
   * @return success
   */
  virtual bool setName(const std::string & name);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const CCopasiParameter::Type & type
   * @param const void * pValue
   * @param const void * pEndValue = NULL
   * @return size_t handle
   */
protected:
  virtual size_t addItem(const std::string & name,
                         const CCopasiParameter::Type & type,
                         const void * pValue,
                         const void * pEndValue = NULL);


  virtual void closeEvent(QCloseEvent *e);

  bool mSlotFinished;

  QMutex mMutex;
  QWaitCondition mWaitSlot;
  QWaitCondition mWaitPause;

  size_t mLastHItem;

private:
  CVector< CQProgressItem * > mProgressItemList;

  QDateTime mNextEventProcessing;

  QWidget * mpMainWidget;

  QThread * mpMainThread;

signals:
  void signalAddItem(const int handle);
  void signalSetName(QString name);
  void signalProgressAll();
  void signalFinishItem(const int handle);

protected slots:

  virtual void slotAddItem(const int handle);

  virtual void slotSetName(QString name);

  virtual void slotProgressAll();

  virtual void slotFinishItem(const int handle);

  virtual void btnStopPressed();

  virtual void btnContinuePressed();
};

#endif
