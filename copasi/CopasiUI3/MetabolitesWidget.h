#ifndef METABOLITES_WIDGET_H
#define METABOLITES_WIDGET_H

#include <qtable.h>
#include "Model/CModel.h"

class MetabolitesWidget : public QWidget
{
protected:
	QTable *table;
	CModel *mModel;
	

public:
	MetabolitesWidget(CModel *model, QWidget *parent, const char * name=0, WFlags f=0);

};

#endif