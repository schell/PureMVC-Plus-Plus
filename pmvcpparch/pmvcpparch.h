/* 
 * File:   pmvcpparch.h
 * Author: Schell Scivally
 *
 * Created on November 23, 2009, 1:17 PM
 */

#ifndef _PMVCPPARCH_H
#define	_PMVCPPARCH_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>

#include "pmvcppbase.h"
//--------------------------------------
//  Multiton
//--------------------------------------
class MultitonKeyHeir
{
public:
    void setMultitonKey(std::string key);
    std::string getMultitonKey();
protected:
    std::string _multitonKey;
};
//--------------------------------------
//  Facade
//--------------------------------------
class Facade : public MultitonKeyHeir//, public IFacade
{
};
//--------------------------------------
//  Notifier
//--------------------------------------
class Notifier : public MultitonKeyHeir//,public INotifier
{
public:
    void initializeNotifier(std::string key);
};
//--------------------------------------
//  SimpleCommand
//--------------------------------------
class SimpleCommand : public Notifier//,public ICommand
{
public:
    virtual void execute(INotification* notification) = 0;
};
//--------------------------------------
//  Model
//--------------------------------------
class Model : public MultitonKeyHeir//,public IModel
{
public:
    Model(std::string key);
};
#endif	/* _PMVCPPARCH_H */