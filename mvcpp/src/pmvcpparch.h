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
class MultitonKeyHeir : public virtual IMultitonKeyHeir
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
private:
    std::string _multitonKey;
};
//--------------------------------------
//  Notification
//--------------------------------------
/**
 * A base <code>INotification</code> implementation.
 *
 * <P>
 * The Observer Pattern as implemented within PureMVC exists
 * to support event-driven communication between the
 * application and the actors of the MVC triad.</P>
 *
 * <P>
 * <code>IMediator</code> implementors
 * place event listeners on their view components, which they
 * handle in the usual way. This may lead to the broadcast of <code>Notification</code>s to
 * trigger <code>ICommand</code>s or to communicate with other <code>IMediators</code>. <code>IProxy</code> and <code>ICommand</code>
 * instances communicate with each other and <code>IMediator</code>s
 * by broadcasting <code>INotification</code>s.</P>
 *
 * <P>
 * PureMVC <code>Notification</code>s follow a 'Publish/Subscribe'
 * pattern. PureMVC classes need not be related to each other in a
 * parent/child relationship in order to communicate with one another
 * using <code>Notification</code>s.
 *
 * @see Observer
 *
 */
class Notification : public INotification
{
public:
    std::string name;
    std::string type;
    IBody* body;
    
    Notification(std::string name, IBody* body, std::string type);
    Notification(std::string name, IBody* body);
    Notification(std::string name, std::string type);
    std::string getName();
    void setBody( IBody* body );
    IBody* getBody();
    void setType( std::string type );
    std::string getType();
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
class Notifier : public MultitonKeyHeir, public virtual INotifier
{
public:
    void sendNotification   ( std::string notificationName, IBody* body, std::string type);
    void sendNotification   ( std::string notificationName, std::string type );
    void sendNotification   ( std::string notificationName, IBody* body );
    void sendNotification   ( std::string notificationName );
    void initializeNotifier(std::string key);
protected:
    IFacade* getFacade();
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
    void sendNotification( std::string notificationName, IBody* body, std::string type);
    void sendNotification( std::string notificationName, std::string type );
    void sendNotification( std::string notificationName, IBody* body );
    void sendNotification( std::string notificationName );

protected:
    IModel* model;
    IController* controller;
    IView* view;

    void initializeFacade(std::string key);
    void initializeNotifier(std::string key);
    void initializeModel();
    void initializeController();
    void initializeView();
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
    virtual void execute(INotification* notification);
};
//--------------------------------------
//  MacroCommand
//--------------------------------------

/**
 * A base <code>ICommand</code> implementation that executes other <code>ICommand</code>s.
 *
 * <P>
 * A <code>MacroCommand</code> maintains an list of
 * <code>ICommand</code> Class references called <i>SubCommands</i>.</P>
 *
 * <P>
 * When <code>execute</code> is called, the <code>MacroCommand</code>
 * instantiates and calls <code>execute</code> on each of its <i>SubCommands</i> turn.
 * Each <i>SubCommand</i> will be passed a reference to the original
 * <code>INotification</code> that was passed to the <code>MacroCommand</code>'s
 * <code>execute</code> method.</P>
 *
 * <P>
 * Unlike <code>SimpleCommand</code>, your subclass
 * should not override <code>execute</code>, but instead, should
 * override the <code>initializeMacroCommand</code> method,
 * calling <code>addSubCommand</code> once for each <i>SubCommand</i>
 * to be executed.</P>
 *
 * <P>
 *
 * @see Controller
 * @see Notification
 * @see SimpleCommand
 */
class MacroCommand : public SimpleCommand
{
public:
    /**
         * Constructor.
         *
         * <P>
         * You should not need to define a constructor,
         * instead, override the <code>initializeMacroCommand</code>
         * method.</P>
         *
         * <P>
         * If your subclass does define a constructor, be
         * sure to call <code>super()</code>.</P>
         */
    MacroCommand();
protected:
    /**
         * Initialize the <code>MacroCommand</code>.
         *
         * <P>
         * In your subclass, override this method to
         * initialize the <code>MacroCommand</code>'s <i>SubCommand</i>
         * list with <code>ICommand</code> class references like
         * this:</P>
         *
         * <listing>
         *        // Initialize MyMacroCommand
         *        override protected function initializeMacroCommand( ) : void
         *        {
         *            addSubCommand( com.me.myapp.controller.FirstCommand );
         *            addSubCommand( com.me.myapp.controller.SecondCommand );
         *            addSubCommand( com.me.myapp.controller.ThirdCommand );
         *        }
         * </listing>
         *
         * <P>
         * Note that <i>SubCommand</i>s may be any <code>ICommand</code> implementor,
         * <code>MacroCommand</code>s or <code>SimpleCommands</code> are both acceptable.
         */
    virtual void initializeMacroCommand();
    /**
         * Add a <i>SubCommand</i>.
         *
         * <P>
         * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
         * order.</P>
         *
         * @param command A pointer to the <code>ICommand</code> sub-command.
         */
    void addSubCommand( ICommand* command );
    /**
     *  Subcommands.
     *  Holds all the subcommands.
     * 
     */
    std::vector<ICommand*> subCommands;
    virtual void execute(INotification* notification);
    
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
protected:
//    IView* view;
//    vector<ICommand*> commandMap;
};

//--------------------------------------
//  View
//--------------------------------------
/**
 * A Multiton <code>IView</code> implementation.
 *
 * <P>
 * In PureMVC, the <code>View</code> class assumes these responsibilities:
 * <UL>
 * <LI>Maintain a cache of <code>IMediator</code> instances.</LI>
 * <LI>Provide methods for registering, retrieving, and removing <code>IMediators</code>.</LI>
 * <LI>Notifiying <code>IMediators</code> when they are registered or removed.</LI>
 * <LI>Managing the observer lists for each <code>INotification</code> in the application.</LI>
 * <LI>Providing a method for attaching <code>IObservers</code> to an <code>INotification</code>'s observer list.</LI>
 * <LI>Providing a method for broadcasting an <code>INotification</code>.</LI>
 * <LI>Notifying the <code>IObservers</code> of a given <code>INotification</code> when it broadcast.</LI>
 * </UL>
 *
 *  @see Mediator
 *  @see Observer
 *  @see Notification
 */
class View : public MultitonKeyHeir, public IView
{
public:
};
#endif/* _PMVCPPARCH_H */