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
#include "../test/pmvcarchTestSuite.h"

static MultitonTestSuite suite_MultitonTestSuite;

static CxxTest::List Tests_MultitonTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MultitonTestSuite( "../test/pmvcarchTestSuite.h", 27, "MultitonTestSuite", suite_MultitonTestSuite, Tests_MultitonTestSuite );

static class TestDescription_MultitonTestSuite_testCreateInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testCreateInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 30, "testCreateInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testCreateInstances(); }
} testDescription_MultitonTestSuite_testCreateInstances;

static class TestDescription_MultitonTestSuite_testNumberInstances : public CxxTest::RealTestDescription {
public:
 TestDescription_MultitonTestSuite_testNumberInstances() : CxxTest::RealTestDescription( Tests_MultitonTestSuite, suiteDescription_MultitonTestSuite, 38, "testNumberInstances" ) {}
 void runTest() { suite_MultitonTestSuite.testNumberInstances(); }
} testDescription_MultitonTestSuite_testNumberInstances;

static IBodyTestSuite suite_IBodyTestSuite;

static CxxTest::List Tests_IBodyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IBodyTestSuite( "../test/pmvcarchTestSuite.h", 53, "IBodyTestSuite", suite_IBodyTestSuite, Tests_IBodyTestSuite );

static class TestDescription_IBodyTestSuite_testCanSetGet_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testCanSetGet_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 61, "testCanSetGet_type" ) {}
 void runTest() { suite_IBodyTestSuite.testCanSetGet_type(); }
} testDescription_IBodyTestSuite_testCanSetGet_type;

static class TestDescription_IBodyTestSuite_testConstructor_Sets_type : public CxxTest::RealTestDescription {
public:
 TestDescription_IBodyTestSuite_testConstructor_Sets_type() : CxxTest::RealTestDescription( Tests_IBodyTestSuite, suiteDescription_IBodyTestSuite, 66, "testConstructor_Sets_type" ) {}
 void runTest() { suite_IBodyTestSuite.testConstructor_Sets_type(); }
} testDescription_IBodyTestSuite_testConstructor_Sets_type;

static NotificationTestSuite suite_NotificationTestSuite;

static CxxTest::List Tests_NotificationTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotificationTestSuite( "../test/pmvcarchTestSuite.h", 78, "NotificationTestSuite", suite_NotificationTestSuite, Tests_NotificationTestSuite );

static class TestDescription_NotificationTestSuite_testConstructorSets_name_type : public CxxTest::RealTestDescription {
public:
 TestDescription_NotificationTestSuite_testConstructorSets_name_type() : CxxTest::RealTestDescription( Tests_NotificationTestSuite, suiteDescription_NotificationTestSuite, 88, "testConstructorSets_name_type" ) {}
 void runTest() { suite_NotificationTestSuite.testConstructorSets_name_type(); }
} testDescription_NotificationTestSuite_testConstructorSets_name_type;

static MacroCommandTestSuite suite_MacroCommandTestSuite;

static CxxTest::List Tests_MacroCommandTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MacroCommandTestSuite( "../test/pmvcarchTestSuite.h", 135, "MacroCommandTestSuite", suite_MacroCommandTestSuite, Tests_MacroCommandTestSuite );

static class TestDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector : public CxxTest::RealTestDescription {
public:
 TestDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector() : CxxTest::RealTestDescription( Tests_MacroCommandTestSuite, suiteDescription_MacroCommandTestSuite, 142, "testAdd_addSubCommand_IncrementsCommandVector" ) {}
 void runTest() { suite_MacroCommandTestSuite.testAdd_addSubCommand_IncrementsCommandVector(); }
} testDescription_MacroCommandTestSuite_testAdd_addSubCommand_IncrementsCommandVector;

static class TestDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands : public CxxTest::RealTestDescription {
public:
 TestDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands() : CxxTest::RealTestDescription( Tests_MacroCommandTestSuite, suiteDescription_MacroCommandTestSuite, 146, "testExecuteShouldExecAllSubCommands" ) {}
 void runTest() { suite_MacroCommandTestSuite.testExecuteShouldExecAllSubCommands(); }
} testDescription_MacroCommandTestSuite_testExecuteShouldExecAllSubCommands;

static NotifierTestSuite suite_NotifierTestSuite;

static CxxTest::List Tests_NotifierTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NotifierTestSuite( "../test/pmvcarchTestSuite.h", 157, "NotifierTestSuite", suite_NotifierTestSuite, Tests_NotifierTestSuite );

