/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.cpp,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/04 17:20:48 $
   End CVS Header */

/**
 *  CScanMethod class.
 *  This class describes the Scan method
 *
 *  Created for Copasi by Rohan Luktuke 2002
 */

#include <string>

//#define COPASI_TRACE_CONSTRUCTION
#include "mathematics.h"
#include "copasi.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "utilities/CReadConfig.h"
#include "randomGenerator/CRandom.h" 
//#include "utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "CScanTask.h"

// this will have to be defined somewhere else with the
// values of other distribution types
//#define SD_UNIFORM 0
//#define SD_GAUSS 1
//#define SD_BOLTZ 2
//#define SD_REGULAR 3

//**************** CScanItem classes ***************************

//static
CScanItem* CScanItem::createScanItemFromParameterGroup(const CCopasiParameterGroup* si)
{
  if (!si) return NULL;

  CScanProblem::Type type = *(CScanProblem::Type*)(si->getValue("Type"));

  CScanItem* tmp;

  if (type == CScanProblem::SCAN_REPEAT)
    tmp = new CScanItemRepeat(si);

  if (type == CScanProblem::SCAN_LINEAR)
    tmp = new CScanItemLinear(si);

  return tmp;
}

CScanItem::CScanItem(const CCopasiParameterGroup* si)
    : mNumSteps(0),
    mpValue(NULL),
    mStoreValue(0.0),
    mIndex(0),
    mFlagFinished(false)
{
  mNumSteps = *(unsigned C_INT32*)(si->getValue("Number of steps"));

  std::string tmpString = *(std::string*)(si->getValue("Object"));
  CCopasiObject* tmpObject = CCopasiContainer::ObjectFromName(tmpString);
  if (!tmpObject) {mpValue = NULL; return;}
  if (!tmpObject->isValueDbl()) {mpValue = NULL; return;}
  mpValue = (C_FLOAT64*)tmpObject->getReference();
}

void CScanItem::reset()
{
  mIndex = 0;
  mFlagFinished = false;
  this->step(); //purely virtual
}

//*******

CScanItemRepeat::CScanItemRepeat(const CCopasiParameterGroup* si)
    : CScanItem(si)
{}

void CScanItemRepeat::step()
{
  //do something ...

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;
  ++mIndex;

  //  std::cout << "SIRepeat " << mIndex-1<< std::endl;
}

//*******

CScanItemLinear::CScanItemLinear(const CCopasiParameterGroup* si)
    : CScanItem(si)
{
  mMin = *(C_FLOAT64*)(si->getValue("Minimum"));
  mMax = *(C_FLOAT64*)(si->getValue("Maximum"));
  mFaktor = (mMax - mMin) / mNumSteps;
}

void CScanItemLinear::step()
{
  //do something ...
  *mpValue = mMin + mIndex * mFaktor;

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;
  ++mIndex;

  //std::cout << "SILinear " << mMin + (mIndex-1)*mFaktor<< std::endl;
}

//**************** CScanMethod class ***************************

CScanMethod * CScanMethod::createMethod() {return new CScanMethod;}

CScanMethod::CScanMethod():
    CCopasiMethod(CCopasiTask::scan, CCopasiMethod::scanMethod),
    mpProblem(NULL),
    mpRandomGenerator(NULL),
    mTotalSteps(1)
    //    mVariableSize(0),
    //    mpVariables(NULL)
{
  addParameter("Random Number Generator", CCopasiParameter::STRING,
               CRandom::TypeName[1]);
  addParameter("Random Number Seed", CCopasiParameter::INT, (C_INT32) 0);
}

