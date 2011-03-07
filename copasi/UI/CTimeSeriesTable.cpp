// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTimeSeriesTable.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:57 $
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

#include "CTimeSeriesTable.h"
#include "qtUtilities.h"

CTimeSeriesTable::CTimeSeriesTable(QWidget* p, const char * name):
    Q3Table(3, 3, p, name),
    mpTS(NULL),
    mFlagConc(true)
{
  setLeftMargin(0);
  mItem = new Q3TableItem(this, Q3TableItem::Never);
}

CTimeSeriesTable::~CTimeSeriesTable()
{
  pdelete(mpTS)
}

void CTimeSeriesTable::setTimeSeries(const CTimeSeries & TS)
{
  pdelete(mpTS);
  mpTS = new CTimeSeries(TS);

  if (mpTS != NULL)
    {
      setNumRows((int) mpTS->getRecordedSteps());
      setNumCols((int) mpTS->getNumVariables());

      Q3Header *tableHeader = horizontalHeader();
      size_t i, imax = mpTS->getNumVariables();

      for (i = 0; i < imax; ++i)
        tableHeader->setLabel((int) i, FROM_UTF8(mpTS->getTitle(i)));
    }
  else
    {
      setNumRows(0);
      setNumCols(0);
    }
}

QString CTimeSeriesTable::textForCell(unsigned int row, unsigned int col)
{
  if (mpTS == NULL) return "";

  if (row > mpTS->getRecordedSteps()) return "";

  if (col > mpTS->getNumVariables()) return "";

  if (mFlagConc)
    return QString::number(mpTS->getConcentrationData(row, col));
  else
    return QString::number(mpTS->getData(row, col));
}

void CTimeSeriesTable::showConcentrations(bool conc)
{
  mFlagConc = conc;
  hide(); show(); //TODO: ugly!
}

const CTimeSeries* CTimeSeriesTable::getTimeSeries()
{
  return mpTS;
}

bool CTimeSeriesTable::doShowConcentrations() const
{
  return this->mFlagConc;
}
