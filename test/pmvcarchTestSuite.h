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
#include <stdint.h>

// cxxtest
#include <cxxtest/TestSuite.h>
// Base classes of pmvcpp
#include "pmvcpp.h"

using namespace PureMVC;

//--------------------------------------
//  Patterns
//--------------------------------------
class MultitonTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateInstances()
    {
        int* single_1 = Multiton<int>::instance();
        int* single_2 = Multiton<int>::instance();
        int* single_3 = Multiton<int>::instance("instance3");
        TS_ASSERT_EQUALS(&*single_1, &*single_2);
        TS_ASSERT_DIFFERS(&*single_1, &*single_3);
    }
    void testNumberInstances()
    {
        Multiton<int>::clear();
        TS_ASSERT_EQUALS(Multiton<int>::size(), (size_t) 0);
        Multiton<int>::instance();
        TS_ASSERT_EQUALS(Multiton<int>::size(), (size_t) 1);
        Multiton<int>::instance();
        TS_ASSERT_EQUALS(Multiton<int>::size(), (size_t) 1);
        Multiton<int>::instance("new instance");
        TS_ASSERT_EQUALS(Multiton<int>::size(), (size_t) 2);
    }
};
//--------------------------------------
//  Notification
//--------------------------------------
class NotificationTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->name = 666;
        this->body = 93737645;
        this->type = 777;
        this->notification = new Notification(this->name, (void*) &this->body, this->type);
    }
    void testConstructorSets_name_type()
    {
        TS_ASSERT_EQUALS(this->notification->getName(), this->name);
        TS_ASSERT_EQUALS(this->notification->getType(), this->type);
        int castBody = *((int*) this->notification->getBody());
        TS_ASSERT_EQUALS(castBody, this->body);
    }
private:
    Notification* notification;
    int name;
    int type;
    int body;
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
        this->macroTestClass->execute(new Notification(666, 777));
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 3);
    }
private:
    MacroTestClass* macroTestClass;
};
//--------------------------------------
//  Notifier
//--------------------------------------
class NotifierTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->notifier = new Notifier();
        this->key = "NotifierTestSuiteMultitonKey";
        this->noteName = 666;
        this->facade = Facade::getInstance(this->key);
        this->getFacade()->registerCommand<MacroTestClass>(this->noteName);
        SimpleTestClass::executions = 0;
        this->notifier->initializeNotifier(this->key);
    }
    void tearDown()
    {
        //Facade::removeCore(this->key);
    }
    void testCanInitializeNotifier()
    {
        TS_ASSERT_EQUALS(this->notifier->getMultitonKey(), this->key);
    }
    void testCanSendNotification()
    {
        TS_ASSERT(Multiton<View>::exists(this->key));
        TS_ASSERT(this->facade->hasCommand(this->noteName));
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 0);
        this->notifier->sendNotification(this->noteName);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 3);
    }

private:
    Notifier* notifier;
    Notification* notification;
    IFacade* facade;
    std::string key;
    int noteName;

    Facade* getFacade()
    {
        if(Multiton<Facade>::exists(this->key))
            return Multiton<Facade>::instance(this->key);
        else
            return 0;
    }
};
//--------------------------------------
//  Observer
//--------------------------------------
class InterestedObject
{
public:
    InterestedObject()
    {
        this->memberNotification = new Notification(999,101010);
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
        this->noteName = 666;
        this->noteType = 777;
        this->notification = new Notification(this->noteName, this->noteType);
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
        TS_ASSERT(! this->observer->compareNotifyContext((intptr_t) &*newInterestedObject));
        TS_ASSERT(this->observer->compareNotifyContext((intptr_t) &*this->contextObject));
    }
private:
    int noteName;
    int noteType;
    INotification* notification;
    InterestedObject* contextObject;
    Observer<InterestedObject>* observer;
};
//--------------------------------------
//  Proxy
//--------------------------------------
class ProxyTestClass : public Proxy
{
public:
    bool registered;
    bool removed;
    
