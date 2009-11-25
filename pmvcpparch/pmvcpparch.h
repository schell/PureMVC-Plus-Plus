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
//  MultitonKeyHeir
//--------------------------------------
/**
 *  Multiton key holding class.
 *  Inheritors of this class all hold multiton keys.
 */
class MultitonKeyHeir : public IMultitonKeyHeir
{
public:
    /**
     *  Set multiton key.
     *  Sets the multiton key.
     *  @param key The name of the key
     */
    virtual void setMultitonKey(std::string key);
    /**
     *  Get multiton key.
     *  Returns the multiton key.
     *  @return The string key name
     */
    virtual std::string getMultitonKey();
protected:
    std::string _multitonKey;
};
//--------------------------------------
//  Facade
//--------------------------------------
/**
 * A base Multiton <code>IFacade</code> implementation.
 *
 * @see Model::Model
 * @see View::View
 * @see Controller::Controller
 */
class Facade : public MultitonKeyHeir, public IFacade
{
public:
    Facade();
protected:
    IController* controller;
    
    void initializeController();
};
//--------------------------------------
//  Notifier
//--------------------------------------
/**
 * A Base <code>INotifier</code> implementation.
 *
 * <p>
 * <code>MacroCommand, Command, Mediator</code> and <code>Proxy</code>
 * all have a need to send <code>Notifications</code>. <p>
 * <p>
 * The <code>INotifier</code> interface provides a common method called
 * <code>sendNotification</code> that relieves implementation code of
 * the necessity to actually construct <code>Notifications</code>.</p>
 *
 * <p>
 * The <code>Notifier</code> class, which all of the above mentioned classes
 * extend, provides an initialized reference to the <code>Facade</code>
 * Multiton, which is required for the convienience method
 * for sending <code>Notifications</code>, but also eases implementation as these
 * classes have frequent <code>Facade</code> interactions and usually require
 * access to the facade anyway.</p>
 *
 * <p>
 * NOTE: There is one caveat to notifiers, they cannot
 * send notifications or reach the facade until they
 * have a valid multitonKey.
 *
 * The multitonKey is set:
 *   * on a Command when it is executed by the Controller
 *   * on a Mediator is registered with the View
 *   * on a Proxy is registered with the Model.
 *
 * @see Proxy::Proxy
 * @see Facade::Facade
 * @see Mediator::Mediator
 * @see MacroCommand::MacroCommand
 * @see SimpleCommand::SimpleCommand
 */
class Notifier : public MultitonKeyHeir, public INotifier
{
public:
    void initializeNotifier(std::string key);
};
//--------------------------------------
//  SimpleCommand
//--------------------------------------
/**
 * A base <code>ICommand</code> implementation.
 *
 * <p>
 * Your subclass should override the <code>execute</code>
 * method where your business logic will handle the <code>INotification</code>.
 * </p>
 *
 * @see Controller::Controller
 * @see Notification::Notification
 * @see MacroCommand::MacroCommand
 */
class SimpleCommand : public Notifier, public ICommand
{
public:
    virtual void execute(INotification* notification) = 0;
};
//--------------------------------------
//  Model
//--------------------------------------
/**
 * A Multiton <code>IModel</code> implementation.
 *
 * <p>
 * In PureMVC, the <code>Model</code> class provides
 * access to model objects (Proxies) by named lookup.
 *
 * <p>
 * The <code>Model</code> assumes these responsibilities:</p>
 *
 * <UL>
 * <LI>Maintain a cache of <code>IProxy</code> instances.</LI>
 * <LI>Provide methods for registering, retrieving, and removing
 * <code>IProxy</code> instances.</LI>
 * </UL>
 *
 * <p>
 * Your application must register <code>IProxy</code> instances
 * with the <code>Model</code>. Typically, you use an
 * <code>ICommand</code> to create and register <code>IProxy</code>
 * instances once the <code>Facade</code> has initialized the Core
 * actors.</p>
 *
 * @see Proxy::Proxy
 * @see IProxy::IProxy
 */
class Model : public MultitonKeyHeir, public IModel
{
public:
    Model(std::string key);
};

//--------------------------------------
//  Controller
//--------------------------------------
/**
 * A Multiton <code>IController</code> implementation.
 *
 * <P>
 * In PureMVC, the <code>Controller</code> class follows the
 * 'Command and Controller' strategy, and assumes these
 * responsibilities:
 * <UL>
 * <LI> Remembering which <code>ICommand</code>s
 * are intended to handle which <code>INotifications</code>.</LI>
 * <LI> Registering itself as an <code>IObserver</code> with
 * the <code>View</code> for each <code>INotification</code>
 * that it has an <code>ICommand</code> mapping for.</LI>
 * <LI> Creating a new instance of the proper <code>ICommand</code>
 * to handle a given <code>INotification</code> when notified by the <code>View</code>.</LI>
 * <LI> Calling the <code>ICommand</code>'s <code>execute</code>
 * method, passing in the <code>INotification</code>.</LI>
 * </UL>
 *
 * <P>
 * Your application must register <code>ICommands</code> with the
 * Controller.
 * <P>
 * The simplest way is to subclass </code>Facade</code>,
 * and use its <code>initializeController</code> method to add your
 * registrations.
 *
 * @see View
 * @see Observer
 * @see Notification
 * @see SimpleCommand
 * @see MacroCommand
 */
class Controller : public MultitonKeyHeir, public IController
{

};
#endif	/* _PMVCPPARCH_H */