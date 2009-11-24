/**
 *	Implementation file for the pmvcpp architecture.
 *
 *	@author	Schell Scivally
 */
#include <iostream>
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