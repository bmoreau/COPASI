/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/19 20:11:45 $
   End CVS Header */

#include "copasi.h"
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"
#include "CCopasiContainer.h"

const std::vector< CCopasiContainer * > CReport::EmptyList;

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport(const CCopasiContainer * pParent):
    CCopasiObject("Report", pParent, "Report"),
    mpOstream(NULL),
    mStreamOwner(false),
    mpReportDef(NULL),
    mTarget(""),
    mAppend(true)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::CReport(const CReport & src,
                 const CCopasiContainer * pParent):
    CCopasiObject("Report", pParent, "Report"),
    mpOstream(src.mpOstream),
    mStreamOwner(false),
    mpReportDef(src.mpReportDef),
    mTarget(src.mTarget),
    mAppend(src.mAppend)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  headerObjectList.clear();
  bodyObjectList.clear();
  footerObjectList.clear();

  if (mStreamOwner) pdelete(mpOstream);

  mpOstream = NULL;
  mStreamOwner = false;

  //  CKeyFactory::remove(mKey);
  // mpReportDef pointer shall be dealt outside, where it is created
  //  pdelete(mpReportDef);
}

CReportDefinition* CReport::getReportDefinition()
{return mpReportDef;}

void CReport::setReportDefinition(CReportDefinition* reportDef)
{mpReportDef = reportDef;}

const std::string& CReport::getTarget()
{return mTarget;}

void CReport::setTarget(std::string target)
{mTarget = target;}

bool CReport::append()
{return mAppend;}

void CReport::setAppend(bool append)
{mAppend = append;}

void CReport::printHeader()
{
  // check if there is a target defined,
  if (!mpOstream)
    return;
  // for loop print out mpReportDef->getHeader()
  unsigned C_INT32 i;
  for (i = 0; i < headerObjectList.size(); i++)
    headerObjectList[i]->print(mpOstream);
}

void CReport::printBody()
{
  // check if there is a target defined,
  if (!mpOstream)
    return;
  // for loop print out mpReportDef->getBody()
  unsigned C_INT32 i;
  for (i = 0; i < bodyObjectList.size(); i++)
    bodyObjectList[i]->print(mpOstream);
}

void CReport::printFooter()
{
  // check if there is a target defined,
  if (!mpOstream)
    return;
  // for loop print out mpReportDef->getFooter()
  unsigned C_INT32 i;
  for (i = 0; i < footerObjectList.size(); i++)
    footerObjectList[i]->print(mpOstream);
}

// Compile the List of Report Objects;
// Support Parellel

bool CReport::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  headerObjectList.clear();
  bodyObjectList.clear();
  footerObjectList.clear();

  // check if there is a Report Definition Defined
  if (!mpReportDef) return false;

  generateObjectsFromName(&listOfContainer, headerObjectList,
                          mpReportDef->getHeaderAddr());
  generateObjectsFromName(&listOfContainer, bodyObjectList,
                          mpReportDef->getBodyAddr());
  generateObjectsFromName(&listOfContainer, footerObjectList,
                          mpReportDef->getFooterAddr());

  return true;
}

std::ostream * CReport::open(std::ostream * pOstream)
{
  if (mStreamOwner) pdelete(mpOstream);

  if (pOstream)
    {
      mpOstream = pOstream;
      mStreamOwner = false;
    }
  else if (mTarget != "")
    {
      mpOstream = new std::ofstream;
      mStreamOwner = true;

      if (mAppend)
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out | std::ios_base::app);
      else
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out);

      if (((std::ofstream *) mpOstream)->is_open()) pdelete(mpOstream);
    }

  return mpOstream;
}

std::ostream * CReport::getStream() const {return mpOstream;}

void CReport::printBody(CReport * pReport)
{
  if (pReport)
    pReport->printBody();
}

// make to support parallel tasks
void CReport::generateObjectsFromName(const std::vector< CCopasiContainer * > * pListOfContainer,
                                      std::vector<CCopasiObject*> & objectList,
                                      std::vector<CCopasiObjectName>* nameVector)
{
  unsigned C_INT32 i;
  CCopasiObject* pSelected;

  // if no specified container list
  if (!pListOfContainer)
    for (i = 0; i < nameVector->size(); i++)
      {
        pSelected = NULL;
        pSelected =
          (CCopasiObject*)CCopasiContainer::Root->getObject((*(nameVector))[i]);
        if (pSelected)
          objectList.push_back(pSelected);
      }
  else
    {
      CCopasiContainer* pCopasiObject;
      unsigned C_INT32 containerIndex;
      for (i = 0; i < nameVector->size(); i++)
        {
          //favor to search the list of container first
          pSelected = NULL;
          for (containerIndex = 0; containerIndex < pListOfContainer->size(); containerIndex++)
            {
              pCopasiObject = (*pListOfContainer)[containerIndex];
              pSelected =
                (CCopasiObject*)pCopasiObject->getObject((*(nameVector))[i]);
              if (pSelected)
                {
                  objectList.push_back(pSelected);
                  break;
                }
            }
          // if not find search the root
          if (!pSelected)
            {
              pSelected =
                (CCopasiObject*)CCopasiContainer::Root->getObject((*(nameVector))[i]);
              // has been deleted all where
              if (pSelected)
                objectList.push_back(pSelected);
            }
        }
    }
}