    ProxyTestClass(void* data) : Proxy(data)
    {
        this->registered = false;
        this->removed = false;
    }
    ProxyTestClass(std::string name) : Proxy(name)
    {
        this->registered = false;
        this->removed = false;
    }
    ProxyTestClass(std::string name, void* data) : Proxy(name, data)
    {
        this->registered = false;
        this->removed = false;
    }
    void onRegister()
    {
        this->ones = 111;
        this->setData(&this->ones);
        this->registered = true;
    }
    void onRemove()
    {
        this->removed = true;
    }
private:
    bool calledRegister;
    int ones;
};
class ProxyTestSuite : public CxxTest::TestSuite
{
public:
    void testConstructorCanInitializeData()
    {
        int twos = 222;
        this->proxy = new ProxyTestClass(&twos);
        TS_ASSERT_EQUALS(twos, *(int*) this->proxy->getData());
    }
    void testCanSetAndGetData()
    {
        struct data
        {
            std::string name;
            int id;
        };
        struct data xyz;
        xyz.name = "xyz has a name";
        xyz.id = 666;

        this->proxy->setData(&xyz);
        struct data pyt = *(data*) this->proxy->getData();
        TS_ASSERT_EQUALS(xyz.name, pyt.name);
        struct data sss;
        sss.name = "blah";
        sss.id  = 86;
        this->proxy->setData(&sss);
        pyt = *(data*) this->proxy->getData();
        TS_ASSERT_EQUALS(sss.name, pyt.name);
    }
    void testRegisterCallsDerivedClassMember()
    {
        int threes = 333;
        this->proxy = new ProxyTestClass(&threes);
        TS_ASSERT_EQUALS(*(int*) this->proxy->getData(), threes);
        this->proxy->onRegister();
        TS_ASSERT_DIFFERS(*(int*) this->proxy->getData(), threes); // should be 111
    }
private:
    Proxy* proxy;
};
//--------------------------------------
//  Mediator
//--------------------------------------
class MediatorTestClass : public Mediator
{
public:
    MediatorTestClass(std::string name, void* number) : Mediator(name, number)
    {
        this->notifiedLastBy = 0;
        this->registered = false;
        this->removed = false;
    }
    void onRegister()
    {
        this->registered = true;
    }
    void onRemove()
    {
        this->removed = true;
    }
    std::vector<int> listNotificationInterests()
    {
        std::vector<int> interests;
        interests.push_back(1);
        interests.push_back(2);
        interests.push_back(3);
        interests.push_back(4);
        return interests;
    }
    void handleNotification(INotification* notification)
    {
        int name = notification->getName();
        int type = notification->getType();

        switch(name)
        {
            case 1:
                this->notifiedLastBy = 1;
                break;
            case 2:
                this->notifiedLastBy = 2;
                break;
            case 3:
                this->notifiedLastBy = 3;
                break;
            case 4:
                this->notifiedLastBy = 4;
                break;
            default:
                this->notifiedLastBy = 0;
        }
    }
    // converts our void* viewComponent to the number it is storing
    int getNumber()
    {
        return *((int*) this->getViewComponent());
    }
    int notifiedLastBy;
    bool registered;
    bool removed;
};
class MediatorTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->name = "MediatorTestSuite";
        this->number = 5;
    }
    void testConstructorSetsNameAndViewComponent()
    {
        this->mediator = new MediatorTestClass(this->name, &this->number);
        TS_ASSERT_EQUALS(this->mediator->getName(), this->name);
        TS_ASSERT_EQUALS(this->mediator->getNumber(), this->number);
    }
    void testCanGetNotificationInterests()
    {
        IMediator* medPtr = this->mediator;
        std::vector<int> interests = medPtr->listNotificationInterests();
        TS_ASSERT_EQUALS(interests.size(), (size_t) 4);
    }
    void testViewComponentPointsToOriginalMemoryAddress()
    {
        // make a number
        int number = 98765168;
        // copy the number
        int originalNumber = number;
        // store the number
        this->mediator->setViewComponent(&number);
        // change the number
        number = 5;
        // retrieve the stored number
        int storedNumber = *(int*)this->mediator->getViewComponent();
        // did the stored number change with the first?
        TS_ASSERT_DIFFERS(originalNumber, storedNumber);
        TS_ASSERT_EQUALS(number, storedNumber);
        // store the mediator for the next test
        this->storedMediator = this->mediator;
    }
    void testViewComponentPersistsAfterScope()
    {
        int number = 5;
        int storedNumber = *(int*)this->storedMediator->getViewComponent();
        TS_ASSERT_EQUALS(number, storedNumber);
    }
