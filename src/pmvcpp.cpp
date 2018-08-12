/* 
 * File:   pmvcpp.cpp - implementation for the PureMVC++ software architecture.
 * Author: Schell Scivally - civiliansoftware.com
 *
 * Created on December 17, 2009, 12:56 PM
 * PureMVC++ - Copyright(c) 2009 Schell Scivally Enterprise, some rights reserved.
 * Your reuse is governed by the Creative Commons Attribution 3.0 United States License
 * 
 */

#include <iostream>
#include <stdint.h>
#include "pmvcpp.h"

using namespace PureMVC;
//--------------------------------------
//  MultitonKeyHeir
//--------------------------------------
void MultitonKeyHeir::setMultitonKey(std::string key)
{
    this->_multitonKey = key;
}

std::string MultitonKeyHeir::getMultitonKey()
{
    return this->_multitonKey;
}
//--------------------------------------
//  Notification
//--------------------------------------
Notification::Notification(int name, void* body, int notificationType)
{
    this->name = name;
    this->setBody(body);
    this->setType(notificationType);
}
Notification::Notification(int name, void* body)
{
    this->name = name;
    this->setBody(body);
}
Notification::Notification(int name, int notificationType)
{
    this->name = name;
    this->setType(notificationType);
}
Notification::Notification(int name)
{
    this->name = name;
}
int Notification::getName()
{
    return this->name;
}
void Notification::setBody( void* body )
{
    this->body = body;
}
void* Notification::getBody()
{
    return this->body;
}
void Notification::setType( int notificationType )
{
    this->type = notificationType;
}
int Notification::getType()
{
    return this->type;
}
//--------------------------------------
//  Notifier
//--------------------------------------
void Notifier::sendNotification( int notificationName, void* body, int notificationType)
{
    this->getFacade()->sendNotification(notificationName, body, notificationType);
}
void Notifier::sendNotification( int notificationName, int notificationType )
{
    this->getFacade()->sendNotification(notificationName, notificationType);
}
void Notifier::sendNotification( int notificationName, void* body )
{
    this->getFacade()->sendNotification(notificationName, body);
}
void Notifier::sendNotification( int notificationName )
{
    this->getFacade()->sendNotification(notificationName);
}
void Notifier::initializeNotifier(std::string key)
{
    this->setMultitonKey(key);
}
IFacade* Notifier::getFacade()
{
    return Multiton<Facade>::instance(this->getMultitonKey());
}
//--------------------------------------
//  SimpleCommand
//--------------------------------------
// nothing to define!
//--------------------------------------
//  MacroCommand
//--------------------------------------
MacroCommand::MacroCommand()
{
}
void MacroCommand::addSubCommand(ICommand* command)
{
    this->subCommands.push_back(command);
}
void MacroCommand::execute(INotification* notification)
{
    std::vector<ICommand*>::iterator it;
    for(it = this->subCommands.begin(); it != this->subCommands.end(); it++)
    {
        (*it)->execute(notification);
    }
}
//--------------------------------------
//  Observer
//--------------------------------------
// defined in header
//--------------------------------------
//  Proxy
//--------------------------------------
Proxy::Proxy()
{
}
Proxy::Proxy(std::string proxyName, void* data)
{
    this->proxyName = proxyName;
    this->setData(&data);
}
Proxy::Proxy(std::string proxyName)
{
    this->proxyName = proxyName;
}
Proxy::Proxy(void* data)
{
    this->data = data;
}
std::string Proxy::getProxyName()
{
    return this->proxyName;
}
void Proxy::setData( void* data )
{
    this->data = data;
}
void* Proxy::getData()
{
    return this->data;
}
//--------------------------------------
//  Mediator
//--------------------------------------
Mediator::Mediator( std::string mediatorName, void* viewComponent )
{
    this->mediatorName = mediatorName;
    this->setViewComponent(viewComponent);
}
Mediator::Mediator( std::string mediatorName )
{
    this->mediatorName = mediatorName;
}
Mediator::Mediator( void* viewComponent )
{
    this->setViewComponent(viewComponent);
}
std::string Mediator::getMediatorName()
{
    return this->mediatorName;
}
void Mediator::setViewComponent( void* viewComponent )
{
    this->viewComponent = viewComponent;
}
void* Mediator::getViewComponent()
{
    return this->viewComponent;
}
std::string Mediator::getName()
{
    return this->mediatorName;
}
//--------------------------------------
//  Model
//--------------------------------------
Model::Model()
{}
IModel* Model::getInstance(std::string key)
{
    // if the instance already exists, return it.
    if(Multiton<Model>::exists(key))
        return Multiton<Model>::instance(key);
    // if not, create it and initialize
    Model* modelPtr = Multiton<Model>::instance(key);
    modelPtr->setMultitonKey(key);
    return modelPtr;
}
void Model::registerProxy( IProxy* proxy )
{
    proxy->initializeNotifier(this->getMultitonKey());
    if(! this->hasProxy(proxy->getProxyName()))
    {
        this->proxyMap[proxy->getProxyName()] = proxy;
        proxy->onRegister();
    }
}
IProxy* Model::retrieveProxy( std::string proxyName )
{
    return this->proxyMap[proxyName];
}
bool Model::hasProxy( std::string proxyName )
{
    return ! (this->proxyMap.find(proxyName) == this->proxyMap.end());
}
IProxy* Model::removeProxy( std::string proxyName )
{
    //std::cout << "removeProxy()\n";
    // if this proxy has not been registered, return a null pointer
    if(! this->hasProxy(proxyName))
        return (IProxy*) 0;

    // get the proxy
    IProxy* proxy = this->proxyMap[proxyName];
    // remove the proxy from the map
    this->proxyMap.erase(proxyName);
    // alert the proxy that it's been removed
    proxy->onRemove();

    return proxy;
}
void Model::removeModel( std::string key )
{
    Multiton<Model>::erase(key);
}
//--------------------------------------
//  View
//--------------------------------------
View::View( )
{
}
IView* View::getInstance(std::string key)
{
    // if the instance already exists, simply return it
    if(Multiton<View>::exists(key))
        return Multiton<View>::instance(key);
    // if the instance needs to be created, do so and take
    // care of some initialization
    View* viewPtr = Multiton<View>::instance(key);
    viewPtr->setMultitonKey(key);
    return viewPtr;
}
void View::registerObserver ( int notificationName, IObserverRestricted* observer )
{
    if(! this->existsObserversInterestedIn(notificationName))
    {
        std::vector<IObserverRestricted*> observerVector;
        observerVector.push_back(observer);
        this->observerMap[notificationName] = observerVector;
    }
    else
    {
        this->observerMap[notificationName].push_back(observer);
    }
}
void View::notifyObservers( INotification* notification )
{
    int noteName = notification->getName();
    if(this->existsObserversInterestedIn(noteName))
    {
        // there was some stuff about the reference array changing while
        // running this loop, although i don't see how that could happen
        // until we add threads to this architecture - so i'm keeping
        // it simple here
        std::vector<IObserverRestricted*> observers = this->observerMap[noteName];
        std::vector<IObserverRestricted*>::iterator it;
        for(it = observers.begin(); it != observers.end(); it++)
        {
            (*it)->notifyObserver(notification);
        }
    }
}
IObserverRestricted* View::removeObserver( int notificationName, intptr_t contextAddress )
{
    IObserverRestricted* observer = nullptr;
    if(this->existsObserversInterestedIn(notificationName))
    {
        std::vector<IObserverRestricted*> observers = this->observerMap[notificationName];
        std::vector<IObserverRestricted*>::iterator it;

        for(it = observers.begin(); it != observers.end(); it++)
        {
            // this is tricky because in c++ we can't compare arbitrary types
            // we have to downcast the IObserverRestricteds to their derived classes
            // in order to properly compare them. someone may object to this -
            // i know it's programming taboo - so by all means figure out a
            // better way to do this, however i'm sure  it will
            // involve refactoring the base classes
            if((*it)->compareNotifyContext(contextAddress) == true)
            {
                observer = *it;
                observers.erase(it);
                break;
            }
        }
        
        this->observerMap[notificationName] = observers;

        if(observers.size() == (size_t) 0)
           this->observerMap.erase(notificationName);
    }
    return observer;
}
void View::registerMediator( IMediator* mediator )
{
    // if this mediator has already been registered, abort
    if(this->hasMediator(mediator->getMediatorName()))
        return;

    mediator->initializeNotifier(this->getMultitonKey());
    // register the mediator by name
    this->mediatorMap[mediator->getMediatorName()] = mediator;
    // get the mediator's notification interests
    std::vector<int> interests = mediator->listNotificationInterests();
    if(interests.size() > (size_t) 0)
    {
        // create an observer functor for the mediator
        Observer<IMediator>* observer = new Observer<IMediator>(&IMediator::handleNotification, mediator);
        // register this observer for every notification the mediator is interested in
        for (int i = 0; i < (int) interests.size(); i++)
        {
            this->registerObserver(interests[i], observer);
        }
    }
    // alert the mediator that it has been registered
    mediator->onRegister();
}
IMediator* View::retrieveMediator( std::string mediatorName )
{
    return this->mediatorMap[mediatorName];
}
IMediator* View::removeMediator( std::string mediatorName )
{
    // if the requested mediator has not been registered, return a null pointer
    if(! this->hasMediator(mediatorName))
        return (IMediator*) 0;
    // get the mediator
    IMediator* mediator = this->mediatorMap[mediatorName];
    // get the mediators interests
    std::vector<int> interests = mediator->listNotificationInterests();
    if(interests.size() > (size_t) 0)
    {
        std::vector<std::string>::iterator it;
        for (int i = 0; i < (int) interests.size(); i++)
        {
            // remove the mediator's observer functor listed for this notification
            delete this->removeObserver(interests[i], (intptr_t) &*mediator);
        }
    }
    // remove the mediator from the map
    this->mediatorMap.erase(mediatorName);
    // alert the mediator that it has been removed
    mediator->onRemove();

    return mediator;
}
bool View::hasMediator( std::string mediatorName )
{
    return this->mediatorMap.find(mediatorName) != this->mediatorMap.end();
}
void View::removeView( std::string key )
{
    Multiton<View>::erase(key);
}
bool View::existsObserversInterestedIn(int notificationName)
{
    return this->observerMap.find(notificationName) != this->observerMap.end();
}
//--------------------------------------
//  Controller
//--------------------------------------
Controller::Controller()
{
}
IController* Controller::getInstance(std::string key)
{
    // if the instance already exists, simply return it
    if(Multiton<Controller>::exists(key))
        return Multiton<Controller>::instance(key);
    // if the instance needs to be created, do so and take
    // care of some initialization
    Controller* contPtr = Multiton<Controller>::instance(key);
    contPtr->setMultitonKey(key);
    contPtr->initializeController();
    return contPtr;
}
bool Controller::hasCommand( int notificationName )
{
    return ! (this->commandMap.find(notificationName) == this->commandMap.end());
}
void Controller::removeCommand( int notificationName )
{
    if(this->hasCommand(notificationName))
    {
        // remove observer from view
        delete this->view->removeObserver(notificationName, (intptr_t) &*this);
        // remove null command ptr from map
        this->commandMap.erase(notificationName);
    }
}
void Controller::removeController( std::string key )
{
    Multiton<Controller>::erase(key);
}
void Controller::initializeController( )
{
    this->view = View::getInstance(this->getMultitonKey());
}
//--------------------------------------
//  FACADE
//--------------------------------------
Facade::Facade()
{
	this->model = (IModel*) 0;
	this->view = (IView*) 0;
	this->controller = (IController*) 0;
}
Facade* Facade::getInstance(std::string key)
{
    Facade* facade = Multiton<Facade>::instance(key);
    facade->initializeNotifier(key);
    facade->initializeFacade();
    return facade;
}
void Facade::initializeNotifier(std::string key)
{
    this->setMultitonKey(key);
}
void Facade::initializeFacade()
{
    this->initializeModel();
    this->initializeController();
    this->initializeView();
}
void Facade::initializeModel()
{
    // if it's been initialized, abort
    if(this->model != (IModel*) 0)
        return;
    this->model = Model::getInstance(this->getMultitonKey());
}
void Facade::initializeController()
{
    // if it's been initialized, abort
    if(this->controller != (IController*) 0)
        return;
    this->controller = Controller::getInstance(this->getMultitonKey());
}
void Facade::initializeView()
{
    // if it's been initialized, abort
    if(this->view != (IView*) 0)
        return;
    this->view = View::getInstance(this->getMultitonKey());
}
void Facade::removeCommand( int notificationName )
{
    this->controller->removeCommand(notificationName);
}
bool Facade::hasCommand( int notificationName )
{
    return this->controller->hasCommand(notificationName);
}
void Facade::registerProxy( IProxy* proxy )
{
    this->model->registerProxy(proxy);
}
IProxy* Facade::retrieveProxy( std::string proxyName )
{
    return this->model->retrieveProxy(proxyName);
}
IProxy* Facade::removeProxy ( std::string proxyName )
{
    return this->model->removeProxy(proxyName);
}
bool Facade::hasProxy( std::string proxyName )
{
    return this->model->hasProxy(proxyName);
}
void Facade::registerMediator( IMediator* mediator )
{
    if(this->view == (IView*) 0)
        return;
    this->view->registerMediator(mediator);
}
IMediator* Facade::retrieveMediator( std::string mediatorName )
{
    return this->view->retrieveMediator(mediatorName);
}
IMediator* Facade::removeMediator( std::string mediatorName )
{
    return this->view->removeMediator(mediatorName);
}
bool Facade::hasMediator( std::string mediatorName )
{
    return this->view->hasMediator(mediatorName);
}
void Facade::sendNotification( int notificationName, void* body, int notificationType)
{
    this->notifyObservers(new Notification(notificationName, body, notificationType));
}
void Facade::sendNotification( int notificationName, int notificationType )
{
    this->notifyObservers(new Notification(notificationName, notificationType));
}
void Facade::sendNotification( int notificationName, void* body )
{
    this->notifyObservers(new Notification(notificationName, body));
}
void Facade::sendNotification( int notificationName )
{
    this->notifyObservers(new Notification(notificationName));
}
void Facade::notifyObservers ( INotification* notification )
{
    if(this->view == (IView*) 0)
        return;
    this->view->notifyObservers(notification);
}
bool Facade::hasCore( std::string key )
{
    return Multiton<Facade>::exists(key);
}
void Facade::removeCore( std::string key )
{
    if(! Facade::hasCore(key))
        return;

    Model::removeModel(key);
    View::removeView(key);
    Controller::removeController(key);
    Multiton<Facade>::erase(key);
}
