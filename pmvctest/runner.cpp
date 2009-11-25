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
CxxTest::StaticSuiteDescription suiteDescription_NotesTestSuite( "pmvcarchTestSuite.h", 27, "NotesTestSuite", suite_NotesTestSuite, Tests_NotesTestSuite );

static class TestDescription_NotesTestSuite_testToDoList : public CxxTest::RealTestDescription {
public:
 TestDescription_NotesTestSuite_testToDoList() : CxxTest::RealTestDescription( Tests_NotesTestSuite, suiteDescription_NotesTestSuite, 30, "testToDoList" ) {}
 void runTest() { suite_NotesTestSuite.testToDoList(); }
} testDescription_NotesTestSuite_testToDoList;

static MultitonTestSuite suite_MultitonTestSuite;

static CxxTest::List Tests_MultitonTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MultitonTestSuite( "pmvcarchTestSuite.h", 41, "MultitonTestSuite", suite_MultitonTestSuite, Tests_MultitonTestSuite );

static class TestDescription_MultitonTestSuite_testCreateInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testCreateInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 44, "testCreateInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testCreateInstances(); }
} testDescription_MultitonTestSuite_testCreateInstances;

static class TestDescription_MultitonTestSuite_testNumberInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testNumberInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 58, "testNumberInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testNumberInstances(); }
} testDescription_MultitonTestSuite_testNumberInstances;

static IBodyTestSuite suite_IBodyTestSuite;

static CxxTest::List Tests_IBodyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IBodyTestSuite( "pmvcarchTestSuite.h", 73, "IBodyTestSuite", suite_IBodyTestSuite, Tests_IBodyTestSuite );

static class TestDescription_IBodyTestSuite_testCanSetGet_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testCanSetGet_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 81, "testCanSetGet_type" ) {}
 void runTest() { suite_IBodyTestSuite.testCanSetGet_type(); }
} testDescription_IBodyTestSuite_testCanSetGet_type;

static class TestDescription_IBodyTestSuite_testConstructor_Sets_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testConstructor_Sets_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 86, "testConstructor_Sets_type" ) {}
 void runTest() { suite_IBodyTestSuite.testConstructor_Sets_type(); }
} testDescription_IBodyTestSuite_testConstructor_Sets_type;

static FacadeTestSuite suite_FacadeTestSuite;

static CxxTest::List Tests_FacadeTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FacadeTestSuite( "pmvcarchTestSuite.h", 122, "FacadeTestSuite", suite_FacadeTestSuite, Tests_FacadeTestSuite );

static class TestDescription_FacadeTestSuite_testMultitonKeySet : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testMultitonKeySet() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 135, "testMultitonKeySet" ) {}
 void runTest() { suite_FacadeTestSuite.testMultitonKeySet(); }
} testDescription_FacadeTestSuite_testMultitonKeySet;

static class TestDescription_FacadeTestSuite_testControllerInitialized : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testControllerInitialized() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 139, "testControllerInitialized" ) {}
 void runTest() { suite_FacadeTestSuite.testControllerInitialized(); }
} testDescription_FacadeTestSuite_testControllerInitialized;

static NotifierTestSuite suite_NotifierTestSuite;

static CxxTest::List Tests_NotifierTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotifierTestSuite( "pmvcarchTestSuite.h", 154, "NotifierTestSuite", suite_NotifierTestSuite, Tests_NotifierTestSuite );

static class TestDescription_NotifierTestSuite_testCanInitialize : public CxxTest::RealTestDescription {
public:
 TestDescription_NotifierTestSuite_testCanInitialize() : CxxTest::RealTestDescription( Tests_NotifierTestSuite, suiteDescription_NotifierTestSuite, 163, "testCanInitialize" ) {}
 void runTest() { suite_NotifierTestSuite.testCanInitialize(); }
} testDescription_NotifierTestSuite_testCanInitialize;

static testModel suite_testModel;

static CxxTest::List Tests_testModel = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_testModel( "pmvcarchTestSuite.h", 175, "testModel", suite_testModel, Tests_testModel );

static class TestDescription_testModel_testConstructor_Sets_multitonKey : public CxxTest::RealTestDescription {
public:
 TestDescription_testModel_testConstructor_Sets_multitonKey() : CxxTest::RealTestDescription( Tests_testModel, suiteDescription_testModel, 183, "testConstructor_Sets_multitonKey" ) {}
 void runTest() { suite_testModel.testConstructor_Sets_multitonKey(); }
} testDescription_testModel_testConstructor_Sets_multitonKey;

#include <cxxtest/Root.cpp>