private:
    std::string name;
    int number;
    MediatorTestClass* mediator;
    MediatorTestClass* storedMediator;
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
        this->noteName = 666;
        this->noteType = 777;
        this->notification = new Notification(this->noteName, this->noteType);
        this->contextObject = new InterestedObject();
        this->observer = new Observer<InterestedObject>(&InterestedObject::callbackMethod, this->contextObject);
        this->viewComponent = 888;
        this->mediatorName = this->key + "_mediator";
        this->mediator = new MediatorTestClass(this->mediatorName, &this->viewComponent);
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
        this->getView()->removeObserver(this->noteName, (intptr_t) &*this->contextObject);
        this->contextObject->memberNotification = new Notification(1 + this->noteName, 1 + this->noteType);
        // calling notifyObservers should not reset the name of the contextObject's memberNotification
        this->getView()->notifyObservers(this->notification);
        TS_ASSERT_DIFFERS(this->contextObject->memberNotification->getName(), this->noteName);
    }
    void testCanRegisterAndRetrieveMediator()
    {
        this->view->registerMediator(this->mediator);
        TS_ASSERT(this->view->hasMediator(this->mediatorName));
        TS_ASSERT(this->getMediator()->registered);
        IMediator* mediatorRet = this->view->retrieveMediator(this->mediatorName);
        TS_ASSERT_EQUALS(&*this->mediator, &*mediatorRet);
        this->view->removeMediator(this->mediatorName);
        TS_ASSERT(this->view->hasMediator(this->mediatorName) == false);
    }
    void testRegisteredMediatorRecievesNotificationAndRemovingMediatorRemovesObservers()
    {
        this->view->registerMediator(this->mediator);
        this->view->notifyObservers(new Notification(4, this->noteType));
        TS_ASSERT_EQUALS(this->getMediator()->notifiedLastBy, 4);
        this->view->removeMediator(this->mediatorName);
        this->view->notifyObservers(new Notification(3, this->noteType));
        TS_ASSERT_EQUALS(this->getMediator()->notifiedLastBy, 4);
        TS_ASSERT(this->getMediator()->removed);
    }
    void testCanRetrieveMediator()
    {
        this->view->registerMediator(this->mediator);
        IMediator* mediator = this->view->retrieveMediator(this->mediatorName);
        TS_ASSERT_EQUALS(&*mediator, &*this->mediator);
    }
    void testCanRemoveView()
    {
        TS_ASSERT(Multiton<View>::exists(this->key));
        View::removeView(this->key);
        TS_ASSERT(! Multiton<View>::exists(this->key));
    }
