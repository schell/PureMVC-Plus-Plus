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

/**
 *  An application facade.
 *  Application facade used for testing. Most our application logic
 *  will be somewhere in here.
 */
class ApplicationFacade : public Facade
{
public:
    static ApplicationFacade* instance(std::string key)
    {
        ApplicationFacade* inst = Multiton<ApplicationFacade>::instance(key);
        inst->initializeFacade(key);
        return inst;
    }
    IModel* getModel()
    {
        return this->model;
    }
    IController* getController()
    {
        return this->controller;
    }
    IView* getView()
    {
        return this->view;
    }
    void initializeFacade(std::string key)
    {
        Facade::initializeFacade(key);
    }
};

//--------------------------------------
//  ALL
//--------------------------------------
/**
 *  TODO - Finish implementations
 */
class NotesTestSuite : public CxxTest::TestSuite
{
public:
    void testToDoList()
    {
        TS_WARN("Facade is not fully implemented.");
        TS_WARN("Notifier is not fully implemented.");
        TS_WARN("Model is not fully implemented.");
    }
};
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
//  Observer
//--------------------------------------
class NotificationHandlerClassOne : public INotificationHandler
{
public:
    NotificationHandlerClassOne() : timesHandled(0)
    {
        std::cout << "NotificationHandlerClassOne\n";
    }
    void handleNotification(INotification* notification)
    {
        std::cout << "NotificationHandlerClassOne\n";
        this->note = notification;
    }

    INotification* note;
    int timesHandled;
};
class NotificationHandlerClassTwo : public INotificationHandler
{
public:
    NotificationHandlerClassTwo() : timesHandled(0)
    {
        std::cout << "NotificationHandlerClassTwo\n";
    }
    void handleNotification(INotification* notification)
    {
        std::cout << "NotificationHandlerClassTwo\n";
        this->note = notification;
    }

    INotification* note;
    int timesHandled;
};

class ObserverTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->noteOne = new NotificationHandlerClassOne();
        this->noteTwo = new NotificationHandlerClassTwo();
        this->observerOne = new Observer(&INotificationHandler::handleNotification, (INotificationHandler*) this->noteOne);
        this->observerTwo = new Observer(&INotificationHandler::handleNotification, (INotificationHandler*) this->noteTwo);
    }
private:
    NotificationHandlerClassOne* noteOne;
    NotificationHandlerClassTwo* noteTwo;
    IObserver* observerOne;
    IObserver* observerTwo;
};
//--------------------------------------
//  Facade
//--------------------------------------
class FacadeTestSuite : public CxxTest::TestSuite
{
//public:
//    void setUp()
//    {
//        this->appKey = "testAppFacadeKey";
//        this->appFacade = ApplicationFacade::instance(this->appKey);
//        this->appFacade->initializeFacade(this->appKey);
//    }
//    void tearDown()
//    {
//        Multiton<ApplicationFacade>::clear();
//    }
//    void testMultitonKeySet()
//    {
//        TS_ASSERT_EQUALS(this->appFacade->getMultitonKey(), this->appKey);
//    }
//    void testModelInitialized()
//    {
//        // compare to null ptr
////        TS_TRACE("appFacade model mem address:");
////        TS_TRACE(&*this->appFacade->getModel());
////        TS_TRACE("null IModel* mem address:");
////        TS_TRACE( &*((IModel*) 0) );
//        TS_ASSERT_DIFFERS(this->appFacade->getModel(), (IModel*) 0);
//    }
//    void testControllerInitialized()
//    {
//        // compare to null ptr
////        TS_TRACE("appFacade controller mem address:");
////        TS_TRACE(&*this->appFacade->getController());
////        TS_TRACE("null IController* mem address:");
////        TS_TRACE( &*((IController*) 0) );
//        TS_ASSERT_DIFFERS(this->appFacade->getController(), (IController*) 0);
//    }
//    void testViewInitialized()
//    {
//        // compare to null ptr
////        TS_TRACE("appFacade view mem address:");
////        TS_TRACE(&*this->appFacade->getView());
////        TS_TRACE("null IView* mem address:");
////        TS_TRACE( &*((IView*) 0) );
//        TS_ASSERT_DIFFERS(this->appFacade->getView(), (IView*) 0);
//    }
//    std::string appKey;
//    ApplicationFacade* appFacade;
};
//--------------------------------------
//  Controller
//--------------------------------------
//class ControllerTestSuite : public CxxTest::TestSuite
//{
//public:
//    void setUp()
//    {
//        this->appKey = "testAppFacadeKey_Controller";
//        this->appFacade = ApplicationFacade::instance(this->appKey);
//        this->appFacade->initializeFacade(this->appKey);
//    }
//
//    std::string appKey;
//    ApplicationFacade* appFacade;
//};
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
//  Model
//--------------------------------------
class testModel : public CxxTest::TestSuite
{
public:
//    void setUp()
//    {
//        this->key = "testModelMultitonKey";
//        this->model = new Model(this->key);
//    }
//    void testConstructor_Sets_multitonKey()
//    {
//        this->model = new Model(this->key);
//        TS_ASSERT_EQUALS(this->model->getMultitonKey(), this->key);
//    }
//
//    Model* model;
//    std::string key;
};
#endif	/* _PMVCARCHTESTSUITE_H */