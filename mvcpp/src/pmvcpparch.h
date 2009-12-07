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
     * You need to define a constructor,
     * and add all your subcommands within it.</P>
     *
     * In your subclass, define a constuctor to
     * initialize the <code>MacroCommand</code>'s <i>SubCommand</i>
     * list with <code>ICommand</code> class references like
     * this:</P>
     *
     * <listing>
     *        // Initialize MyMacroCommand
     *        MacroCommandSubclass::MacroCommandSubclass( )
     *        {
     *            this->addSubCommand( new FirstCommand() );
     *            this->addSubCommand( new SecondCommand() );
     *            this->addSubCommand( new ThirdCommand() );
     *        }
     * </listing>
     *
     * <P>
     * Note that <i>SubCommand</i>s may be any <code>ICommand</code> implementor,
     * <code>MacroCommand</code>s or <code>SimpleCommands</code> are both acceptable.
     */
    MacroCommand();
    /**
     * Execute this <code>MacroCommand</code>'s <i>SubCommands</i>.
     *
     * <P>
     * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
     * order.
     *
     * @param notification the <code>INotification</code> object to be passsed to each <i>SubCommand</i>.
     */
    void execute(INotification* notification);
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
    void addSubCommand( ICommand* command );
    /**
     *  Subcommands.
     *  Holds all the subcommands.
     * 
     */
    std::vector<ICommand*> subCommands;
};
/**
 * A base <code>IObserver</code> implementation.
 *
 * <P>
 * An <code>Observer</code> is an object that encapsulates information
 * about an interested object with a method that should
 * be called when a particular <code>INotification</code> is broadcast. </P>
 *
 * <P>
 * In PureMVC, the <code>Observer</code> class assumes these responsibilities:
 * <UL>
 * <LI>Encapsulate the notification (callback) method of the interested object.</LI>
 * <LI>Encapsulate the notification context (this) of the interested object.</LI>
 * <LI>Provide methods for setting the notification method and context.</LI>
 * <LI>Provide a method for notifying the interested object.</LI>
 * </UL>
 *
 * @see View
 * @see Notification
 */
template<class T>
class Observer : public IObserver<T>
{
private:
    typedef void(T::*NotifyMethod)(INotification*);
    typedef T* NotifyContext;
    NotifyMethod notifyMethod;
    NotifyContext notifyContext;
public:
    /**
     * Constructor.
     *
     * <P>
     * The notification method on the interested object should take
     * one parameter of type <code>INotification</code></P>
     *
     * @param method the notification method of the interested object
     * @param context the notification context of the interested object
     */
    Observer( NotifyMethod method, NotifyContext context )
    {
        this->setNotifyMethod(method);
        this->setNotifyContext(context);
    }
    /**
     * Set the notification method.
     *
     * <P>
     * The notification method should take one parameter of type <code>INotification</code>.</P>
     *
     * @param method the notification (callback) method of the interested object.
     */
    void setNotifyMethod( NotifyMethod method )
    {
        this->notifyMethod = method;
    }
    /**
     * Set the notification context.
     *
     * @param context the notification context (this) of the interested object.
     */
    void setNotifyContext( NotifyContext context )
    {
        this->notifyContext = context;
    }
    /**
     * Get the notification method.
     *
     * @return the notification (callback) method of the interested object.
     */
    NotifyMethod getNotifyMethod()
    {
        return this->notifyMethod;
    }
    /**
     * Get the notification context.
     *
     * @return the notification context (<code>this</code>) of the interested object.
     */
    NotifyContext getNotifyContext()
    {
        return this->notifyContext;
    }
    /**
     * Notify the interested object.
     *
     * @param notification the <code>INotification</code> to pass to the interested object's notification method.
     */
    void notifyObserver( INotification* notification )
    {
        (this->notifyContext->*notifyMethod)(notification);
    }
    /**
     * Compare an object to the notification context.
     *
     * @param compareContext the object to compare
     * @return boolean indicating if the object and the notification context are the same
     */
    bool compareNotifyContext( NotifyContext compareContext )
    {
        return &*compareContext == &*this->notifyContext;
    }
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
    /**
     * Constructor.
     *
     * <P>
     * This <code>IModel</code> implementation is a Multiton,
     * so you should not call the constructor
     * directly, but instead call the static Multiton
     * Factory method <code>Model.getInstance( multitonKey )</code>
     *
     * @throws Error Error if instance for this Multiton key instance has already been constructed
     *
     */
    Model();
    
