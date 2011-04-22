// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000097.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/04/22 15:27:31 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000097_H__
#define TEST_000097_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for dealing with render information
 */

class CCopasiDataModel;

class test000097 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000097);
  CPPUNIT_TEST(test_import_local_render_information);
  CPPUNIT_TEST(test_import_global_render_information);
  CPPUNIT_TEST(test_export_local_render_information);
  CPPUNIT_TEST(test_export_global_render_information);
  CPPUNIT_TEST(test_save_local_render_information);
  CPPUNIT_TEST(test_save_global_render_information);
  CPPUNIT_TEST(test_read_local_render_information);
  CPPUNIT_TEST(test_read_global_render_information);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model with local render information
  static const char* SBML_MODEL_1;
  // SBML model with global render information
  static const char* SBML_MODEL_2;
  // COPASI model with local render information
  static const char* CPS_MODEL_1;
  // COPASI model with global render information
  static const char* CPS_MODEL_2;

  CCopasiDataModel* pDataModel;

  // method the create a model with a single compartment
  // and a small layout
  void createModel();

  // method to add a local render information object
  // to the given model
  void addLocalRenderInformation();

  // method to add a global render information object
  // to the given model
  void addGlobalRenderInformation();

public:
  void setUp();

  void tearDown();

  // tests whether we are importing local render information
  void test_import_local_render_information();

  // tests whether we are importing global render information
  void test_import_global_render_information();

  // tests whether we are exporting local render information
  void test_export_local_render_information();

  // tests whether we are exporting global render information
  void test_export_global_render_information();

  // tests whether we are saving local render information
  void test_save_local_render_information();

  // tests whether we are saving global render information
  void test_save_global_render_information();

  // test whether we are reading local render information
  void test_read_local_render_information();

  // test whether we are reading global render information
  void test_read_global_render_information();
};

#endif /* TEST000097_H__ */
