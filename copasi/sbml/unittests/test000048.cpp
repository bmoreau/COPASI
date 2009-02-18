// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000048.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:38:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000048.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/report/CCopasiRootContainer.h"

CCopasiDataModel* test000048::pCOPASIDATAMODEL = NULL;

void test000048::setUp()
{
  // Create the root container.
  CCopasiRootContainer::init(false, 0, NULL);
  // Create the global data model.
  pCOPASIDATAMODEL = CCopasiRootContainer::Root->addDatamodel();
}

void test000048::tearDown()
{
  delete CCopasiRootContainer::Root;
  CCopasiRootContainer::Root = NULL;
}

void test000048::test_bug919()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000048::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == false);
  // since the compartment is no constant all species should be
  // exported with the hasOnlySubstanceUnits flag set to true
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 2);
  const Species* pA = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getHasOnlySubstanceUnits() == true);
  const Species* pB = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getHasOnlySubstanceUnits() == true);

  CPPUNIT_ASSERT(pModel->getNumInitialAssignments() == 1);
  // check the initial assignment
  const InitialAssignment* pIA = pModel->getInitialAssignment(0);
  CPPUNIT_ASSERT(pIA != NULL);
  CPPUNIT_ASSERT(pIA->getSymbol() == pCompartment->getId());
  CPPUNIT_ASSERT(pIA->isSetMath() == true);
  const ASTNode* pNode = pIA->getMath();
  CPPUNIT_ASSERT(pNode != NULL);
  // since the quantity unit is set to particle numbers, the expression should
  // consists of only one node which is a reference to species A
  CPPUNIT_ASSERT(pNode->getType() == AST_NAME);
  CPPUNIT_ASSERT(pNode->getName() == pA->getId());
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  // check the rule
  const Rule* pRule = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  const RateRule* pRateRule = dynamic_cast<const RateRule*>(pRule);
  CPPUNIT_ASSERT(pRateRule != NULL);
  CPPUNIT_ASSERT(pRateRule->getVariable() == pCompartment->getId());
  CPPUNIT_ASSERT(pRule->isSetMath() == true);
  pNode = pRateRule->getMath();
  CPPUNIT_ASSERT(pNode != NULL);
  CPPUNIT_ASSERT(pNode->getType() == AST_NAME);
  CPPUNIT_ASSERT(pNode->getName() == pA->getId());
}