    /**
     * Register an <code>IProxy</code> with the <code>Model</code>.
     *
     * @param proxy an <code>IProxy</code> to be held by the <code>Model</code>.
     */
    void registerProxy( IProxy* proxy );
    /**
     * Retrieve an <code>IProxy</code> from the <code>Model</code>.
     *
     * @param proxyName
     * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
     */
    IProxy* retrieveProxy( std::string proxyName );

    /**
     * Check if a Proxy is registered
     *
     * @param proxyName
     * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
     */
    bool hasProxy( std::string proxyName );

    /**
     * Remove an <code>IProxy</code> from the <code>Model</code>.
     *
     * @param proxyName name of the <code>IProxy</code> instance to be removed.
     * @return the <code>IProxy</code> that was removed from the <code>Model</code>
     */
    IProxy* removeProxy( std::string proxyName );

    /**
     * Remove an IModel instance
     *
     * @param multitonKey of IModel instance to remove
     */
    void removeModel( std::string key );

protected:
    /**
     * Initialize the <code>Model</code> instance.
     *
     * <P>
     * Called automatically by the constructor, this
     * is your opportunity to initialize the Singleton
     * instance in your subclass without overriding the
     * constructor.</P>
     *
     * @return void
     */
    void initializeModel(  );

    // Mapping of proxyNames to IProxy instances
    std::map <std::string, IProxy*> proxyMap;
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
public:
    /**
     * Constructor.
     *
     * <P>
     * This <code>IController</code> implementation is a Multiton,
     * so you should not call the constructor
     * directly, but instead call the static Factory method,
     * passing the unique key for this instance
     * <code>Controller.getInstance( multitonKey )</code>
     *
     * @throws Error Error if instance for this Multiton key has already been constructed
     *
     */
    Controller();

    /**
     * If an <code>ICommand</code> has previously been registered
     * to handle a the given <code>INotification</code>, then it is executed.
     *
     * @param note an <code>INotification</code>
     */
    void executeCommand( INotification* note );
    /**
     * Register a particular <code>ICommand</code> class as the handler
     * for a particular <code>INotification</code>.
     *
     * <P>
     * If an <code>ICommand</code> has already been registered to
     * handle <code>INotification</code>s with this name, it is no longer
     * used, the new <code>ICommand</code> is used instead.</P>
     *
     * The Observer for the new ICommand is only created if this the
     * first time an ICommand has been regisered for this Notification name.
     *
     * @param notificationName the name of the <code>INotification</code>
     * @param commandClassRef the <code>Class</code> of the <code>ICommand</code>
     */
    void registerCommand( std::string notificationName, ICommand* commandClassRef );

    /**
     * Check if a Command is registered for a given Notification
     *
     * @param notificationName
     * @return whether a Command is currently registered for the given <code>notificationName</code>.
     */
    bool hasCommand( std::string notificationName );

    /**
     * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
     *
     * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
     */
    void removeCommand( std::string notificationName );

    /**
     * Remove an IController instance
     *
     * @param multitonKey of IController instance to remove
     */
    static void removeController( std::string key );

protected:
        /**
     * Initialize the Multiton <code>Controller</code> instance.
     *
     * <P>Called automatically by the constructor.</P>
     *
     * <P>Note that if you are using a subclass of <code>View</code>
     * in your application, you should <i>also</i> subclass <code>Controller</code>
     * and override the <code>initializeController</code> method in the
     * following way:</P>
     *
     * <listing>
     *        // ensure that the Controller is talking to my IView implementation
     *        override public function initializeController(  ) : void
     *        {
     *            view = MyView.getInstance();
     *        }
     * </listing>
     *
     * @return void
     */
    void initializeController(  );
    // Local reference to View
    IView* view;

