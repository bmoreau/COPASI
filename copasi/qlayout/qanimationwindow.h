#ifndef QANIMATION_WINDOW_H
#define QANIMATION_WINDOW_H

#include <QMainWindow>

#include <UI/CWindowInterface.h>
#include <qlayout/ui_qanimationwindow.h>

class QLayoutScene;
class QCopasiAnimation;
class CCopasiDataModel;
class QCloseEvent;
class QMenu;
class CLayout;
class QAnimationWindow : public CWindowInterface, public Ui::QAnimationWindow
{
  Q_OBJECT
public:
  QAnimationWindow (CLayout* layout, CCopasiDataModel* dataModel=NULL);
  QAnimationWindow ();
  virtual ~QAnimationWindow ();
  void setScene(QLayoutScene* scene, CCopasiDataModel* dataModel);
  void setAnimation(QCopasiAnimation* animation, CCopasiDataModel* dataModel);
  virtual QMenu *getWindowMenu() const;
public slots:
  void slotShowStep(int);
  void slotExportImage();
  void slotEditSettings();
  void slotSwitchAnimation();
  void slotRandomizeLayout();
  void slotAutoLayout();
private: 
  void init();
protected:
  virtual void closeEvent(QCloseEvent *closeEvent);

  QLayoutScene* mpScene;
  CCopasiDataModel* mpModel;
  QMenu* mpWindowMenu;
  QCopasiAnimation* mAnimation;
  bool mStopLayout;
};

#endif // QANIMATION_WINDOW_H