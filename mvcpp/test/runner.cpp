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
#include "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h"

static MultitonTestSuite suite_MultitonTestSuite;

static CxxTest::List Tests_MultitonTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MultitonTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 28, "MultitonTestSuite", suite_MultitonTestSuite, Tests_MultitonTestSuite );

static class TestDescription_MultitonTestSuite_testCreateInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testCreateInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 31, "testCreateInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testCreateInstances(); }
} testDescription_MultitonTestSuite_testCreateInstances;

static class TestDescription_MultitonTestSuite_testNumberInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testNumberInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 45, "testNumberInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testNumberInstances(); }
} testDescription_MultitonTestSuite_testNumberInstances;

static IBodyTestSuite suite_IBodyTestSuite;

static CxxTest::List Tests_IBodyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IBodyTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 60, "IBodyTestSuite", suite_IBodyTestSuite, Tests_IBodyTestSuite );

static class TestDescription_IBodyTestSuite_testCanSetGet_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testCanSetGet_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 68, "testCanSetGet_type" ) {}
 void runTest() { suite_IBodyTestSuite.testCanSetGet_type(); }
} testDescription_IBodyTestSuite_testCanSetGet_type;

static class TestDescription_IBodyTestSuite_testConstructor_Sets_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testConstructor_Sets_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 73, "testConstructor_Sets_type" ) {}
 void runTest() { suite_IBodyTestSuite.testConstructor_Sets_type(); }
} testDescription_IBodyTestSuite_testConstructor_Sets_type;

static NotificationTestSuite suite_NotificationTestSuite;

static CxxTest::List Tests_NotificationTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotificationTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 85, "NotificationTestSuite", suite_NotificationTestSuite, Tests_NotificationTestSuite );

static class TestDescription_NotificationTestSuite_testConstructorSets_name_type : public CxxTest::RealTestDescription {
public:
 TestDescription_NotificationTestSuite_testConstructorSets_name_type() : CxxTest::RealTestDescription( Tests_NotificationTestSuite, suiteDescription_NotificationTestSuite, 95, "testConstructorSets_name_type" ) {}
 void runTest() { suite_NotificationTestSuite.testConstructorSets_name_type(); }
} testDescription_NotificationTestSuite_testConstructorSets_name_type;

static MacroCommandTestSuite suite_MacroCommandTestSuite;

static CxxTest::List Tests_MacroCommandTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MacroCommandTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 142, "MacroCommandTestSuite", suite_MacroCommandTestSuite, Tests_MacroCommandTestSuite );

static class TestDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector : public CxxTest::RealTestDescription {
public:
 TestDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector() : CxxTest::RealTestDescription( Tests_MacroCommandTestSuite, suiteDescription_MacroCommandTestSuite, 149, "testAdd_addSubCommand_IncrementsCommandVector" ) {}
 void runTest() { suite_MacroCommandTestSuite.testAdd_addSubCommand_IncrementsCommandVector(); }
} testDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector;

static class TestDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands : public CxxTest::RealTestDescription {
public:
 TestDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands() : CxxTest::RealTestDescription( Tests_MacroCommandTestSuite, suiteDescription_MacroCommandTestSuite, 153, "testExecuteShouldExecAllSubCommands" ) {}
 void runTest() { suite_MacroCommandTestSuite.testExecuteShouldExecAllSubCommands(); }
} testDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands;

static NotifierTestSuite suite_NotifierTestSuite;

static CxxTest::List Tests_NotifierTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotifierTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 164, "NotifierTestSuite", suite_NotifierTestSuite, Tests_NotifierTestSuite );

static class TestDescription_NotifierTestSuite_testCanInitializeNotifier : public CxxTest::RealTestDescription {
public:
 TestDescription_NotifierTestSuite_testCanInitializeNotifier() : CxxTest::RealTestDescription( Tests_NotifierTestSuite, suiteDescription_NotifierTestSuite, 178, "testCanInitializeNotifier" ) {}
 void runTest() { suite_NotifierTestSuite.testCanInitializeNotifier(); }
} testDescription_NotifierTestSuite_testCanInitializeNotifier;

static ObserverTestSuite suite_ObserverTestSuite;

