###############################################################################
#
# Description       : CMake build script for COPASI Python bindings
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
# 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
# 
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include(FindPythonLibs)
include(FindPythonInterp)

####################################################################
#
# ensure that LAPACK variables are there for swig
# 
if (APPLE)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DDarwin)
endif(APPLE)

if (CLAPACK_FOUND)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_CLAPACK)
elseif (USE_MKL)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_MKL)
elseif(USE_ACML)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_ACML)
elseif(LAPACK_FOUND)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_LAPACK)
endif()


ADD_CUSTOM_COMMAND(	
    OUTPUT ${COPASI_BINARY_DIR}/copasi/bindings/python/copasi_wrapper.cpp
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS	-I${COPASI_SOURCE_DIR}/copasi/bindings/swig/
            -I${COPASI_SOURCE_DIR}/copasi
            -I${COPASI_SOURCE_DIR}/copasi/bindings/python
			-I${COPASI_SOURCE_DIR}
            -c++
            -python		
            ${SWIG_EXTRA_ARGS}		 
            -o ${COPASI_BINARY_DIR}/copasi/bindings/python/copasi_wrapper.cpp 
            ${COPASI_SOURCE_DIR}/copasi/bindings/python/python.i

    MAIN_DEPENDENCY ${COPASI_SOURCE_DIR}/copasi/bindings/python/python.i
    DEPENDS ${COPASI_SOURCE_DIR}/copasi/bindings/python/CMakeLists.txt
            ${SWIG_DEPENDENCIES}
    COMMENT "Swig Python source") 

# BioPreDyn patch - Change target name
add_custom_target(copasi_binding_python_swig ALL DEPENDS ${COPASI_SOURCE_DIR}/copasi/bindings/python/python.i)

	
####################################################################
#
# Build native library
#


include(../../common.cmake)
include(../../CMakeConsoleApp.cmake)

include_directories(${COPASI_SOURCE_DIR}/copasi/bindings/python)
include_directories(${COPASI_SOURCE_DIR}/copasi)
include_directories(${COPASI_SOURCE_DIR}/copasi/bindings/swig)
include_directories(${COPASI_SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

add_library(copasi_binding_python_lib SHARED copasi_wrapper.cpp)
add_dependencies( copasi_binding_python_lib copasi_binding_python_swig) 

set_target_properties (copasi_binding_python_lib PROPERTIES OUTPUT_NAME "_COPASI")
if (UNIX)
	set_target_properties (copasi_binding_python_lib PROPERTIES PREFIX "")
	set_target_properties (copasi_binding_python_lib PROPERTIES SUFFIX ".so")
else()		
	if (CYGWIN)
		set_target_properties (copasi_binding_python_lib PROPERTIES PREFIX "")
		set_target_properties (copasi_binding_python_lib PROPERTIES SUFFIX ".dll")
	else()
		set_target_properties (copasi_binding_python_lib PROPERTIES SUFFIX ".pyd")	
	endif()
endif()

target_link_libraries(copasi_binding_python_lib sbml_binding_python_lib ${SE_EXTERNAL_LIBS} ${SE_LIBS}  ${PYTHON_LIBRARIES})

# BioPreDyn patch - Remove Python installation package definition
INSTALL(TARGETS copasi_binding_python_lib DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/copasi )

file(WRITE "${COPASI_BINARY_DIR}/copasi/bindings/python/copasi.pth" "copasi\n")
INSTALL(FILES ${COPASI_BINARY_DIR}/copasi/bindings/python/copasi.pth  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR})
INSTALL(FILES ${COPASI_BINARY_DIR}/copasi/bindings/python/COPASI.py  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/copasi )
file(GLOB examples ${COPASI_SOURCE_DIR}/copasi/copasi/bindings/python/examples/*.py)
INSTALL(FILES ${examples} DESTINATION ${MISC_PREFIX}bindings/python) 
