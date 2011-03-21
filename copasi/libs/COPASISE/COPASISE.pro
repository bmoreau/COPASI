# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/libs/COPASISE/COPASISE.pro,v $
#   $Revision: 1.33 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2011/03/21 15:46:21 $
# End CVS Header

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# Automatically generated by qmake (1.07a) Fri Oct 27 13:32:17 2006
######################################################################

TEMPLATE = lib
SRC_TARGET = COPASISE
DISTFILES = COPASISE.pro


include(../../common.pri)

COPASI_LIBS += commandline

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
  COPASI_LIBS += commercial
}
#endif // COPASI_LICENSE_COM

COPASI_LIBS += compareExpressions
COPASI_LIBS += copasiDM
COPASI_LIBS += copasiXML
COPASI_LIBS += crosssection
COPASI_LIBS += elementaryFluxModes
COPASI_LIBS += fitting
COPASI_LIBS += function
COPASI_LIBS += layout
COPASI_LIBS += lyap
COPASI_LIBS += MIRIAM
COPASI_LIBS += math
COPASI_LIBS += model
COPASI_LIBS += moieties
COPASI_LIBS += odepack++
COPASI_LIBS += optimization
COPASI_LIBS += plot
COPASI_LIBS += randomGenerator
COPASI_LIBS += report
COPASI_LIBS += sbmlimport
COPASI_LIBS += sbmlunit
COPASI_LIBS += scan
COPASI_LIBS += sensitivities
COPASI_LIBS += steadystate
COPASI_LIBS += trajectory
COPASI_LIBS += tss
COPASI_LIBS += tssanalysis
COPASI_LIBS += utilities

include(../lib.pri)
