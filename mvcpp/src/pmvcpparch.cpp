/**
 *	Implementation file for the pmvcpp architecture.
 *
 *	@author	Schell Scivally
 */
#include <iostream>
#include <stdint.h>
#include "pmvcpparch.h"
#include "pmvcppexp.h"
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
Notification::Notification(std::string name, IBody* body, std::string type)
{
    this->name = name;
    this->setBody(body);
    this->setType(type);
}
Notification::Notification(std::string name, IBody* body)
{
    this->name = name;
    this->setBody(body);
}
Notification::Notification(std::string name, std::string type)
{
    this->name = name;
    this->setType(type);
}
Notification::Notification(std::string name)
{
    this->name = name;
}
std::string Notification::getName()
{
    return this->name;
}
void Notification::setBody( IBody* body )
{
    this->body = body;
}
IBody* Notification::getBody()
{
    return this->body;
}
void Notification::setType( std::string type )
{
    this->type = type;
}
std::string Notification::getType()
{
    return this->type;
}
//--------------------------------------
//  Notifier
//--------------------------------------
void Notifier::sendNotification( std::string notificationName, IBody* body, std::string type)
{
    this->getFacade()->sendNotification(notificationName, body, type);
}
void Notifier::sendNotification( std::string notificationName, std::string type )
{
    this->getFacade()->sendNotification(notificationName, type);
}
void Notifier::sendNotification( std::string notificationName, IBody* body )
{
    this->getFacade()->sendNotification(notificationName, body);
}
void Notifier::sendNotification( std::string notificationName )
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
// defined in header
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
void Model::registerProxy( IProxyRestricted* proxy )
{
    proxy->initializeNotifier(this->getMultitonKey());
    if(! this->hasProxy(proxy->getProxyName()))
    {
        this->proxyMap[proxy->getProxyName()] = proxy;
        proxy->onRegister();
    }
}
IProxyRestricted* Model::retrieveProxy( std::string proxyName )
{
    return this->proxyMap[proxyName];
}
bool Model::hasProxy( std::string proxyName )
{
    return ! (this->proxyMap.find(proxyName) == this->proxyMap.end());
}
IProxyRestricted* Model::removeProxy( std::string proxyName )
{
    //std::cout << "removeProxy()\n";
    // if this proxy has not been registered, return a null pointer
    if(! this->hasProxy(proxyName))
        return (IProxyRestricted*) 0;

    // get the proxy
    IProxyRestricted* proxy = this->proxyMap[proxyName];
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
void View::registerObserver ( std::string notificationName, IObserverRestricted* observer )
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
    std::string noteName = notification->getName();
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
void View::removeObserver( std::string notificationName, intptr_t contextAddress )
{
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
                observers.erase(it);
                break;
            }
        }

        if(observers.size() == (size_t) 0)
           this->observerMap.erase(notificationName);
    }
}
void View::registerMediator( IMediatorRestricted* mediator )
{
    // if this mediator has already been registered, abort
    if(this->hasMediator(mediator->getMediatorName()))
        return;

    mediator->initializeNotifier(this->getMultitonKey());
    // register the mediator by name
    this->mediatorMap[mediator->getMediatorName()] = mediator;
    // get the mediator's notification interests
    std::vector<std::string> interests = mediator->listNotificationInterests();
    if(interests.size() > (size_t) 0)
    {
        // create an observer functor for the mediator
        Observer<IMediatorRestricted>* observer = new Observer<IMediatorRestricted>(&IMediatorRestricted::handleNotification, mediator);
        // register this observer for every notification the mediator is interested in
        std::vector<std::string>::iterator it;
        for(it = interests.begin(); it != interests.end(); it++)
        {
            this->registerObserver((*it), observer);
        }
    }
    // alert the mediator that it has been registered
    mediator->onRegister();
}
IMediatorRestricted* View::retrieveMediator( std::string mediatorName )
{
    return this->mediatorMap[mediatorName];
}
IMediatorRestricted* View::removeMediator( std::string mediatorName )
{
    // if the requested mediator has not been registered, return a null pointer
    if(! this->hasMediator(mediatorName))
        return (IMediatorRestricted*) 0;
    // get the mediator
    IMediatorRestricted* mediator = this->mediatorMap[mediatorName];
    // get the mediators interests
    std::vector<std::string> interests = mediator->listNotificationInterests();
    if(interests.size() > (size_t) 0)
    {
        std::vector<std::string>::iterator it;
        for (it = interests.begin(); it != interests.end(); it++) 
        {
            // remove the mediator's observer functor listed for this notification
            this->removeObserver((*it), (intptr_t) &*mediator);
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
bool View::existsObserversInterestedIn(std::string notificationName)
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
bool Controller::hasCommand( std::string notificationName )
{
    return ! (this->commandMap.find(notificationName) == this->commandMap.end());
}
void Controller::removeCommand( std::string notificationName )
{
    if(this->hasCommand(notificationName))
    {
        // remove observer from view
        this->view->removeObserver(notificationName, (intptr_t) &*this);
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
Facade::Facade() : model(0), view(0), controller(0)
{
}
IFacade* Facade::getInstance(std::string key)
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
    if(this->controller != (IController*) 0)
        return;
    this->controller = Controller::getInstance(this->getMultitonKey());
}
void Facade::initializeController()
{
    // if it's been initialized, abort
    if(this->model != (IModel*) 0)
        return;
    this->model = Model::getInstance(this->getMultitonKey());
}
void Facade::initializeView()
{
    // if it's been initialized, abort
    if(this->view != (IView*) 0)
        return;
    this->view = View::getInstance(this->getMultitonKey());
}
void Facade::removeCommand( std::string notificationName )
{
    this->controller->removeCommand(notificationName);
}
bool Facade::hasCommand( std::string notificationName )
{
    return this->controller->hasCommand(notificationName);
}
void Facade::registerProxy( IProxyRestricted* proxy )
{
    this->model->registerProxy(proxy);
}
IProxyRestricted* Facade::retrieveProxy( std::string proxyName )
{
    return this->model->retrieveProxy(proxyName);
}
IProxyRestricted* Facade::removeProxy ( std::string proxyName )
{
    return this->model->removeProxy(proxyName);
}
bool Facade::hasProxy( std::string proxyName )
{
    return this->model->hasProxy(proxyName);
}
void Facade::registerMediator( IMediatorRestricted* mediator )
{
    if(this->view == (IView*) 0)
        return;
    this->view->registerMediator(mediator);
}
IMediatorRestricted* Facade::retrieveMediator( std::string mediatorName )
{
    return this->view->retrieveMediator(mediatorName);
}
IMediatorRestricted* Facade::removeMediator( std::string mediatorName )
{
    return this->view->removeMediator(mediatorName);
}
bool Facade::hasMediator( std::string mediatorName )
{
    return this->view->hasMediator(mediatorName);
}
void Facade::sendNotification( std::string notificationName, IBody* body, std::string type)
{
    this->notifyObservers(new Notification(notificationName, body, type));
}
void Facade::sendNotification( std::string notificationName, std::string type )
{
    this->notifyObservers(new Notification(notificationName, type));
}
void Facade::sendNotification( std::string notificationName, IBody* body )
{
    this->notifyObservers(new Notification(notificationName, body));
}
void Facade::sendNotification( std::string notificationName )
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