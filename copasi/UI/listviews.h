/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.h,v $
   $Revision: 1.80 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/20 07:40:15 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <set>
#include <qsplitter.h>
#include <qlistview.h>

#include "copasi.h"
#include "Tree.h"

class DataModelGUI;

//class CSteadyStateTask;
//class CTrajectoryTask;

class CompartmentSymbols;
class CompartmentsWidget1;
class CompartmentsWidget;
class ConstantSymbols;
class DifferentialEquations;
class FixedMetaboliteSymbols;
class FunctionSymbols;
class FunctionWidget1;
class FunctionWidget;
class CMathModel;
class MetaboliteSymbols;
class MetabolitesWidget1;
class MetabolitesWidget;
class ModesWidget;
class ModelWidget;
class MoietyWidget1;
class MoietyWidget;
class ReactionsWidget1;
class ReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class TrajectoryWidget;
class TableDefinition;
class TableDefinition1;
class OptimizationWidget;
class CopasiWidget;
class PlotWidget1;
class PlotWidget;
class CopasiDefaultWidget;

//*********************************************************************************

class FolderListItem : public QListViewItem
  {
  public:
    FolderListItem(QListView *parent, const IndexedNode *f, bool recurs = true);
    FolderListItem(FolderListItem *parent, const IndexedNode *f, bool recurs = true);
    void createSubFolders();
    void deleteSubFolders();

    const IndexedNode *folder() const;
    QString key(int, bool) const;

  protected:
    const IndexedNode *mpFolder;
  };

//********************************************************************************

class ListViews : public QSplitter
  {
    Q_OBJECT
  public:
    ListViews(QWidget *parent = 0, const char *name = 0);
    ~ListViews();

    // CHANGE does not include RENAME
    enum Action {CHANGE = 0, ADD, DELETE, RENAME};
    enum ObjectType {METABOLITE = 0, COMPARTMENT, REACTION, FUNCTION, MODEL, STATE, REPORT, PLOT};

    void setDataModel(DataModelGUI* dm);
    static DataModelGUI* getDataModel() {return dataModel;};
    static bool notify(ObjectType objectType, Action action, const std::string & key = "");
    static bool commit();
    void switchToOtherWidget(C_INT32 id, const std::string & key);

  private:
    CMathModel *mpMathModel;

    CopasiWidget* findWidgetFromItem(FolderListItem* item) const;

    void ConstructNodeWidgets();
    void setupFolders();

    void setTheRightPixmap(QListViewItem* lvi);

    FolderListItem* findListViewItem(int id, std::string key); //should always return a valid item

  private slots:
    void slotFolderChanged(QListViewItem*);

  private:
    static DataModelGUI* dataModel;
    QListViewItem* lastSelection;
    CopasiWidget* currentWidget;
    std::string lastKey;

    static std::set<ListViews *> mListOfListViews;
    bool attach();
    bool detach();

    bool updateCurrentWidget(ObjectType objectType, Action action, const std::string & key = "");
    static bool updateDataModelAndListviews(ObjectType objectType, Action action, const std::string & key);
    static bool updateAllListviews(C_INT32 id);

    //the widgets
    QListView *folders;

    ScanWidget *scanWidget;
    SteadyStateWidget *steadystateWidget;
    TrajectoryWidget *trajectoryWidget;
    MetabolitesWidget *metabolitesWidget;
    ReactionsWidget *reactionsWidget;
    CompartmentsWidget *compartmentsWidget;
    CompartmentSymbols *compartmentSymbols;
    MoietyWidget *moietyWidget;
    FunctionWidget *functionWidget;
    FunctionSymbols *functionSymbols;
    DifferentialEquations *differentialEquations;
    ReactionsWidget1 *reactionsWidget1;
    MetabolitesWidget1 *metabolitesWidget1;
    MetaboliteSymbols *metaboliteSymbols;
    FixedMetaboliteSymbols *fixedMetaboliteSymbols;
    CompartmentsWidget1 *compartmentsWidget1;
    ConstantSymbols *constantSymbols;
    MoietyWidget1 *moietyWidget1;
    FunctionWidget1 *functionWidget1;
    ModesWidget *modesWidget;
    ModelWidget *modelWidget;
    TableDefinition *tableDefinition;
    TableDefinition1 *tableDefinition1;
    OptimizationWidget *optimizationWidget;
    PlotWidget1 *plotWidget1;
    PlotWidget *plotWidget;
    CopasiDefaultWidget *defaultWidget;
  };

#endif