CScanMethod::CScanMethod(const CScanMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(NULL),
    mpRandomGenerator(NULL)
    //    mVariableSize(0),
    //    mpVariables(NULL)
{}

CScanMethod::~CScanMethod()
{
  cleanupScanItems();
}

bool CScanMethod::cleanupScanItems()
{
  if (!mpProblem) return false;
  unsigned C_INT32 i, imax = mScanItems.size();
  for (i = 0; i < imax; ++i) if (mScanItems[i]) delete mScanItems[i];

  mScanItems.resize(0);
  return true;
}

bool CScanMethod::init()
{
  if (!mpProblem) return false;

  cleanupScanItems();

  mTotalSteps = 1;

  unsigned C_INT32 i, imax = mpProblem->getNumberOfScanItems();
  for (i = 0; i < imax; ++i)
    {
      mScanItems.push_back(CScanItem::createScanItemFromParameterGroup(mpProblem->getScanItem(i)));
      mTotalSteps *= mScanItems[i]->getNumSteps();
    }

  return true;
}

bool CScanMethod::scan()
{
  if (!mpProblem) return false;

  bool success = true;

  unsigned C_INT32 i, imax = mScanItems.size();

  //store old parameter values
  for (i = 0; i < imax; ++i)
    mScanItems[i]->storeValue();

  //Do the scan...
  success = loop(0);

  //restore old parameter values
  for (i = 0; i < imax; ++i)
    mScanItems[i]->restoreValue();

  return success;
}

bool CScanMethod::loop(unsigned C_INT32 level)
{
  bool isLastMasterItem = (level == (mScanItems.size() - 1)); //TODO

  CScanItem* currentSI = mScanItems[level];

  for (currentSI->reset(); !currentSI->isFinished(); currentSI->step())
    {
      //TODO: handle slave SIs

      if (isLastMasterItem)
      {if (!calculate()) return false;}
      else
      {if (!loop(level + 1)) return false;} //TODO
    }

  return true;
}

bool CScanMethod::calculate() const
  {
    std::cout << "Scan: calculate..." << std::endl;
    return ((CScanTask*)(getObjectParent()))->processCallback();
  }

void CScanMethod::setProblem(const CScanProblem * problem)
{mpProblem = problem;}

//*************************************************

#ifdef XXXX
void CScanMethod::scan(unsigned C_INT32 s,
                       bool C_UNUSED(nl),
                       void (*pCallback)(CReport *),
                       CReport *pReport)
{
  mVariableSize = mpProblem->getVariableSize();
  mpVariables = mpProblem->getCalculateVariables();

  mpRandomGenerator =
    CRandom::createGenerator(CRandom::TypeNameToEnum(* (std::string *) getValue("Random Number Generator")),
                             * (C_INT32 *) getValue("Random Number Seed"));

  unsigned C_INT32 i, next, top;
  //1.  find the first/last master scan item

  if (s > 0)
    {
      for (i = s - 1; i > 0; i--)
        //if(scanItem[i]->Indp) break;
        //  if (scanProblem->getScanItemParameter(i, "indp")) break;

        next = i;
    }

  else
    next = 0;

  /* 2.  find the last slave item */

  //if(s<scandimension-1)
  if (s < mVariableSize - 1)
    {
      for (i = s + 1; i < mVariableSize; i++)
        //     if (scanProblem->getScanItemParameter(i, "indp")) break;
        top = i;
    }
  else
    top = mVariableSize;

  /* 3.  switch the grid type (distribution) - regular, normal etc */

  /* The "gridType" is just a temporary name for the parameter.
     A proper name will have to be given at the time of entering
     this parameter into the vector.
  */ 
  //switch(gridtype[distribution])
  switch ((int)scanProblem->getScanItemParameter(s, "gridType"))
    {
    case SD_UNIFORM:
    case SD_GAUSS:
    case SD_BOLTZ:
      // start with the min values
      setScanParameterValue(0, s, top);
      //different from SD_REGULR by initial value
      for (i = 0; i < * (unsigned C_INT32 *) scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0) scan(next, false, pCallback, pReport);
          else
            // some function
            {
              scanProblem->calculate();
              pCallback(pReport);
            }
          setScanParameterValue(i, s, top);
        }
      break;
    case SD_REGULAR:
      //start with min value - give 0 as first param in setscanparametervalue
      setScanParameterValue(0, s, top);

      for (i = 1; i <= * (unsigned C_INT32 *) scanProblem->getScanItemParameter(s, "density"); i++)
        {
          if (s != 0)
            scan(next, false, pCallback, pReport);
          else
            // some function
            {
              scanProblem->calculate();
              pCallback(pReport);
            }
          setScanParameterValue(i, s, top);
        }
      break;
    }

  pdelete(mpRandomGenerator);
} // scan() ends

void CScanMethod::setScanParameterValue(unsigned C_INT32 i,
                                        unsigned C_INT32 first,
                                        unsigned C_INT32 last)
{
  unsigned C_INT32 j;
  double min, max, incr, ampl;
  for (j = first; j < last; j++)
    {
      // making a copy of the min and max parameters of the scanItem j
      min = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "min");
      max = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "max");
      ampl = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "ampl");
      incr = * (C_FLOAT64 *) scanProblem->getScanItemParameter(j, "incr");

      // switch the grid type and set values accordingly
      switch ((int)scanProblem->getScanItemParameter(j, "gridType"))
        {
        case SD_UNIFORM:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] =
              min * pow(10, ampl * mpRandomGenerator->getRandomCO());
          else
            mpVariables[j] =
              min + ampl * mpRandomGenerator->getRandomCO();
          break;

        case SD_GAUSS:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = mpRandomGenerator->getRandomNormalLog(min, max);
          else
            mpVariables[j] = mpRandomGenerator->getRandomNormal(min, max);
          break;

        case SD_BOLTZ:
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = mpRandomGenerator->getRandomNormalLog(min, max);
          else
            mpVariables[j] =
              mpRandomGenerator->getRandomNormalPositive(min, max);
          break;

        case SD_REGULAR:
          // log scale
          if (scanProblem->getScanItemParameter(j, "log"))
            mpVariables[j] = min * pow(10, incr * i);
          // non-log scale
          else
            mpVariables[j] = (min + incr * i);
          break;
        }
    }
}
#endif
