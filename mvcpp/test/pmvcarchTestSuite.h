/* 
 * File:   pmvcarchTestSuite.h
 * Author: schell = Schell Scivally
 *
 * Created on November 18, 2009, 10:01 PM
 */

#ifndef _PMVCARCHTESTSUITE_H
#define	_PMVCARCHTESTSUITE_H

#include <iostream>
#include <vector>

// cxxtest
#include <cxxtest/TestSuite.h>
// our basic fpatterns
#include <patterns.h>
// Base classes of pmvcpp
#include <pmvcppbase.h>
// Main classes of pmvcpp
#include <pmvcpparch.h>
// Exception classes of pmvcpp
#include <pmvcppexp.h>

//--------------------------------------
//  Patterns
//--------------------------------------
class MultitonTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateInstances()
    {
        Object* single_1 = Multiton<Object>::instance();
        Object* single_2 = Multiton<Object>::instance();
        Object* single_3 = Multiton<Object>::instance("instance3");
//        TS_TRACE("Address of multiton 1:");
//        TS_TRACE(&*single_1);
//        TS_TRACE("Address of multiton 2:");
//        TS_TRACE(&*single_2);
//        TS_TRACE("Address of multiton 3 (should differ):");
//        TS_TRACE(&*single_3);
        TS_ASSERT_EQUALS(&*single_1, &*single_2);
        TS_ASSERT_DIFFERS(&*single_1, &*single_3);
    }
    void testNumberInstances()
    {
        Multiton<Object>::clear();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 0);
        Multiton<Object>::instance();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 1);
        Multiton<Object>::instance();
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 1);
        Multiton<Object>::instance("new instance");
        TS_ASSERT_EQUALS(Multiton<Object>::size(), (size_t) 2);
    }
};
//--------------------------------------
//  IBody
//--------------------------------------
class IBodyTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->type = "thebodytype";
        this->body = new IBody();
    }
    void testCanSetGet_type()
    {
        this->body->setType(type);
        TS_ASSERT_EQUALS(this->body->getType(), type);
    }
    void testConstructor_Sets_type()
    {
        this->body = new IBody(this->type);
        TS_ASSERT_EQUALS(this->body->getType(), this->type);
    }

    IBody* body;
    std::string type;
};
//--------------------------------------
//  Notification
//--------------------------------------
class NotificationTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->name = "notificationName";
        this->body = new IBody();
        this->type = "notificationType";
        this->notification = new Notification(name, body, type);
    }
    void testConstructorSets_name_type()
    {
        TS_ASSERT_EQUALS(this->notification->getName(), this->name);
        TS_ASSERT_EQUALS(this->notification->getType(), this->type);
        //TS_ASSERT_EQUALS(this->notification->getBody(), this->body);
    }
private:
    Notification* notification;
    std::string name;
    std::string type;
    IBody* body;
};
//--------------------------------------
//  SimpleCommand
//--------------------------------------
class SimpleTestClass : public SimpleCommand
{
public:
    void execute(INotification* notification)
    {
        SimpleTestClass::executions++;
    }
    static int executions;
};
int SimpleTestClass::executions = 0;
//--------------------------------------
//  MacroCommand
//--------------------------------------
class MacroTestClass : public MacroCommand
{
public:
    MacroTestClass()
    {
        this->initializeMacroCommand();
    }
    int getSubCommandSize()
    {
        return (int) this->subCommands.size();
    }
protected:
    void initializeMacroCommand()
    {
        this->addSubCommand(new SimpleTestClass());
        this->addSubCommand(new SimpleTestClass());
        this->addSubCommand(new SimpleTestClass());
    }
};
class MacroCommandTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->macroTestClass = new MacroTestClass();
    }
    void testAdd_addSubCommand_IncrementsCommandVector()
    {
        TS_ASSERT_EQUALS(this->macroTestClass->getSubCommandSize(), 3);
    }
    void testExecuteShouldExecAllSubCommands()
    {
        this->macroTestClass->execute(new Notification("macroCommandTestClassNotificationName", new IBody(), "macroCommandTestClassNoteType"));
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 3);
    }