    // Mapping of Notification names to Command Class references
    std::map<std::string, ICommand*> commandMap;
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
    /**
     * Constructor.
     *
     * <P>
     * This <code>IView</code> implementation is a Multiton,
     * so you should not call the constructor
     * directly, but instead call the static Multiton
     * Factory method <code>View.getInstance( multitonKey )</code>
     *
     * @throws Error Error if instance for this Multiton key has already been constructed
     *
     */
    View( );

    /**
     * Register an <code>IObserverFunctor</code> to be notified
     * of <code>INotifications</code> with a given name.
     *
     * @param notificationName the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
     * @param observer the <code>IObserverFunctor</code> to register
     */
    void registerObserver ( std::string notificationName, IObserverFunctor* observer );


    /**
     * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
     *
     * <P>
     * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
     * list are notified and are passed a reference to the <code>INotification</code> in
     * the order in which they were registered.</P>
     *
     * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
     */
    void notifyObservers( INotification* notification );

    /**
     * Remove the observer for a given notifyContext from an observer list for a given Notification name.
     * <P>
     * @param notificationName which observer list to remove from
     * @param notifyContext remove the observer with this object as its notifyContext
     */
    void removeObserver( std::string notificationName, INotificationHandler* notifyContext );

    /**
     * Register an <code>IMediator</code> instance with the <code>View</code>.
     *
     * <P>
     * Registers the <code>IMediator</code> so that it can be retrieved by name,
     * and further interrogates the <code>IMediator</code> for its
     * <code>INotification</code> interests.</P>
     * <P>
     * If the <code>IMediator</code> returns any <code>INotification</code>
     * names to be notified about, an <code>Observer</code> is created encapsulating
     * the <code>IMediator</code> instance's <code>handleNotification</code> method
     * and registering it as an <code>Observer</code> for all <code>INotifications</code> the
     * <code>IMediator</code> is interested in.</p>
     *
     * @param mediatorName the name to associate with this <code>IMediator</code> instance
     * @param mediator a reference to the <code>IMediator</code> instance
     */
    void registerMediator( IMediator* mediator );

    /**
     * Retrieve an <code>IMediator</code> from the <code>View</code>.
     *
     * @param mediatorName the name of the <code>IMediator</code> instance to retrieve.
     * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
     */
    IMediator* retrieveMediator( std::string mediatorName );

    /**
     * Remove an <code>IMediator</code> from the <code>View</code>.
     *
     * @param mediatorName name of the <code>IMediator</code> instance to be removed.
     * @return the <code>IMediator</code> that was removed from the <code>View</code>
     */
    /**
     * Remove an <code>IMediator</code> from the <code>View</code>.
     *
     * @param mediatorName name of the <code>IMediator</code> instance to be removed.
     * @return the <code>IMediator</code> that was removed from the <code>View</code>
     */
    IMediator* removeMediator( std::string mediatorName );

    /**
     * Check if a Mediator is registered or not
     *
     * @param mediatorName
     * @return whether a Mediator is registered with the given <code>mediatorName</code>.
     */
    bool hasMediator( std::string mediatorName );

    /**
     * Remove an IView instance
     *
     * @param multitonKey of IView instance to remove
     */
    static void removeView( std::string key );

protected:
    /**
     * Initialize the Singleton View instance.
     *
     * <P>
     * Called automatically by the constructor, this
     * is your opportunity to initialize the Singleton
     * instance in your subclass without overriding the
     * constructor.</P>
     *
     * @return void
     */
    void initializeView();
    // Mapping of Mediator names to Mediator instances
    std::map<std::string, IMediator*> mediatorMap;

    // Mapping of Notification names to Observer lists
    std::map<std::string, IObserverFunctor*> observerMap;
};
//--------------------------------------
//  Facade
//--------------------------------------
/**
 * A base Multiton <code>IFacade</code> implementation.
 *
 * @see Model
 * @see View
 * @see Controller
 */
