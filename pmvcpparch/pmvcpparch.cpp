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
//  Notifier
//--------------------------------------
void Notifier::initializeNotifier(std::string key)
{
    this->setMultitonKey(key);
}
//--------------------------------------
//  SimpleCommand
//--------------------------------------

//--------------------------------------
//  Model
//--------------------------------------