private:
    MacroTestClass* macroTestClass;
};
//--------------------------------------
//  Notifier
//--------------------------------------
class NotifierTestSuite : public CxxTest::TestSuite, public Facade
{
public:
    void setUp()
    {
        this->notifier = new Notifier();
        this->key = "testNotifierMultitonKey";
    }
    // here are some helper methods
    // override to intercept notification
    void sendNotification(std::string name, IBody* body, std::string type)
    {
        this->notification = new Notification(name, body, type);
    }
    void testCanInitializeNotifier()
    {
        this->notifier->initializeNotifier(this->key);
        TS_ASSERT_EQUALS(this->notifier->getMultitonKey(), this->key);
    }

    void canSendNotificationThroughFacade()
    {
        //TS_ASSERT_EQUALS()
    }

    Notifier* notifier;
    Notification* notification;
    std::string key;
};
//--------------------------------------
//  Observer
//--------------------------------------
// TODO - figure out compare notify contexts, IObserverRestricteds and whatever the hell else...
class InterestedObject
{
public:
    InterestedObject()
    {
        this->memberNotification = new Notification("","");
    }
    void callbackMethod(INotification* notification)
    {
        //std::cout << "InterestedObject::callbackMethod()\n";
        this->memberNotification = notification;
    }
    INotification* memberNotification;
};
class ObserverTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->noteName = "notificationName";
        this->noteType = "notificationType";
        this->notification = new Notification(this->noteName, new IBody(), this->noteType);
        this->contextObject = new InterestedObject();
        this->observer = new Observer<InterestedObject>(&InterestedObject::callbackMethod, this->contextObject);
    }
    void testObserverConstructorShouldSetNotifyMethodAndNotifyContext()
    {
        TS_ASSERT_EQUALS(&*this->observer->getNotifyContext(), &*this->contextObject);
        TS_ASSERT_EQUALS(&InterestedObject::callbackMethod, this->observer->getNotifyMethod());
    }
    void testCanNotifyInterestedObject()
    {
        this->observer->notifyObserver(this->notification);
        TS_ASSERT_EQUALS(this->contextObject->memberNotification->getName(), this->noteName);
    }
    void testCanCompareContexts()
    {
        InterestedObject* newInterestedObject = new InterestedObject();
        TS_ASSERT(! this->observer->compareNotifyContext((unsigned int) &*newInterestedObject));
        TS_ASSERT(this->observer->compareNotifyContext((unsigned int) &*this->contextObject));
    }
private:
    std::string noteName;
    std::string noteType;
    INotification* notification;
    InterestedObject* contextObject;
    Observer<InterestedObject>* observer;
};
//--------------------------------------
//  Proxy
//--------------------------------------
class ProxyTestClass : public Proxy<bool>
{
public:
    ProxyTestClass(bool data) : Proxy<bool>(data)
    {
    }
    void onRegister()
    {
        this->setData(true);
    }
private:
    bool calledRegister;
};
class ProxyTestSuite : public CxxTest::TestSuite
{
public:
    void testConstructorCanInitializeTemplatedData()
    {
        this->proxy = new ProxyTestClass(true);
        TS_ASSERT(this->proxy->getData());
    }
    void testRegisterCallsDerivedClassMember()
    {
        this->proxy = new ProxyTestClass(false);
        TS_ASSERT(! this->proxy->getData());
        this->proxy->onRegister();
        TS_ASSERT(this->proxy->getData());
    }
private:
    Proxy<bool>* proxy;
};
//--------------------------------------
//  Mediator
//--------------------------------------
class MediatorTestClass : public Mediator<int>
{
public:
    MediatorTestClass(std::string name, int number) : Mediator<int>(name, number)
    {
        this->notifiedLastBy = 0;
    }
    void onRegister()
    {}
    void onRemove()
    {}
    std::vector<std::string> listNotificationInterests()
    {
        std::vector<std::string> interests;
        interests.push_back("interest1");
        interests.push_back("interest2");
        interests.push_back("interest3");
        interests.push_back("interest4");
        return interests;
    }
    void handleNotification(INotification* notification)
    {
        std::string name = notification->getName();
        std::string type = notification->getType();
        
        switch(name)
        {
            case "interest1":
                this->notifiedLastBy = 1;
                break;
                
            case "interest2":
                this->notifiedLastBy = 2;
                break;
            case "interest3":
                this->notifiedLastBy = 3;
                break;
            case "interest4":
                this->notifiedLastBy = 4;
                break;
                
            default:
                this->notifiedLastBy = 0;
                
        }
    }
    int notifiedLastBy;
};
class MediatorTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->name = "IBodyMediator";
        this->number = 5;
    }
    void testConstructorSetsNameAndViewComponent()
    {
        this->mediator = new MediatorTestClass(this->name, this->number);
        TS_ASSERT_EQUALS(this->mediator->getName(), this->name);
        TS_ASSERT_EQUALS(this->mediator->getViewComponent(), this->number);
    }
    void testCanGetNotificationInterests()
    {
        IMediatorRestricted* medPtr = this->mediator;
        std::vector<std::string> interests = medPtr->listNotificationInterests();
        TS_ASSERT_EQUALS(interests.size(), (size_t) 4);
    }
