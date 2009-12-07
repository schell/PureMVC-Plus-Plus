/**
 *	Implementation file for the pmvcpp architecture.
 *
 *	@author	Schell Scivally
 */
#include <iostream>
#include "patterns.h"
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

}
void Notifier::sendNotification( std::string notificationName, std::string type )
{

}
void Notifier::sendNotification( std::string notificationName, IBody* body )
{

}
void Notifier::sendNotification( std::string notificationName )
{

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
void SimpleCommand::execute(INotification* notification)
{
    
}
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
//  Model
//--------------------------------------
Model::Model()
{}
void Model::registerProxy( IProxy* proxy )
{}
IProxy* Model::retrieveProxy( std::string proxyName )
{return 0;}
bool Model::hasProxy( std::string proxyName )
{return true;}
IProxy* Model::removeProxy( std::string proxyName )
{return 0;}
void Model::removeModel( std::string key )
{}
void Model::initializeModel(  )
{}
//--------------------------------------
//  View
//--------------------------------------
View::View( )
{}
void View::registerObserver ( std::string notificationName, IObserverFunctor* observer )
{}
void View::notifyObservers( INotification* notification )
{}
void View::removeObserver( std::string notificationName, INotificationHandler* notifyContext )
{}
void View::registerMediator( IMediator* mediator )
{}
IMediator* View::retrieveMediator( std::string mediatorName )
{return 0;}
IMediator* View::removeMediator( std::string mediatorName )
{return 0;}
bool View::hasMediator( std::string mediatorName )
{return true;}
void View::removeView( std::string key )
{}
void View::initializeView()
{}
//--------------------------------------
//  Controller
//--------------------------------------
Controller::Controller()
{}
void Controller::executeCommand( INotification* note )
{}
void Controller::registerCommand( std::string notificationName, ICommand* commandClassRef )
{}
bool Controller::hasCommand( std::string notificationName )
{}
void Controller::removeCommand( std::string notificationName )
{}
void Controller::removeController( std::string key )
{}
void Controller::initializeController( )
{}
//--------------------------------------
//  FACADE
//--------------------------------------
Facade::Facade()
{
    // make sure our pointers are null at first
    // for testing purposes
    this->model = 0;
    this->controller = 0;
    this->view = 0;
}
void Facade::registerCommand( std::string notificationName, ICommand* commandClassRef )
{}
void Facade::removeCommand( std::string notificationName )
{}
bool Facade::hasCommand( std::string notificationName )
{return true;}
void Facade::registerProxy ( IProxy* proxy )
{}
IProxy* Facade::retrieveProxy ( std::string proxyName )
{return 0;}
IProxy* Facade::removeProxy ( std::string proxyName )
{return 0;}
bool Facade::hasProxy( std::string proxyName )
{return true;}
void Facade::registerMediator( IMediator* mediator )
{}
IMediator* Facade::retrieveMediator( std::string mediatorName )
{return 0;}
IMediator* Facade::removeMediator( std::string mediatorName )
{return 0;}
bool Facade::hasMediator( std::string mediatorName )
{return true;}
void Facade::sendNotification( std::string notificationName, IBody* body, std::string type)
{}
void Facade::sendNotification( std::string notificationName, std::string type )
{}
void Facade::sendNotification( std::string notificationName, IBody* body )
{}
void Facade::sendNotification( std::string notificationName )
{}
void Facade::notifyObservers ( INotification* notification )
{}
void Facade::initializeNotifier(std::string key)
{
    this->setMultitonKey(key);
}
bool Facade::hasCore( std::string key )
{return true;}
void Facade::removeCore( std::string key )
{}
void Facade::initializeFacade(std::string key)
{
    this->initializeNotifier(key);
    this->initializeModel();
    this->initializeController();
    this->initializeView();
}

void Facade::initializeModel()
{
    // if it's been initialized, abort
    if(this->controller != (IController*) 0)
        return;
    this->controller = Multiton<Controller>::instance(this->getMultitonKey());
    this->controller->setMultitonKey(this->getMultitonKey());
}
void Facade::initializeController()
{
    // if it's been initialized, abort
    if(this->model != (IModel*) 0)
        return;
    this->model = Multiton<Model>::instance(this->getMultitonKey());
    this->model->setMultitonKey(this->getMultitonKey());
}
void Facade::initializeView()
{
    // if it's been initialized, abort
    if(this->view != (IView*) 0)
        return;
    this->view = Multiton<View>::instance(this->getMultitonKey());
    this->view->setMultitonKey(this->getMultitonKey());
}