const char* test000048::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.2.23++ (Debug) (http://www.copasi.org) at 2007-12-05 21:20:21 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"23\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_13\" name=\"Mass action (irreversible)\" type=\"MassAction\" reversible=\"false\">\n"
  "      <Expression>\n"
  "        k1*PRODUCT&lt;substrate_i&gt;\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_81\" name=\"k1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_79\" name=\"substrate\" order=\"1\" role=\"substrate\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "    <Function key=\"Function_44\" name=\"Objective Function\" type=\"Expression\">\n"
  "      <Expression>\n"
  "        \n"
  "      </Expression>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"ode\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumber&gt;\n"
  "        </Expression>\n"
  "        <InitialExpression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialParticleNumber&gt;\n"
  "        </InitialExpression>\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"A\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"B\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction\" reversible=\"false\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfProducts>\n"
  "          <Product metabolite=\"Metabolite_1\" stoichiometry=\"1\"/>\n"
  "        </ListOfProducts>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_103\" name=\"k1\" value=\"0.1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_13\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_81\">\n"
  "              <SourceParameter reference=\"Parameter_103\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_79\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1000 1000 100\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <ListOfTasks>\n"
  "    <Task key=\"Task_11\" name=\"Steady-State\" type=\"steadyState\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_7\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"JacobianRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"StabilityAnalysisRequested\" type=\"bool\" value=\"1\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Enhanced Newton\" type=\"EnhancedNewton\">\n"
  "        <Parameter name=\"Resolution\" type=\"unsignedFloat\" value=\"1e-09\"/>\n"
  "        <Parameter name=\"Derivation Factor\" type=\"unsignedFloat\" value=\"0.001\"/>\n"
  "        <Parameter name=\"Use Newton\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Use Back Integration\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Accept Negative Concentrations\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Iteration Limit\" type=\"unsignedInteger\" value=\"50\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_12\" name=\"Time-Course\" type=\"timeCourse\" scheduled=\"true\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"StepNumber\" type=\"unsignedInteger\" value=\"100000\"/>\n"
  "        <Parameter name=\"StepSize\" type=\"float\" value=\"0.001\"/>\n"
  "        <Parameter name=\"Duration\" type=\"float\" value=\"100\"/>\n"
  "        <Parameter name=\"TimeSeriesRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"OutputStartTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Stochastic (Gibson + Bruck)\" type=\"Stochastic\">\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"integer\" value=\"1000000\"/>\n"
  "        <Parameter name=\"Subtype\" type=\"unsignedInteger\" value=\"2\"/>\n"
  "        <Parameter name=\"Use Random Seed\" type=\"bool\" value=\"0\"/>\n"
  "        <Parameter name=\"Random Seed\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_13\" name=\"Scan\" type=\"scan\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"Subtask\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <ParameterGroup name=\"ScanItems\">\n"
  "        </ParameterGroup>\n"
  "        <Parameter name=\"Output in subtask\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Adjust initial conditions\" type=\"bool\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Scan Framework\" type=\"ScanFramework\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_14\" name=\"Elementary Flux Modes\" type=\"fluxMode\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_8\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"EFM Algorithm\" type=\"EFMAlgorithm\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_15\" name=\"Optimization\" type=\"optimization\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_9\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"Time-Course\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"ObjectiveFunction\" type=\"key\" value=\"\"/>\n"
  "        <Parameter name=\"Maximize\" type=\"bool\" value=\"0\"/>\n"
  "        <ParameterGroup name=\"OptimizationItemList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"OptimizationConstraintList\">\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Random Search\" type=\"RandomSearch\">\n"
  "        <Parameter name=\"Number of Iterations\" type=\"unsignedInteger\" value=\"100000\"/>\n"
  "        <Parameter name=\"Random Number Generator\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <Parameter name=\"Seed\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_16\" name=\"Parameter Estimation\" type=\"parameterFitting\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_10\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_11\"/>\n"
  "        <Parameter name=\"Time-Course\" type=\"key\" value=\"Task_12\"/>\n"
  "        <ParameterGroup name=\"OptimizationItemList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"OptimizationConstraintList\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"Experiment Set\">\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"Cross Validation Set\">\n"
  "          <Parameter name=\"Weight\" type=\"unsignedFloat\" value=\"1\"/>\n"
  "          <Parameter name=\"Threshold\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Evolutionary Programming\" type=\"EvolutionaryProgram\">\n"
  "        <Parameter name=\"Number of Generations\" type=\"unsignedInteger\" value=\"200\"/>\n"
  "        <Parameter name=\"Population Size\" type=\"unsignedInteger\" value=\"20\"/>\n"
  "        <Parameter name=\"Random Number Generator\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <Parameter name=\"Seed\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_17\" name=\"Metabolic Control Analysis\" type=\"metabolicControlAnalysis\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_11\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"Steady-State\" type=\"key\" value=\"Task_11\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"MCA Method (Reder)\" type=\"MCAMethod(Reder)\">\n"
  "        <Parameter name=\"Modulation Factor\" type=\"unsignedFloat\" value=\"1e-09\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_18\" name=\"Lyapunov Exponents\" type=\"lyapunovExponents\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_12\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"ExponentNumber\" type=\"unsignedInteger\" value=\"3\"/>\n"
  "        <Parameter name=\"DivergenceRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"TransientTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"Wolf Method\" type=\"WolfMethod\">\n"
  "        <Parameter name=\"Orthonormalization Interval\" type=\"unsignedFloat\" value=\"1\"/>\n"
  "        <Parameter name=\"Overall time\" type=\"unsignedFloat\" value=\"1000\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Use Default Absolute Tolerance\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_19\" name=\"Time Scale Separation Analysis\" type=\"timeScaleSeparation\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "        <Parameter name=\"StepNumber\" type=\"unsignedInteger\" value=\"100\"/>\n"
  "        <Parameter name=\"StepSize\" type=\"float\" value=\"0.01\"/>\n"
  "        <Parameter name=\"Duration\" type=\"float\" value=\"1\"/>\n"
  "        <Parameter name=\"TimeSeriesRequested\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"OutputStartTime\" type=\"float\" value=\"0\"/>\n"
  "      </Problem>\n"
  "      <Method name=\"ILDM (LSODA)\" type=\"TimeScaleSeparation(ILDM)\">\n"
  "        <Parameter name=\"Deuflhard Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Integrate Reduced Model\" type=\"bool\" value=\"1\"/>\n"
  "        <Parameter name=\"Relative Tolerance\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Absolute Tolerance\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "        <Parameter name=\"Adams Max Order\" type=\"unsignedInteger\" value=\"12\"/>\n"
  "        <Parameter name=\"BDF Max Order\" type=\"unsignedInteger\" value=\"5\"/>\n"
  "        <Parameter name=\"Max Internal Steps\" type=\"unsignedInteger\" value=\"10000\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_20\" name=\"Time Scale Separation\" type=\"timeScaleSeparationAnalysis\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Problem>\n"
  "      </Problem>\n"
  "      <Method name=\"Time Scale Separation Method\" type=\"TimeScaleSeparationMethod\">\n"
  "      </Method>\n"
  "    </Task>\n"
  "    <Task key=\"Task_21\" name=\"Sensitivities\" type=\"sensitivities\" scheduled=\"false\" updateModel=\"false\">\n"
  "      <Report reference=\"Report_13\" target=\"\" append=\"1\"/>\n"
  "      <Problem>\n"
  "        <Parameter name=\"SubtaskType\" type=\"unsignedInteger\" value=\"1\"/>\n"
  "        <ParameterGroup name=\"TargetFunctions\">\n"
  "          <Parameter name=\"SingleObject\" type=\"cn\" value=\"\"/>\n"
  "          <Parameter name=\"ObjectListType\" type=\"unsignedInteger\" value=\"7\"/>\n"
  "        </ParameterGroup>\n"
  "        <ParameterGroup name=\"ListOfVariables\">\n"
  "          <ParameterGroup name=\"Variables\">\n"
  "            <Parameter name=\"SingleObject\" type=\"cn\" value=\"\"/>\n"
  "            <Parameter name=\"ObjectListType\" type=\"unsignedInteger\" value=\"41\"/>\n"
  "          </ParameterGroup>\n"
  "        </ParameterGroup>\n"
  "      </Problem>\n"
  "      <Method name=\"Sensitivities Method\" type=\"SensitivitiesMethod\">\n"
  "        <Parameter name=\"Delta factor\" type=\"unsignedFloat\" value=\"1e-06\"/>\n"
  "        <Parameter name=\"Delta minimum\" type=\"unsignedFloat\" value=\"1e-12\"/>\n"
  "      </Method>\n"
  "    </Task>\n"
  "  </ListOfTasks>\n"
  "  <ListOfReports>\n"
  "    <Report key=\"Report_7\" name=\"Steady-State\" taskType=\"steadyState\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Steady-State]\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_8\" name=\"Elementary Flux Modes\" taskType=\"fluxMode\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Footer>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_9\" name=\"Optimization\" taskType=\"optimization\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Object=Description\"/>\n"
  "        <Object cn=\"String=\\[Function Evaluations\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Value\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Parameters\\]\"/>\n"
  "      </Header>\n"
  "      <Body>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters\"/>\n"
  "      </Body>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Optimization],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_10\" name=\"Parameter Estimation\" taskType=\"parameterFitting\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Object=Description\"/>\n"
  "        <Object cn=\"String=\\[Function Evaluations\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Value\\]\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"String=\\[Best Parameters\\]\"/>\n"
  "      </Header>\n"
  "      <Body>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Function Evaluations\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Value\"/>\n"
  "        <Object cn=\"Separator=&#x09;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Parameters\"/>\n"
  "      </Body>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Parameter Estimation],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_11\" name=\"Metabolic Control Analysis\" taskType=\"metabolicControlAnalysis\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_12\" name=\"Lyapunov Exponents\" taskType=\"lyapunovExponents\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "    <Report key=\"Report_13\" name=\"Sensitivities\" taskType=\"sensitivities\" separator=\"&#x09;\" precision=\"6\">\n"
  "      <Comment>\n"
  "        <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "          Automatically generated report.\n"
  "        </body>\n"
  "      </Comment>\n"
  "      <Header>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Sensitivities],Object=Description\"/>\n"
  "      </Header>\n"
  "      <Footer>\n"
  "        <Object cn=\"String=&#x0a;\"/>\n"
  "        <Object cn=\"CN=Root,Vector=TaskList[Sensitivities],Object=Result\"/>\n"
  "      </Footer>\n"
  "    </Report>\n"
  "  </ListOfReports>\n"
  "  <ListOfPlots>\n"
  "    <PlotSpecification name=\"Particle Number Rates, Volume Rates, and Global Quantity Rates\" type=\"Plot2D\" active=\"0\">\n"
  "      <Parameter name=\"log X\" type=\"bool\" value=\"0\"/>\n"
  "      <Parameter name=\"log Y\" type=\"bool\" value=\"0\"/>\n"
  "      <ListOfPlotItems>\n"
  "        <PlotItem name=\"A.ParticleNumberRate\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumberRate\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "        <PlotItem name=\"B.ParticleNumberRate\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=ParticleNumberRate\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "      </ListOfPlotItems>\n"
  "    </PlotSpecification>\n"
  "    <PlotSpecification name=\"Concentrations, Volumes, and Global Quantity Values\" type=\"Plot2D\" active=\"0\">\n"
  "      <Parameter name=\"log X\" type=\"bool\" value=\"0\"/>\n"
  "      <Parameter name=\"log Y\" type=\"bool\" value=\"0\"/>\n"
  "      <ListOfPlotItems>\n"
  "        <PlotItem name=\"[A]\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "        <PlotItem name=\"[B]\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=Concentration\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "        <PlotItem name=\"Compartments[compartment].Volume\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Compartments[compartment],Reference=Volume\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "      </ListOfPlotItems>\n"
  "    </PlotSpecification>\n"
  "    <PlotSpecification name=\"Reaction Event Fluxes\" type=\"Plot2D\" active=\"0\">\n"
  "      <Parameter name=\"log X\" type=\"bool\" value=\"0\"/>\n"
  "      <Parameter name=\"log Y\" type=\"bool\" value=\"1\"/>\n"
  "      <ListOfPlotItems>\n"
  "        <PlotItem name=\"(reaction).ParticleFlux\" type=\"Curve2D\">\n"
  "          <Parameter name=\"Line type\" type=\"unsignedInteger\" value=\"0\"/>\n"
  "          <Parameter name=\"Recording Activity\" type=\"string\" value=\"during\"/>\n"
  "          <ListOfChannels>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Reference=Time\"/>\n"
  "            <ChannelSpec cn=\"CN=Root,Model=New Model,Vector=Reactions[reaction],Reference=ParticleFlux\"/>\n"
  "          </ListOfChannels>\n"
  "        </PlotItem>\n"
  "      </ListOfPlotItems>\n"
  "    </PlotSpecification>\n"
  "  </ListOfPlots>\n"
  "  <GUI>\n"
  "  </GUI>\n"
  "  <SBMLReference file=\"Bug916.xml\">\n"
  "    <SBMLMap SBMLid=\"compartment_0\" COPASIkey=\"Compartment_0\"/>\n"
  "    <SBMLMap SBMLid=\"reaction_0\" COPASIkey=\"Reaction_0\"/>\n"
  "    <SBMLMap SBMLid=\"species_0\" COPASIkey=\"Metabolite_0\"/>\n"
  "    <SBMLMap SBMLid=\"species_1\" COPASIkey=\"Metabolite_1\"/>\n"
  "  </SBMLReference>\n"
  "</COPASI>\n"
;