private:
    std::string name;
    int number;
    MediatorTestClass* mediator;
};
//--------------------------------------
//  View
//--------------------------------------
class ViewTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        // setup view
        this->key = "ViewTestSuiteKey";
        this->view = View::getInstance(this->key);
        // setup observer
        this->noteName = this->key + "_notificationName";
        this->noteType = this->key + "_notificationType";
        this->notification = new Notification(this->noteName, new IBody(), this->noteType);
        this->contextObject = new InterestedObject();
        this->observer = new Observer<InterestedObject>(&InterestedObject::callbackMethod, this->contextObject);
        this->viewComponent = 666;
        this->mediatorName = this->key + "_mediator";
        this->mediator = new MediatorTestClass(this->mediatorName, this->viewComponent);
    }
    void testMultitonKeyIsSet()
    {
        TS_ASSERT_EQUALS(this->getView()->getMultitonKey(), this->key);
    }
    void testCanRegisterAndNotifyAndRemoveObserver()
    {
        this->getView()->registerObserver(this->noteName, this->observer);
        this->getView()->notifyObservers(this->notification);
        TS_ASSERT_EQUALS(this->contextObject->memberNotification->getName(), this->noteName);
        this->getView()->removeObserver(this->noteName, (unsigned int) &*this->contextObject);
        this->contextObject->memberNotification = new Notification("not_" + this->noteName, "not_" + this->noteType);
        // calling notifyObservers should not reset the name of the contextObject's memberNotification
        this->getView()->notifyObservers(this->notification);
        TS_ASSERT_DIFFERS(this->contextObject->memberNotification->getName(), this->noteName);
    }
    void testCanRegisterAndRetrieveMediator()
    {
        this->view->registerMediator(this->mediator);
        TS_ASSERT(this->view->hasMediator(this->mediatorName));
        IMediatorRestricted* mediatorRet = this->view->retrieveMediator(this->mediatorName);
        TS_ASSERT_EQUALS(&*this->mediator, &*mediatorRet);
        this->view->removeMediator(this->mediatorName);
        TS_ASSERT(this->view->hasMediator(this->mediatorName) == false);
    }
    void testRegisteredMediatorRecievesNotification()
    {
        this->view->registerMediator(this->mediator);
        this->view->notifyObservers()
    }
private:
    std::string key;
    IView* view;

    std::string noteName;
    std::string noteType;
    INotification* notification;
    InterestedObject* contextObject;
    IObserverRestricted* observer;
    int viewComponent;
    std::string mediatorName;
    IMediatorRestricted* mediator;

    View* getView()
    {
        return dynamic_cast<View*>(this->view);
    }
};
//--------------------------------------
//  Controller
//--------------------------------------
class ControllerTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->key = "ControllerTestSuiteKey";
        this->controller = Controller::getInstance(this->key);
    }
    void testCanGetControllerInstance()
    {
        Controller* contPtr = this->getController();
        TS_ASSERT_EQUALS(&*contPtr, &*this->controller);
        TS_ASSERT_EQUALS(contPtr->getMultitonKey(), this->key);
    }

private:
    Controller* getController()
    {
        return dynamic_cast<Controller*>( Controller::getInstance(this->key) );
    }
    std::string key;
    IController* controller;
};
//--------------------------------------
//  Facade
//--------------------------------------
class FacadeTestSuite : public CxxTest::TestSuite
{

};
#endif	/* _PMVCARCHTESTSUITE_H */