static CxxTest::List Tests_ObserverTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ObserverTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 211, "ObserverTestSuite", suite_ObserverTestSuite, Tests_ObserverTestSuite );

static class TestDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 222, "testObserverConstructorShouldSetNotifyMethodAndNotifyContext" ) {}
 void runTest() { suite_ObserverTestSuite.testObserverConstructorShouldSetNotifyMethodAndNotifyContext(); }
} testDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext;

static class TestDescription_ObserverTestSuite_testCanNotifyInterestedObject : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testCanNotifyInterestedObject() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 227, "testCanNotifyInterestedObject" ) {}
 void runTest() { suite_ObserverTestSuite.testCanNotifyInterestedObject(); }
} testDescription_ObserverTestSuite_testCanNotifyInterestedObject;

static class TestDescription_ObserverTestSuite_testCanCompareContexts : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testCanCompareContexts() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 232, "testCanCompareContexts" ) {}
 void runTest() { suite_ObserverTestSuite.testCanCompareContexts(); }
} testDescription_ObserverTestSuite_testCanCompareContexts;

static ProxyTestSuite suite_ProxyTestSuite;

static CxxTest::List Tests_ProxyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ProxyTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 261, "ProxyTestSuite", suite_ProxyTestSuite, Tests_ProxyTestSuite );

static class TestDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData : public CxxTest::RealTestDescription {
public:
 TestDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData() : CxxTest::RealTestDescription( Tests_ProxyTestSuite, suiteDescription_ProxyTestSuite, 264, "testConstructorCanInitializeTemplatedData" ) {}
 void runTest() { suite_ProxyTestSuite.testConstructorCanInitializeTemplatedData(); }
} testDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData;

static class TestDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember : public CxxTest::RealTestDescription {
public:
 TestDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember() : CxxTest::RealTestDescription( Tests_ProxyTestSuite, suiteDescription_ProxyTestSuite, 269, "testRegisterCallsDerivedClassMember" ) {}
 void runTest() { suite_ProxyTestSuite.testRegisterCallsDerivedClassMember(); }
} testDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember;

static MediatorTestSuite suite_MediatorTestSuite;

static CxxTest::List Tests_MediatorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MediatorTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 282, "MediatorTestSuite", suite_MediatorTestSuite, Tests_MediatorTestSuite );

static class TestDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent : public CxxTest::RealTestDescription {
public:
 TestDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent() : CxxTest::RealTestDescription( Tests_MediatorTestSuite, suiteDescription_MediatorTestSuite, 290, "testConstructorSetsNameAndViewComponent" ) {}
 void runTest() { suite_MediatorTestSuite.testConstructorSetsNameAndViewComponent(); }
} testDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent;

static ViewTestSuite suite_ViewTestSuite;

static CxxTest::List Tests_ViewTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ViewTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 304, "ViewTestSuite", suite_ViewTestSuite, Tests_ViewTestSuite );

static class TestDescription_ViewTestSuite_testMultitonKeyIsSet : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testMultitonKeyIsSet() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 319, "testMultitonKeyIsSet" ) {}
 void runTest() { suite_ViewTestSuite.testMultitonKeyIsSet(); }
} testDescription_ViewTestSuite_testMultitonKeyIsSet;

static class TestDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 323, "testCanRegisterAndNotifyAndRemoveObserver" ) {}
 void runTest() { suite_ViewTestSuite.testCanRegisterAndNotifyAndRemoveObserver(); }
} testDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver;

static ControllerTestSuite suite_ControllerTestSuite;

static CxxTest::List Tests_ControllerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ControllerTestSuite( "/home/clcks/Code/MVC++/trunk/mvcpp/test/pmvcarchTestSuite.h", 352, "ControllerTestSuite", suite_ControllerTestSuite, Tests_ControllerTestSuite );

static class TestDescription_ControllerTestSuite_testCanGetControllerInstance : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanGetControllerInstance() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 360, "testCanGetControllerInstance" ) {}
 void runTest() { suite_ControllerTestSuite.testCanGetControllerInstance(); }
} testDescription_ControllerTestSuite_testCanGetControllerInstance;

#include <cxxtest/Root.cpp>