private:
    std::string key;
    IView* view;

    int noteName;
    int noteType;
    INotification* notification;
    InterestedObject* contextObject;
    IObserverRestricted* observer;
    int viewComponent;
    std::string mediatorName;
    IMediator* mediator;

    View* getView()
    {
        return dynamic_cast<View*>(this->view);
    }
    MediatorTestClass* getMediator()
    {
        return dynamic_cast<MediatorTestClass*>(this->mediator);
    }
};
//--------------------------------------
//  Model
//--------------------------------------
class ModelTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->key = "ModelTestSuiteMultitonKey";
        this->proxyName = this->key + "_proxy";
        this->model = Model::getInstance(this->key);
        bool truth = true;
        this->proxy = new ProxyTestClass(this->proxyName, &truth);
    }
    void testMultitonKeyIsSet()
    {
        TS_ASSERT_EQUALS(this->model->getMultitonKey(), this->key);
    }
    void testCanRegisterAndRetrieveAndRemoveProxy()
    {
        TS_ASSERT(! this->model->hasProxy(this->proxyName));
        this->model->registerProxy(this->proxy);
        TS_ASSERT(this->model->hasProxy(this->proxyName));
        TS_ASSERT(this->getProxy()->registered);
        
        IProxy* proxyPtr = this->model->retrieveProxy(this->proxyName);
        TS_ASSERT_EQUALS(&*this->proxy, &*proxyPtr);

        proxyPtr = this->model->removeProxy(this->proxyName);
        TS_ASSERT_EQUALS(&*proxyPtr, &*this->proxy);
        TS_ASSERT(! this->model->hasProxy(this->proxyName));
        TS_ASSERT(this->getProxy()->removed);
    }
    void testCanRemoveModel()
    {
        TS_ASSERT(Multiton<Model>::exists(this->key));
        Model::removeModel(this->key);
        TS_ASSERT(! Multiton<Model>::exists(this->key));
    }
private:
    IModel* model;
    std::string key;

    IProxy* proxy;
    int data;
    std::string proxyName;

    Model* getModel()
    {
        return dynamic_cast<Model*>(this->model);
    }
    ProxyTestClass* getProxy()
    {
        return dynamic_cast<ProxyTestClass*>(this->proxy);
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
        this->command = new MacroTestClass();
        this->noteName = 666;
        this->noteType = 777;
        this->notification = new Notification(this->noteName, this->noteType);
        this->getController()->registerCommand<MacroTestClass>(this->noteName);
        SimpleTestClass::executions = 0;
    }
    void testCanGetControllerInstance()
    {
        Controller* contPtr = this->getController();
        TS_ASSERT_EQUALS(&*contPtr, &*this->controller);
        TS_ASSERT_EQUALS(contPtr->getMultitonKey(), this->key);
    }
    void testMultitonKeyIsSet()
    {
        TS_ASSERT_EQUALS(this->controller->getMultitonKey(), this->key);
    }
    void testCanRegisterCommand()
    {
        TS_ASSERT(this->controller->hasCommand(this->noteName));
    }
    void testCanExecuteCommandAndExecuteThroughNotification()
    {
        this->getController()->executeCommand<MacroTestClass>(this->notification);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 3);
        this->getView()->notifyObservers(this->notification);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 6);
    }
    void testCanRemoveCommand()
    {
        this->controller->removeCommand(this->noteName);
        this->getView()->notifyObservers(this->notification);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 0);
        this->getController()->executeCommand<MacroTestClass>(this->notification);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 0);
    }
    void testCanRemoveController()
    {
        TS_ASSERT(Multiton<Controller>::exists(this->key));
        Controller::removeController(this->key);
        TS_ASSERT(! Multiton<Controller>::exists(this->key));
    }

