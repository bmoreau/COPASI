/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MetabolitesWidget1.h,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/10 11:07:59 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/MetaboliteWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolite Widget, i.e the second level 
 ** of Metabolites.
 *****************************************************************************/
#ifndef METABOLITESWIDGET1_H
#define METABOLITESWIDGET1_H

#include "copasiWidget.h"

// class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
// class QButtonGroup;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
// class QRadioButton;
class QCheckBox;

class CMetab;

class MetabolitesWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    MetabolitesWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MetabolitesWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnDeleteClicked();

  protected:
    bool loadFromMetabolite(const CMetab*);
    bool saveToMetabolite();
    std::string objKey;

    //Widgets
    QGridLayout* MetabolitesWidget1Layout;
    //    QGridLayout* ButtonGroup2Layout;
    //    QGridLayout* ButtonGroup3Layout;
    QHBoxLayout* Layout7;
    QLabel* mLblName;
    QLineEdit* mEditName;
    QLabel* mLblCompartment;
    QComboBox* mComboCompartment;
    QFrame* Line1;
    QLabel* mLblInitStatus;
    QCheckBox * mCheckStatus;
    QLabel* mLblStatus;
    QLineEdit * mEditStatus;
    QFrame* Line2;
    QLabel* mLblInitConcentration;
    QLineEdit* mEditInitConcentration;
    QLabel* mLblConcentration;
    QLineEdit* mEditConcentration;
    QLabel* mLblInitNumber;
    QLineEdit* mEditInitNumber;
    QLabel* mLblNumber;
    QLineEdit* mEditNumber;
    QLabel* mLblTransitionTime;
    QLineEdit* mEditTransitionTime;
    QLabel* mLblRate;
    QLineEdit* mEditRate;
    QFrame* Line3;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QPushButton* newMetaboliteBtn;
    QPushButton* deleteMetaboliteBtn;
  };

#endif // METABOLITESWIDGET1_H