class Facade : public IFacade, public MultitonKeyHeir
{
public:
    /**
     * Constructor.
     *
     * <P>
     * This <code>IFacade</code> implementation is a Multiton,
     * so you should not call the constructor
     * directly, but instead call the static Factory method,
     * passing the unique key for this instance
     * <code>Facade.getInstance( multitonKey )</code>
     *
     * @throws Error Error if instance for this Multiton key has already been constructed
     *
     */
    Facade();

    /**
     * Register an <code>ICommand</code> with the <code>Controller</code> by Notification name.
     *
     * @param notificationName the name of the <code>INotification</code> to associate the <code>ICommand</code> with
     * @param commandClassRef a reference to the Class of the <code>ICommand</code>
     */
    void registerCommand( std::string notificationName, ICommand* commandClassRef );

    /**
     * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
     *
     * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
     */
    void removeCommand( std::string notificationName );

    /**
     * Check if a Command is registered for a given Notification
     *
     * @param notificationName
     * @return whether a Command is currently registered for the given <code>notificationName</code>.
     */
    bool hasCommand( std::string notificationName );

    /**
     * Register an <code>IProxy</code> with the <code>Model</code> by name.
     *
     * @param proxyName the name of the <code>IProxy</code>.
     * @param proxy the <code>IProxy</code> instance to be registered with the <code>Model</code>.
     */
    void registerProxy ( IProxy* proxy );
    /**
     * Retrieve an <code>IProxy</code> from the <code>Model</code> by name.
     *
     * @param proxyName the name of the proxy to be retrieved.
     * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
     */
    IProxy* retrieveProxy ( std::string proxyName );

    /**
     * Remove an <code>IProxy</code> from the <code>Model</code> by name.
     *
     * @param proxyName the <code>IProxy</code> to remove from the <code>Model</code>.
     * @return the <code>IProxy</code> that was removed from the <code>Model</code>
     */
    IProxy* removeProxy ( std::string proxyName );

    /**
     * Check if a Proxy is registered
     *
     * @param proxyName
     * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
     */
    bool hasProxy( std::string proxyName );

    /**
     * Register a <code>IMediator</code> with the <code>View</code>.
     *
     * @param mediatorName the name to associate with this <code>IMediator</code>
     * @param mediator a reference to the <code>IMediator</code>
     */
    void registerMediator( IMediator* mediator );

    /**
     * Retrieve an <code>IMediator</code> from the <code>View</code>.
     *
     * @param mediatorName
     * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
     */
    IMediator* retrieveMediator( std::string mediatorName );

    /**
     * Remove an <code>IMediator</code> from the <code>View</code>.
     *
     * @param mediatorName name of the <code>IMediator</code> to be removed.
     * @return the <code>IMediator</code> that was removed from the <code>View</code>
     */
    IMediator* removeMediator( std::string mediatorName );

    /**
     * Check if a Mediator is registered or not
     *
     * @param mediatorName
     * @return whether a Mediator is registered with the given <code>mediatorName</code>.
     */
    bool hasMediator( std::string mediatorName );

    /**
     * Create and send an <code>INotification</code>.
     *
     * <P>
     * Keeps us from having to construct new notification
     * instances in our implementation code.
     * @param notificationName the name of the notiification to send
     * @param body the body of the notification (optional)
     * @param type the type of the notification (optional)
     */
    void sendNotification( std::string notificationName, IBody* body, std::string type );
    void sendNotification( std::string notificationName, IBody* body );
    void sendNotification( std::string notificationName, std::string type );
    void sendNotification( std::string notificationName );
    /**
     * Notify <code>Observer</code>s.
     * <P>
     * This method is left public mostly for backward
     * compatibility, and to allow you to send custom
     * notification classes using the facade.</P>
     *<P>
     * Usually you should just call sendNotification
     * and pass the parameters, never having to
     * construct the notification yourself.</P>
     *
     * @param notification the <code>INotification</code> to have the <code>View</code> notify <code>Observers</code> of.
     */
    void notifyObservers ( INotification* notification );

