// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSensTask.i,v $ 
//   $Revision: 1.1.2.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/14 15:11:48 $ 
// End CVS Header 

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "sensitivities/CSensTask.h"

%}

// process is ignored because I have written extension code in CCopasiTask
// that calls the task specific process, so this new process should be
// used for all tasks
%ignore CSensTask::process(const bool& useInitialValues);
%ignore CSensTask::initialize;
%ignore CSensTask::print;
%ignore operator<<(std::ostrean&,const CSensTask&);

%newobject CSensTask::createMethod(const int &) const;

%include "sensitivities/CSensTask.h"
