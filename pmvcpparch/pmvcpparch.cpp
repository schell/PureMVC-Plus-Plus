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
    this->controller = 0;
}
void Facade::initializeController()
{
    // if it's been initialized, abort
    if(this->controller != (IController*) 0)
        return;
    this->controller = Multiton<Controller>::instance(this->getMultitonKey());
    this->controller->setMultitonKey(this->getMultitonKey());
}
//--------------------------------------
//  Notifier
//--------------------------------------
void Notifier::initializeNotifier(std::string key)
{
    this->_multitonKey = key;
}
//--------------------------------------
//  SimpleCommand
//--------------------------------------

//--------------------------------------
//  Model
//--------------------------------------
Model::Model(std::string key)
{
    this->_multitonKey = key;
}