    /**
     * Set the Multiton key for this facade instance.
     * <P>
     * Not called directly, but instead from the
     * constructor when getInstance is invoked.
     * It is necessary to be public in order to
     * implement INotifier.</P>
     */
    void initializeNotifier( std::string key );

    /**
     * Check if a Core is registered or not
     *
     * @param key the multiton key for the Core in question
     * @return whether a Core is registered with the given <code>key</code>.
     */
    static bool hasCore( std::string key );

    /**
     * Remove a Core.
     * <P>
     * Remove the Model, View, Controller and Facade
     * instances for the given key.</P>
     *
     * @param multitonKey of the Core to remove
     */
    static void removeCore( std::string key );
protected:
    /**
     * Initialize the Multiton <code>Facade</code> instance.
     *
     * <P>
     * Called automatically by the constructor. Override in your
     * subclass to do any subclass specific initializations. Be
     * sure to call <code>super.initializeFacade()</code>, though.</P>
     */
    void initializeFacade( std::string key );

    /**
     * Initialize the <code>Controller</code>.
     *
     * <P>
     * Called by the <code>initializeFacade</code> method.
     * Override this method in your subclass of <code>Facade</code>
     * if one or both of the following are true:
     * <UL>
     * <LI> You wish to initialize a different <code>IController</code>.</LI>
     * <LI> You have <code>Commands</code> to register with the <code>Controller</code> at startup.</code>. </LI>
     * </UL>
     * If you don't want to initialize a different <code>IController</code>,
     * call <code>super.initializeController()</code> at the beginning of your
     * method, then register <code>Command</code>s.
     * </P>
     */
    void initializeController( );

    /**
     * Initialize the <code>Model</code>.
     *
     * <P>
     * Called by the <code>initializeFacade</code> method.
     * Override this method in your subclass of <code>Facade</code>
     * if one or both of the following are true:
     * <UL>
     * <LI> You wish to initialize a different <code>IModel</code>.</LI>
     * <LI> You have <code>Proxy</code>s to register with the Model that do not
     * retrieve a reference to the Facade at construction time.</code></LI>
     * </UL>
     * If you don't want to initialize a different <code>IModel</code>,
     * call <code>super.initializeModel()</code> at the beginning of your
     * method, then register <code>Proxy</code>s.
     * <P>
     * Note: This method is <i>rarely</i> overridden; in practice you are more
     * likely to use a <code>Command</code> to create and register <code>Proxy</code>s
     * with the <code>Model</code>, since <code>Proxy</code>s with mutable data will likely
     * need to send <code>INotification</code>s and thus will likely want to fetch a reference to
     * the <code>Facade</code> during their construction.
     * </P>
     */
    void initializeModel( );


    /**
     * Initialize the <code>View</code>.
     *
     * <P>
     * Called by the <code>initializeFacade</code> method.
     * Override this method in your subclass of <code>Facade</code>
     * if one or both of the following are true:
     * <UL>
     * <LI> You wish to initialize a different <code>IView</code>.</LI>
     * <LI> You have <code>Observers</code> to register with the <code>View</code></LI>
     * </UL>
     * If you don't want to initialize a different <code>IView</code>,
     * call <code>super.initializeView()</code> at the beginning of your
     * method, then register <code>IMediator</code> instances.
     * <P>
     * Note: This method is <i>rarely</i> overridden; in practice you are more
     * likely to use a <code>Command</code> to create and register <code>Mediator</code>s
     * with the <code>View</code>, since <code>IMediator</code> instances will need to send
     * <code>INotification</code>s and thus will likely want to fetch a reference
     * to the <code>Facade</code> during their construction.
     * </P>
     */
    void initializeView( );


    // References to Model, View and Controller
    IController* controller;
    IModel* model;
    IView* view;
};

#endif/* _PMVCPPARCH_H */