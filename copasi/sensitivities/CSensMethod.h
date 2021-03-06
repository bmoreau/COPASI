// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.h,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:33:42 $
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

#ifndef COPASI_SENSMethod
#define COPASI_SENSMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CAnnotatedMatrix.h"

class CSensProblem;
//class CProcessReport;

class CSensMethodLocalData
{
public:
  CCopasiArray tmp1;
  CCopasiArray tmp2;

  std::vector<CCopasiObject*> variables;

  /**
   * holds the index in the index array corresponding to the given level.
   * I.e. which dimension of the result array the variables correspond to.
   */
  size_t index;
};

class CSensMethod : public CCopasiMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  CSensMethod();

protected:
  /**
   * Specific constructor.
   * @param CCopasiMethod::SubType subType
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  explicit CSensMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent = NULL);

public:
  /**
   * Create a trajectory method.
   * Note: the returned object has to be released after use with delete
   */
  static CSensMethod *
  createMethod(CCopasiMethod::SubType subType
               = CCopasiMethod::sensMethod);

  /**
   * Copy constructor.
   * @param "const CTSSMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CSensMethod(const CSensMethod & src,
              const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CSensMethod();

  /**
   */
  bool process(CProcessReport * handler);

  /**
   * initializes the subtask, creates the internal data structures of the method,
   * resizes the result arrays and creates the array annotations
   */
  bool initialize(CSensProblem* problem);

  /**
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  bool restore(const bool & updateModel);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * estimate how many calls to the subtask are necessary. Works only after
   * initialize() was called.
   */
  size_t getNumberOfSubtaskCalculations();

protected:

  bool calculate_one_level(size_t level, CCopasiArray & result);
  bool do_target_calculation(CCopasiArray & result, bool first);

  C_FLOAT64 do_variation(CCopasiObject* variable);

  /**
   * wraps the CCopasiObject::setObjectValue() method so we can add special treatment
   * of concentrations
   */
  void setValue(CCopasiObject* variable, C_FLOAT64 value);

  void calculate_difference(size_t level, const C_FLOAT64 & delta,
                            CCopasiArray & result, CCopasiArray::index_type & resultindex);

  /**
   * calculate the scaled sensitivities. Calls scaling_variables().
   * It is assumed that the scaled result array is already of the correct size
   * (this is done in initialize()).
   */
  void do_scaling();

  /**
   * This contains the loop over the target functions for scaling the sensitivities
   */
  void scaling_targetfunction(const C_FLOAT64 & factor,
                              CCopasiArray::index_type & resultindex);

  /**
   * This contains the loop over the variables for scaling the sensitivities. Works recursively
   * and calls scaling_targetfunction() in the end.
   */
  void scaling_variables(size_t level, const C_FLOAT64 & factor,
                         CCopasiArray::index_type & resultindex);

  /**
   * collapse the first dimension of the scaled result (by
   * calculating the 2-norm over the target functions)
   */
  void do_collapsing();

  C_FLOAT64 do_collapsing_innerloop(CCopasiArray::index_type & fullindex);

  // Attributes
protected:
  /**
   *  A pointer to the sensitivities problem.
   */
  CSensProblem * mpProblem;

  std::vector<CSensMethodLocalData> mLocalData;

  std::vector<CCopasiObject*> mTargetfunctionPointers;

  CCopasiTask * mpSubTask;

  std::vector< Refresh * > mInitialRefreshes;

  C_FLOAT64 * mpDeltaFactor;
  C_FLOAT64 * mpMinDelta;
  
  ///stores the update model flag of the subtask
  bool mStoreSubtasktUpdateFlag;

private:
  size_t mProgressHandler;
  unsigned C_INT32 mProgress;

  size_t mCounter;
  size_t mFailedCounter;
};

#endif