static class TestDescription_NotifierTestSuite_testCanInitializeNotifier : public CxxTest::RealTestDescription {
public:
 TestDescription_NotifierTestSuite_testCanInitializeNotifier() : CxxTest::RealTestDescription( Tests_NotifierTestSuite, suiteDescription_NotifierTestSuite, 174, "testCanInitializeNotifier" ) {}
 void runTest() { suite_NotifierTestSuite.testCanInitializeNotifier(); }
} testDescription_NotifierTestSuite_testCanInitializeNotifier;

static class TestDescription_NotifierTestSuite_testCanSendNotification : public CxxTest::RealTestDescription {
public:
 TestDescription_NotifierTestSuite_testCanSendNotification() : CxxTest::RealTestDescription( Tests_NotifierTestSuite, suiteDescription_NotifierTestSuite, 178, "testCanSendNotification" ) {}
 void runTest() { suite_NotifierTestSuite.testCanSendNotification(); }
} testDescription_NotifierTestSuite_testCanSendNotification;

static ObserverTestSuite suite_ObserverTestSuite;

static CxxTest::List Tests_ObserverTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ObserverTestSuite( "../test/pmvcarchTestSuite.h", 219, "ObserverTestSuite", suite_ObserverTestSuite, Tests_ObserverTestSuite );

static class TestDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 230, "testObserverConstructorShouldSetNotifyMethodAndNotifyContext" ) {}
 void runTest() { suite_ObserverTestSuite.testObserverConstructorShouldSetNotifyMethodAndNotifyContext(); }
} testDescription_ObserverTestSuite_testObserverConstructorShouldSetNotifyMethodAndNotifyContext;

static class TestDescription_ObserverTestSuite_testCanNotifyInterestedObject : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testCanNotifyInterestedObject() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 235, "testCanNotifyInterestedObject" ) {}
 void runTest() { suite_ObserverTestSuite.testCanNotifyInterestedObject(); }
} testDescription_ObserverTestSuite_testCanNotifyInterestedObject;

static class TestDescription_ObserverTestSuite_testCanCompareContexts : public CxxTest::RealTestDescription {
public:
 TestDescription_ObserverTestSuite_testCanCompareContexts() : CxxTest::RealTestDescription( Tests_ObserverTestSuite, suiteDescription_ObserverTestSuite, 240, "testCanCompareContexts" ) {}
 void runTest() { suite_ObserverTestSuite.testCanCompareContexts(); }
} testDescription_ObserverTestSuite_testCanCompareContexts;

static ProxyTestSuite suite_ProxyTestSuite;

static CxxTest::List Tests_ProxyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ProxyTestSuite( "../test/pmvcarchTestSuite.h", 284, "ProxyTestSuite", suite_ProxyTestSuite, Tests_ProxyTestSuite );

static class TestDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData : public CxxTest::RealTestDescription {
public:
 TestDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData() : CxxTest::RealTestDescription( Tests_ProxyTestSuite, suiteDescription_ProxyTestSuite, 287, "testConstructorCanInitializeTemplatedData" ) {}
 void runTest() { suite_ProxyTestSuite.testConstructorCanInitializeTemplatedData(); }
} testDescription_ProxyTestSuite_testConstructorCanInitializeTemplatedData;

static class TestDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember : public CxxTest::RealTestDescription {
public:
 TestDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember() : CxxTest::RealTestDescription( Tests_ProxyTestSuite, suiteDescription_ProxyTestSuite, 292, "testRegisterCallsDerivedClassMember" ) {}
 void runTest() { suite_ProxyTestSuite.testRegisterCallsDerivedClassMember(); }
} testDescription_ProxyTestSuite_testRegisterCallsDerivedClassMember;

static MediatorTestSuite suite_MediatorTestSuite;

static CxxTest::List Tests_MediatorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MediatorTestSuite( "../test/pmvcarchTestSuite.h", 352, "MediatorTestSuite", suite_MediatorTestSuite, Tests_MediatorTestSuite );

static class TestDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent : public CxxTest::RealTestDescription {
public:
 TestDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent() : CxxTest::RealTestDescription( Tests_MediatorTestSuite, suiteDescription_MediatorTestSuite, 360, "testConstructorSetsNameAndViewComponent" ) {}
 void runTest() { suite_MediatorTestSuite.testConstructorSetsNameAndViewComponent(); }
} testDescription_MediatorTestSuite_testConstructorSetsNameAndViewComponent;

static class TestDescription_MediatorTestSuite_testCanGetNotificationInterests : public CxxTest::RealTestDescription {
public:
 TestDescription_MediatorTestSuite_testCanGetNotificationInterests() : CxxTest::RealTestDescription( Tests_MediatorTestSuite, suiteDescription_MediatorTestSuite, 366, "testCanGetNotificationInterests" ) {}
 void runTest() { suite_MediatorTestSuite.testCanGetNotificationInterests(); }
} testDescription_MediatorTestSuite_testCanGetNotificationInterests;

static ViewTestSuite suite_ViewTestSuite;

