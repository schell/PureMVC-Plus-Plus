/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "pmvcarchTestSuite.h"

static NotesTestSuite suite_NotesTestSuite;

static CxxTest::List Tests_NotesTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotesTestSuite( "pmvcarchTestSuite.h", 59, "NotesTestSuite", suite_NotesTestSuite, Tests_NotesTestSuite );

static class TestDescription_NotesTestSuite_testToDoList : public CxxTest::RealTestDescription {
public:
 TestDescription_NotesTestSuite_testToDoList() : CxxTest::RealTestDescription( Tests_NotesTestSuite, suiteDescription_NotesTestSuite, 62, "testToDoList" ) {}
 void runTest() { suite_NotesTestSuite.testToDoList(); }
} testDescription_NotesTestSuite_testToDoList;

static MultitonTestSuite suite_MultitonTestSuite;

static CxxTest::List Tests_MultitonTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MultitonTestSuite( "pmvcarchTestSuite.h", 73, "MultitonTestSuite", suite_MultitonTestSuite, Tests_MultitonTestSuite );

static class TestDescription_MultitonTestSuite_testCreateInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testCreateInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 76, "testCreateInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testCreateInstances(); }
} testDescription_MultitonTestSuite_testCreateInstances;

static class TestDescription_MultitonTestSuite_testNumberInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testNumberInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 90, "testNumberInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testNumberInstances(); }
} testDescription_MultitonTestSuite_testNumberInstances;

static IBodyTestSuite suite_IBodyTestSuite;

static CxxTest::List Tests_IBodyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IBodyTestSuite( "pmvcarchTestSuite.h", 105, "IBodyTestSuite", suite_IBodyTestSuite, Tests_IBodyTestSuite );

static class TestDescription_IBodyTestSuite_testCanSetGet_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testCanSetGet_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 113, "testCanSetGet_type" ) {}
 void runTest() { suite_IBodyTestSuite.testCanSetGet_type(); }
} testDescription_IBodyTestSuite_testCanSetGet_type;

static class TestDescription_IBodyTestSuite_testConstructor_Sets_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testConstructor_Sets_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 118, "testConstructor_Sets_type" ) {}
 void runTest() { suite_IBodyTestSuite.testConstructor_Sets_type(); }
} testDescription_IBodyTestSuite_testConstructor_Sets_type;

static FacadeTestSuite suite_FacadeTestSuite;

static CxxTest::List Tests_FacadeTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FacadeTestSuite( "pmvcarchTestSuite.h", 130, "FacadeTestSuite", suite_FacadeTestSuite, Tests_FacadeTestSuite );

static class TestDescription_FacadeTestSuite_testMultitonKeySet : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testMultitonKeySet() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 143, "testMultitonKeySet" ) {}
 void runTest() { suite_FacadeTestSuite.testMultitonKeySet(); }
} testDescription_FacadeTestSuite_testMultitonKeySet;

static class TestDescription_FacadeTestSuite_testModelInitialized : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testModelInitialized() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 147, "testModelInitialized" ) {}
 void runTest() { suite_FacadeTestSuite.testModelInitialized(); }
} testDescription_FacadeTestSuite_testModelInitialized;

static class TestDescription_FacadeTestSuite_testControllerInitialized : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testControllerInitialized() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 156, "testControllerInitialized" ) {}
 void runTest() { suite_FacadeTestSuite.testControllerInitialized(); }
} testDescription_FacadeTestSuite_testControllerInitialized;

static class TestDescription_FacadeTestSuite_testViewInitialized : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testViewInitialized() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 165, "testViewInitialized" ) {}
 void runTest() { suite_FacadeTestSuite.testViewInitialized(); }
} testDescription_FacadeTestSuite_testViewInitialized;

static ControllerTestSuite suite_ControllerTestSuite;

static CxxTest::List Tests_ControllerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ControllerTestSuite( "pmvcarchTestSuite.h", 180, "ControllerTestSuite", suite_ControllerTestSuite, Tests_ControllerTestSuite );

static class TestDescription_ControllerTestSuite_testControllerHasAccessToView : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testControllerHasAccessToView() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 189, "testControllerHasAccessToView" ) {}
 void runTest() { suite_ControllerTestSuite.testControllerHasAccessToView(); }
} testDescription_ControllerTestSuite_testControllerHasAccessToView;

static NotifierTestSuite suite_NotifierTestSuite;

static CxxTest::List Tests_NotifierTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotifierTestSuite( "pmvcarchTestSuite.h", 200, "NotifierTestSuite", suite_NotifierTestSuite, Tests_NotifierTestSuite );

static class TestDescription_NotifierTestSuite_testCanInitialize : public CxxTest::RealTestDescription {
public:
 TestDescription_NotifierTestSuite_testCanInitialize() : CxxTest::RealTestDescription( Tests_NotifierTestSuite, suiteDescription_NotifierTestSuite, 209, "testCanInitialize" ) {}
 void runTest() { suite_NotifierTestSuite.testCanInitialize(); }
} testDescription_NotifierTestSuite_testCanInitialize;

#include <cxxtest/Root.cpp>