private:
    std::string key;
    int noteName;
    int noteType;
    IController* controller;
    ICommand* command;
    INotification* notification;

    Controller* getController()
    {
        return dynamic_cast<Controller*>( Controller::getInstance(this->key) );
    }
    View* getView()
    {
        if(Multiton<View>::exists(this->key))
            return Multiton<View>::instance(this->key);
        else
            return (View*) 0;
    }
};
//--------------------------------------
//  Facade
//--------------------------------------
class FacadeTestClass : public Facade
{

};
class FacadeTestSuite : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->key = "FacadeTestSuiteMultitonKey";
        this->noteName = 444;
        this->noteBody = 777;
        this->noteType = 555;
        this->proxyName= this->key + "_proxy";
        this->mediatorName = this->key + "_mediator";
        this->proxy = new ProxyTestClass(this->proxyName);
        this->mediator = new MediatorTestClass(this->mediatorName, &this->noteBody);
        this->facade = Facade::getInstance(this->key);
        SimpleTestClass::executions = 0;
    }
    void testMultitonKeysAreSet()
    {
        TS_ASSERT_EQUALS(this->facade->getMultitonKey(), this->key);
        TS_ASSERT_EQUALS(this->get<Model>()->getMultitonKey(), this->key);
        TS_ASSERT_EQUALS(this->get<View>()->getMultitonKey(), this->key);
        TS_ASSERT_EQUALS(this->get<Controller>()->getMultitonKey(), this->key);
    }
    void testCanRegisterAndRemoveCommand()
    {
        TS_ASSERT(!  this->facade->hasCommand(this->noteName));
        this->get<Facade>()->registerCommand<MacroTestClass>(this->noteName);
        TS_ASSERT(this->facade->hasCommand(this->noteName));
        this->facade->removeCommand(this->noteName);
        TS_ASSERT(! this->facade->hasCommand(this->noteName));
    }
    void testCanRegisterAndRetrieveAndRemoveProxy()
    {
        TS_ASSERT(! this->facade->hasProxy(this->proxyName));
        this->facade->registerProxy(this->proxy);
        TS_ASSERT(this->facade->hasProxy(this->proxyName));
        IProxy* proxyPtr = this->facade->retrieveProxy(this->proxyName);
        TS_ASSERT_EQUALS(&*proxyPtr, &*this->proxy);
        this->facade->removeProxy(this->proxyName);
        TS_ASSERT(! this->facade->hasProxy(this->proxyName));
    }
    void testCanRegisterAndRetrieveAndRemoveMediator()
    {
        TS_ASSERT(! this->facade->hasMediator(this->mediatorName));
        this->facade->registerMediator(this->mediator);
        TS_ASSERT(this->facade->hasMediator(this->mediatorName));
        IMediator* medPtr = this->facade->retrieveMediator(this->mediatorName);
        TS_ASSERT_EQUALS(&*medPtr, &*this->mediator);
        this->facade->removeMediator(this->mediatorName);
        TS_ASSERT(! this->facade->hasMediator(this->mediatorName));
    }
    void testCanSendNotificationToCommand()
    {
        this->get<Facade>()->registerCommand<MacroTestClass>(this->noteName);
        this->facade->sendNotification(this->noteName);
        TS_ASSERT_EQUALS(SimpleTestClass::executions, 3);
    }
    void testCanSendNotificationToMediator()
    {
        this->facade->registerMediator(this->mediator);
        this->facade->sendNotification(2);
        TS_ASSERT_EQUALS(dynamic_cast<MediatorTestClass*>(this->mediator)->notifiedLastBy, 2);
        this->facade->removeMediator(this->mediatorName);
    }
    void testCanRemoveCore()
    {
        TS_ASSERT(Facade::hasCore(this->key));
        Facade::removeCore(this->key);
        TS_ASSERT(! Multiton<Model>::exists(this->key));
        TS_ASSERT(! Multiton<View>::exists(this->key));
        TS_ASSERT(! Multiton<Controller>::exists(this->key));
        TS_ASSERT(! Multiton<Facade>::exists(this->key));
        TS_ASSERT(! Facade::hasCore(this->key));
    }
private:
    std::string key;
    int noteName;
    int noteType;
    int noteBody;
    std::string proxyName;
    std::string mediatorName;
    IProxy* proxy;
    IMediator* mediator;
    IFacade* facade;

    template<class T>
    T* get()
    {
        if(Multiton<T>::exists(this->key))
            return Multiton<T>::instance(this->key);
        else
            return (T*) 0;
    };
};
#endif	/* _PMVCARCHTESTSUITE_H */