static CxxTest::List Tests_ViewTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ViewTestSuite( "../test/pmvcarchTestSuite.h", 380, "ViewTestSuite", suite_ViewTestSuite, Tests_ViewTestSuite );

static class TestDescription_ViewTestSuite_testMultitonKeyIsSet : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testMultitonKeyIsSet() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 398, "testMultitonKeyIsSet" ) {}
 void runTest() { suite_ViewTestSuite.testMultitonKeyIsSet(); }
} testDescription_ViewTestSuite_testMultitonKeyIsSet;

static class TestDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 402, "testCanRegisterAndNotifyAndRemoveObserver" ) {}
 void runTest() { suite_ViewTestSuite.testCanRegisterAndNotifyAndRemoveObserver(); }
} testDescription_ViewTestSuite_testCanRegisterAndNotifyAndRemoveObserver;

static class TestDescription_ViewTestSuite_testCanRegisterAndRetrieveMediator : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testCanRegisterAndRetrieveMediator() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 413, "testCanRegisterAndRetrieveMediator" ) {}
 void runTest() { suite_ViewTestSuite.testCanRegisterAndRetrieveMediator(); }
} testDescription_ViewTestSuite_testCanRegisterAndRetrieveMediator;

static class TestDescription_ViewTestSuite_testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 423, "testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers" ) {}
 void runTest() { suite_ViewTestSuite.testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers(); }
} testDescription_ViewTestSuite_testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers;

static class TestDescription_ViewTestSuite_testCanRetrieveMediator : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testCanRetrieveMediator() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 433, "testCanRetrieveMediator" ) {}
 void runTest() { suite_ViewTestSuite.testCanRetrieveMediator(); }
} testDescription_ViewTestSuite_testCanRetrieveMediator;

static class TestDescription_ViewTestSuite_testCanRemoveView : public CxxTest::RealTestDescription {
public:
 TestDescription_ViewTestSuite_testCanRemoveView() : CxxTest::RealTestDescription( Tests_ViewTestSuite, suiteDescription_ViewTestSuite, 439, "testCanRemoveView" ) {}
 void runTest() { suite_ViewTestSuite.testCanRemoveView(); }
} testDescription_ViewTestSuite_testCanRemoveView;

static ModelTestSuite suite_ModelTestSuite;

static CxxTest::List Tests_ModelTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ModelTestSuite( "../test/pmvcarchTestSuite.h", 470, "ModelTestSuite", suite_ModelTestSuite, Tests_ModelTestSuite );

static class TestDescription_ModelTestSuite_testMultitonKeyIsSet : public CxxTest::RealTestDescription {
public:
 TestDescription_ModelTestSuite_testMultitonKeyIsSet() : CxxTest::RealTestDescription( Tests_ModelTestSuite, suiteDescription_ModelTestSuite, 480, "testMultitonKeyIsSet" ) {}
 void runTest() { suite_ModelTestSuite.testMultitonKeyIsSet(); }
} testDescription_ModelTestSuite_testMultitonKeyIsSet;

static class TestDescription_ModelTestSuite_testCanRegisterAndRetrieveAndRemoveProxy : public CxxTest::RealTestDescription {
public:
 TestDescription_ModelTestSuite_testCanRegisterAndRetrieveAndRemoveProxy() : CxxTest::RealTestDescription( Tests_ModelTestSuite, suiteDescription_ModelTestSuite, 484, "testCanRegisterAndRetrieveAndRemoveProxy" ) {}
 void runTest() { suite_ModelTestSuite.testCanRegisterAndRetrieveAndRemoveProxy(); }
} testDescription_ModelTestSuite_testCanRegisterAndRetrieveAndRemoveProxy;

static class TestDescription_ModelTestSuite_testCanRemoveModel : public CxxTest::RealTestDescription {
public:
 TestDescription_ModelTestSuite_testCanRemoveModel() : CxxTest::RealTestDescription( Tests_ModelTestSuite, suiteDescription_ModelTestSuite, 499, "testCanRemoveModel" ) {}
 void runTest() { suite_ModelTestSuite.testCanRemoveModel(); }
} testDescription_ModelTestSuite_testCanRemoveModel;

static ControllerTestSuite suite_ControllerTestSuite;

static CxxTest::List Tests_ControllerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ControllerTestSuite( "../test/pmvcarchTestSuite.h", 525, "ControllerTestSuite", suite_ControllerTestSuite, Tests_ControllerTestSuite );

static class TestDescription_ControllerTestSuite_testCanGetControllerInstance : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanGetControllerInstance() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 539, "testCanGetControllerInstance" ) {}
 void runTest() { suite_ControllerTestSuite.testCanGetControllerInstance(); }
} testDescription_ControllerTestSuite_testCanGetControllerInstance;

