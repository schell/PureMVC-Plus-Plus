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
void Facade::sendNotification( std::string notificationName, IBody* body, std::string type)
{

}
void Facade::sendNotification( std::string notificationName, std::string type )
{

}
void Facade::sendNotification( std::string notificationName, IBody* body )
{

}
void Facade::sendNotification( std::string notificationName )
{

}
void Facade::initializeFacade(std::string key)
{
    this->initializeNotifier(key);
    this->initializeModel();
    this->initializeController();
    this->initializeView();
}
void Facade::initializeNotifier(std::string key)
{
    this->setMultitonKey(key);
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
    this->initializeMacroCommand();
}
void MacroCommand::initializeMacroCommand()
{
    std::cout <<"\nMacroCommand::initializeMacroCommand\n";
}
void MacroCommand::execute(INotification* notification)
{
    
}
void MacroCommand::addSubCommand(ICommand* command)
{
    this->subCommands.push_back(command);
}
//--------------------------------------
//  Model
//--------------------------------------