static class TestDescription_ControllerTestSuite_testMultitonKeyIsSet : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testMultitonKeyIsSet() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 545, "testMultitonKeyIsSet" ) {}
 void runTest() { suite_ControllerTestSuite.testMultitonKeyIsSet(); }
} testDescription_ControllerTestSuite_testMultitonKeyIsSet;

static class TestDescription_ControllerTestSuite_testCanRegisterCommand : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanRegisterCommand() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 549, "testCanRegisterCommand" ) {}
 void runTest() { suite_ControllerTestSuite.testCanRegisterCommand(); }
} testDescription_ControllerTestSuite_testCanRegisterCommand;

static class TestDescription_ControllerTestSuite_testCanExecuteCommandAndExecuteThroughNotification : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanExecuteCommandAndExecuteThroughNotification() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 553, "testCanExecuteCommandAndExecuteThroughNotification" ) {}
 void runTest() { suite_ControllerTestSuite.testCanExecuteCommandAndExecuteThroughNotification(); }
} testDescription_ControllerTestSuite_testCanExecuteCommandAndExecuteThroughNotification;

static class TestDescription_ControllerTestSuite_testCanRemoveCommand : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanRemoveCommand() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 560, "testCanRemoveCommand" ) {}
 void runTest() { suite_ControllerTestSuite.testCanRemoveCommand(); }
} testDescription_ControllerTestSuite_testCanRemoveCommand;

static class TestDescription_ControllerTestSuite_testCanRemoveController : public CxxTest::RealTestDescription {
public:
 TestDescription_ControllerTestSuite_testCanRemoveController() : CxxTest::RealTestDescription( Tests_ControllerTestSuite, suiteDescription_ControllerTestSuite, 568, "testCanRemoveController" ) {}
 void runTest() { suite_ControllerTestSuite.testCanRemoveController(); }
} testDescription_ControllerTestSuite_testCanRemoveController;

static FacadeTestSuite suite_FacadeTestSuite;

static CxxTest::List Tests_FacadeTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FacadeTestSuite( "../test/pmvcarchTestSuite.h", 602, "FacadeTestSuite", suite_FacadeTestSuite, Tests_FacadeTestSuite );

static class TestDescription_FacadeTestSuite_testMultitonKeysAreSet : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testMultitonKeysAreSet() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 617, "testMultitonKeysAreSet" ) {}
 void runTest() { suite_FacadeTestSuite.testMultitonKeysAreSet(); }
} testDescription_FacadeTestSuite_testMultitonKeysAreSet;

static class TestDescription_FacadeTestSuite_testCanRegisterAndRemoveCommand : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanRegisterAndRemoveCommand() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 624, "testCanRegisterAndRemoveCommand" ) {}
 void runTest() { suite_FacadeTestSuite.testCanRegisterAndRemoveCommand(); }
} testDescription_FacadeTestSuite_testCanRegisterAndRemoveCommand;

static class TestDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveProxy : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveProxy() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 632, "testCanRegisterAndRetrieveAndRemoveProxy" ) {}
 void runTest() { suite_FacadeTestSuite.testCanRegisterAndRetrieveAndRemoveProxy(); }
} testDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveProxy;

static class TestDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveMediator : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveMediator() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 642, "testCanRegisterAndRetrieveAndRemoveMediator" ) {}
 void runTest() { suite_FacadeTestSuite.testCanRegisterAndRetrieveAndRemoveMediator(); }
} testDescription_FacadeTestSuite_testCanRegisterAndRetrieveAndRemoveMediator;

static class TestDescription_FacadeTestSuite_testCanSendNotificationToCommand : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanSendNotificationToCommand() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 652, "testCanSendNotificationToCommand" ) {}
 void runTest() { suite_FacadeTestSuite.testCanSendNotificationToCommand(); }
} testDescription_FacadeTestSuite_testCanSendNotificationToCommand;

static class TestDescription_FacadeTestSuite_testCanSendNotificationToMediator : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanSendNotificationToMediator() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 658, "testCanSendNotificationToMediator" ) {}
 void runTest() { suite_FacadeTestSuite.testCanSendNotificationToMediator(); }
} testDescription_FacadeTestSuite_testCanSendNotificationToMediator;

static class TestDescription_FacadeTestSuite_testCanRemoveCore : public CxxTest::RealTestDescription {
public:
 TestDescription_FacadeTestSuite_testCanRemoveCore() : CxxTest::RealTestDescription( Tests_FacadeTestSuite, suiteDescription_FacadeTestSuite, 665, "testCanRemoveCore" ) {}
 void runTest() { suite_FacadeTestSuite.testCanRemoveCore(); }
} testDescription_FacadeTestSuite_testCanRemoveCore;

#include <cxxtest/Root.cpp>
