/* 
 * File:   pmvcppbase.h
 * Author: Schell Scivally
 *
 * Created on November 21, 2009, 10:51 AM
 */

#ifndef _PMVCPPBASE_H
#define	_PMVCPPBASE_H

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<cstdlib>

//--------------------------------------
//  IBody
//--------------------------------------
/**
 *  Notification body.
 *  The base class for a body of a notification.
 */
class IBody
{
public:
    IBody(){}
    IBody(std::string type)
    {
        this->_type = type;
    }
    void setType(std::string type)
    {
        this->_type = type;
    }
    std::string getType()
    {
        return this->_type;
    }
private:
    std::string _type;
};
//--------------------------------------
//  IMultitonKeyHeir
//--------------------------------------
/**
 *  Contains a multiton key.
 *  Classes that inherit contain multiton key getters and setters.
 */
class IMultitonKeyHeir
{
public:
    /**
     *  Set multiton key.
     *  Sets the multiton key.
     *  @param key The name of the key
     */
    virtual void setMultitonKey(std::string key) = 0;
    /**
     *  Get multiton key.
     *  Returns the multiton key.
     *  @return The string key name
     */
    virtual std::string getMultitonKey() = 0;
};
//--------------------------------------
//  INotifier
//--------------------------------------
/**
 * The interface definition for a PureMVC Notifier.
 *
 * <p>
 * <code>MacroCommand, Command, Mediator</code> and <code>Proxy</code>
 * all have a need to send <code>Notifications</code>. </p>
 *
 * <p>
 * The <code>INotifier</code> interface provides a common method called
 * <code>sendNotification</code> that relieves implementation code of
 * the necessity to actually construct <code>Notifications</code>.</p>
 *
 * <p>
 * The <code>Notifier</code> class, which all of the above mentioned classes
 * extend, also provides an initialized reference to the <code>Facade</code>
 * Singleton, which is required for the convienience method
 * for sending <code>Notifications</code>, but also eases implementation as these
 * classes have frequent <code>Facade</code> interactions and usually require
 * access to the facade anyway.</p>
 *
 * @see IFacade IFacade
 * @see INotification
 */
class INotifier
{
public:
    /**
     * Send a <code>INotification</code>.
     *
     * <p>
     * Convenience method to prevent having to construct new
     * notification instances in our implementation code.</p>
     *
     * @param notificationName the name of the notification to send
     * @param body the body of the notification (optional)
     * @param type the type of the notification (optional)
     */
    virtual void sendNotification   ( std::string notificationName, IBody* body, std::string type) = 0;
    virtual void sendNotification   ( std::string notificationName, std::string type ) = 0;
    virtual void sendNotification   ( std::string notificationName, IBody* body ) = 0;
    virtual void sendNotification   ( std::string notificationName ) = 0;
    /**
     * Initialize this INotifier instance.
     * <p>
     * This is how a Notifier gets its multitonKey.
     * Calls to sendNotification or to access the
     * facade will fail until after this method
     * has been called.</p>
     *
     * @param key the multitonKey for this INotifier to use
     */
    virtual void initializeNotifier ( std::string key ) = 0;
    virtual 	 ~INotifier         (){};
};
/**
 * The interface definition for a PureMVC Notification.
 *
 * <p>
 * PureMVC does not rely upon underlying event models such 
 * as the one provided with Flash, and ActionScript 3 does 
 * not have an inherent event model.</p>
 * 
 * <p>
 * The Observer Pattern as implemented within PureMVC exists 
 * to support event-driven communication between the 
 * application and the actors of the MVC triad.</p>
 * 
 * <p>
 * Notifications are not meant to be a replacement for Events
 * in Flex/Flash/AIR. Generally, <code>IMediator</code> implementors
 * place event listeners on their view components, which they
 * then handle in the usual way. This may lead to the broadcast of <code>Notification</code>s to 
 * trigger <code>ICommand</code>s or to communicate with other <code>IMediators</code>. <code>IProxy</code> and <code>ICommand</code>
 * instances communicate with each other and <code>IMediator</code>s 
 * by broadcasting <code>INotification</code>s.</p>
 * 
 * <p>
 * A key difference between Flash <code>Event</code>s and PureMVC 
 * <code>Notification</code>s is that <code>Event</code>s follow the 
 * 'Chain of Responsibility' pattern, 'bubbling' up the display hierarchy 
 * until some parent component handles the <code>Event</code>, while
 * PureMVC <code>Notification</code>s follow a 'Publish/Subscribe'
 * pattern. PureMVC classes need not be related to each other in a 
 * parent/child relationship in order to communicate with one another
 * using <code>Notification</code>s.
 * 
 * @see IView
 * @see IObserver
 */
class INotification
{
public:
        /**
         * Get the name of the <code>INotification</code> instance.
         * No setter, should be set by constructor only
         */
	virtual std::string getName         () = 0;
        /**
         * Set the body of the <code>INotification</code> instance
         */
	virtual void        setBody         ( IBody* body ) = 0;
        /**
         * Get the body of the <code>INotification</code> instance
         */
	virtual IBody*      getBody         () = 0;
        /**
         * Set the type of the <code>INotification</code> instance
         */
	virtual void        setType         ( std::string type ) = 0;
        /**
         * Get the type of the <code>INotification</code> instance
         */
	virtual std::string getType         () = 0;
        /**
         * Get the string representation of the <code>INotification</code> instance
         */
	virtual             ~INotification  (){};
};
/**
 * The interface definition for a PureMVC Command.
 *
 * @see INotification
 */
class ICommand : public virtual INotifier
{
public:
        /**
         * Execute the <code>ICommand</code>'s logic to handle a given <code>INotification</code>.
         *
         * @param note an <code>INotification</code> to handle.
         */
	virtual void execute	( INotification* notification ) = 0;
	virtual      ~ICommand	(){};
};
/**
 * The interface definition for a PureMVC Controller.
 *
 * <p>
 * In PureMVC, an <code>IController</code> implementor
 * follows the 'Command and Controller' strategy, and
 * assumes these responsibilities:
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
 * @see INotification
 * @see ICommand
 */
class IController : public virtual IMultitonKeyHeir
{
public:
    IController(){}
        /**
         * Register a particular <code>ICommand</code> class as the handler
         * for a particular <code>INotification</code>.
         *
         * @param notificationName the name of the <code>INotification</code>
         * @param commandClassRef the Class of the <code>ICommand</code>
         */
         //void registerCommand( std::string notificationName, ICommand* commandClassRef );
        /**
         * Execute the <code>ICommand</code> previously registered as the
         * handler for <code>INotification</code>s with the given notification name.
         *
         * @param notification the <code>INotification</code> to execute the associated <code>ICommand</code> for
         */
	virtual void executeCommand( INotification* notification ) = 0;
        /**
         * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
         *
         * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
         */
	virtual void removeCommand( std::string notificationName ) = 0;
        /**
         * Check if a Command is registered for a given Notification
         *
         * @param notificationName
         * @return whether a Command is currently registered for the given <code>notificationName</code>.
         */
	virtual bool hasCommand( std::string notificationName ) = 0;
	virtual ~IController(){};
};
/**
 *  An INotificationHandler base class.
 *  An IObserver requires a context to call a notification method from,
 *  and this class supports the IObserver by providing a contract
 *  that the context will have said notification handling method.
 */
class INotificationHandler
{
public:
    /**
     * Handle an <code>INotification</code>.
     *
     * @param notification the <code>INotification</code> to be handled
     */
    virtual void handleNotification ( INotification* notification ) = 0;
};
/**
 *  An Observer functor interface.
 *  A functor to be used to call Obsever notification handlers. IObserver
 *  has been split into two classes, one base untemplated class and one
 *  derived templated class.
 * 
 */
class IObserverFunctor
{
public:
    /**
     *  A callback.
     *  Call the Observer's callback function in the context of
     *  the Observer.
     *
     */
    virtual void notifyObserver(INotification* notification) = 0;
    /**
     * Compare an object's memory address to the notification context's memory address.
     *
     * @param memoryAddress the object to compare
     * @return boolean indicating if the object and the notification context are the same
     */
    virtual bool compareNotifyContext( unsigned int memoryAddress ) = 0;
};
/**
 * The interface definition for a PureMVC Observer.
 *
 * <p>
 * In PureMVC, <code>IObserver</code> implementors assume these responsibilities:
 * <UL>
 * <LI>Encapsulate the notification (callback) method of the interested object.</LI>
 * <LI>Encapsulate the notification context (this) of the interested object.</LI>
 * <LI>Provide methods for setting the interested object' notification method and context.</LI>
 * <LI>Provide a method for notifying the interested object.</LI>
 * </UL>
 *
 * <p>
 * PureMVC does not rely upon underlying event
 * models such as the one provided with Flash,
 * and ActionScript 3 does not have an inherent
 * event model.</p>
 *
 * <p>
 * The Observer Pattern as implemented within
 * PureMVC exists to support event driven communication
 * between the application and the actors of the
 * MVC triad.</p>
 *
 * <p>
 * An Observer is an object that encapsulates information
 * about an interested object with a notification method that
 * should be called when an </code>INotification</code> is broadcast. The Observer then
 * acts as a proxy for notifying the interested object.
 *
 * <p>
 * Observers can receive <code>Notification</code>s by having their
 * <code>notifyObserver</code> method invoked, passing
 * in an object implementing the <code>INotification</code> interface, such
 * as a subclass of <code>Notification</code>.</p>
 *
 * @see IView
 * @see INotification
 */
template<class T>
class IObserver : public IObserverFunctor
{
public:
        /**
         * Set the notification method.
         *
         * <p>
         * The notification method should take one parameter of type <code>INotification</code></p>
         *
         * @param notifyMethod the notification (callback) method of the interested object
         */
	virtual void setNotifyMethod( void(T::*fptr)(INotification*) ) = 0;
        /**
         * Set the notification context.
         *
         * @param notifyContext the notification context (this) of the interested object
         */
	virtual void setNotifyContext( T* notifyContext ) = 0;

	virtual ~IObserver(){};
};
/**
 * The interface definition for a PureMVC Proxy.
 *
 * <p>
 * In PureMVC, <code>IProxy</code> implementors assume these responsibilities:</p>
 * <UL>
 * <LI>Implement a common method which returns the name of the Proxy.</LI>
 * <LI>Provide methods for setting and getting the data object.</LI>
 * </UL>
 * <p>
 * Additionally, <code>IProxy</code>s typically:</p>
 * <UL>
 * <LI>Maintain references to one or more pieces of model data.</LI>
 * <LI>Provide methods for manipulating that data.</LI>
 * <LI>Generate <code>INotifications</code> when their model data changes.</LI>
 * <LI>Expose their name as a <code>public static const</code> called <code>NAME</code>, if they are not instantiated multiple times.</LI>
 * <LI>Encapsulate interaction with local or remote services used to fetch and persist model data.</LI>
 * </UL>
 */
template<class T>
class IProxy : public virtual INotifier
{
public:
        /**
         * Get the Proxy name
         *
         * @return the Proxy instance name
         */
	virtual std::string getProxyName() = 0;
        /**
         * Set the data object
         *
         * @param data the data object
         */
	virtual void setData( T data ) = 0;
        /**
         * Get the data object
         *
         * @return the data as type Object
         */
	virtual T getData() = 0;
        /**
         * Called by the Model when the Proxy is registered
         */
	virtual void onRegister() = 0;
        /**
         * Called by the Model when the Proxy is removed
         */
	virtual void onRemove() = 0;

};
/**
 * The interface definition for a PureMVC Model.
 *
 * <p>
 * In PureMVC, <code>IModel</code> implementors provide
 * access to <code>IProxy</code> objects by named lookup. </p>
 *
 * <p>
 * An <code>IModel</code> assumes these responsibilities:</p>
 *
 * <UL>
 * <LI>Maintain a cache of <code>IProxy</code> instances</LI>
 * <LI>Provide methods for registering, retrieving, and removing <code>IProxy</code> instances</LI>
 * </UL>
 */
class IModel : public virtual IMultitonKeyHeir
{
public:
        /**
         * Register an <code>IProxy</code> instance with the <code>Model</code>.
         *
         * @param proxyName the name to associate with this <code>IProxy</code> instance.
         * @param proxy an object reference to be held by the <code>Model</code>.
         */
	virtual void registerProxy( IRegisterable* proxy ) = 0;
        /**
         * Retrieve an <code>IProxy</code> instance from the Model.
         *
         * @param proxyName
         * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
         */
	virtual IRegisterable* retrieveProxy( std::string proxyName ) = 0;
        /**
         * Remove an <code>IProxy</code> instance from the Model.
         *
         * @param proxyName name of the <code>IProxy</code> instance to be removed.
         * @return the <code>IProxy</code> that was removed from the <code>Model</code>
         */
	virtual IRegisterable* removeProxy( std::string proxyName ) = 0;
        /**
         * Check if a Proxy is registered
         *
         * @param proxyName
         * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
         */
	virtual bool hasProxy( std::string proxyName ) = 0;
	virtual ~IModel(){};
};

/**
 * The untemplated portion of the interface definition for a PureMVC Mediator.
 *
 * IMediator has been split into two pieces to deal with C++'s template system.
 * <p>
 * In PureMVC, <code>IMediator</code> implementors assume these responsibilities:</p>
 * <UL>
 * <LI>Implement a common method which returns a list of all <code>INotification</code>s
 * the <code>IMediator</code> has interest in.</LI>
 * <LI>Implement a notification callback method.</LI>
 * <LI>Implement methods that are called when the IMediator is registered or removed from the View.</LI>
 * </UL>
 * <p>
 * Additionally, <code>IMediator</code>s typically:
 * <UL>
 * <LI>Act as an intermediary between one or more view components such as text boxes or
 * list controls, maintaining references and coordinating their behavior.</LI>
 * <LI>In Flash-based apps, this is often the place where event listeners are
 * added to view components, and their handlers implemented.</LI>
 * <LI>Respond to and generate <code>INotifications</code>, interacting with of
 * the rest of the PureMVC app.
 * </UL></p>
 * <p>
 * When an <code>IMediator</code> is registered with the <code>IView</code>,
 * the <code>IView</code> will call the <code>IMediator</code>'s
 * <code>listNotificationInterests</code> method. The <code>IMediator</code> will
 * return an <code>Array</code> of <code>INotification</code> names which
 * it wishes to be notified about.</p>
 *
 * <p>
 * The <code>IView</code> will then create an <code>Observer</code> object
 * encapsulating that <code>IMediator</code>'s (<code>handleNotification</code>) method
 * and register it as an Observer for each <code>INotification</code> name returned by
 * <code>listNotificationInterests</code>.</p>
 *
 * <p>
 * A concrete IMediator implementor usually looks something like this:</p>
 *
 * <code>An example goes here</code>
 *
 * @see INotification
 */
template<class T>
class IMediatorRestricted : public virtual INotifier, public INotificationHandler
{
public:
        /**
         * Get the <code>IMediator</code> instance name
         *
         * @return the <code>IMediator</code> instance name
         */
	virtual std::string getMediatorName() = 0;
        /**
         * List <code>INotification</code> interests.
         *
         * @return an <code>Array</code> of the <code>INotification</code> names this <code>IMediator</code> has an interest in.
         */
	virtual std::vector<std::string> listNotificationInterests() = 0;
        /**
         * Called by the View when the Mediator is registered
         */
	virtual void onRegister() = 0;
        /**
         * Called by the View when the Mediator is removed
         */
	virtual void onRemove() = 0;

        virtual ~IMediatorRestricted(){};
};
/**
 *  The templated portion of IMediator.
 *
 *  IMediatorTemplated inherits from IMediatorRestricted and adds some
 *  required template functions.
 *
 */
template<class T>
class IMediatorTemplated : public IMediatorRestricted
{
public:
        /**
         * Get the <code>IMediator</code>'s view component.
         *
         * @return Object the view component
         */
	virtual T getViewComponent() = 0;
        /**
         * Set the <code>IMediator</code>'s view component.
         *
         * @param Object the view component
         */
	virtual void setViewComponent( T viewComponent ) = 0;
        
	virtual ~IMediatorTemplated(){};

};
/**
 * The interface definition for a PureMVC View.
 *
 * <p>
 * In PureMVC, <code>IView</code> implementors assume these responsibilities:</p>
 *
 * <p>
 * In PureMVC, the <code>View</code> class assumes these responsibilities:
 * <UL>
 * <LI>Maintain a cache of <code>IMediator</code> instances.</LI>
 * <LI>Provide methods for registering, retrieving, and removing <code>IMediators</code>.</LI>
 * <LI>Managing the observer lists for each <code>INotification</code> in the application.</LI>
 * <LI>Providing a method for attaching <code>IObservers</code> to an <code>INotification</code>'s observer list.</LI>
 * <LI>Providing a method for broadcasting an <code>INotification</code>.</LI>
 * <LI>Notifying the <code>IObservers</code> of a given <code>INotification</code> when it broadcast.</LI>
 * </UL>
 *
 * @see IMediator
 * @see IObserver
 * @see INotification
 */
class IView : public virtual IMultitonKeyHeir
{
public:
        /**
         * Register an <code>IObserver</code> to be notified
         * of <code>INotifications</code> with a given name.
         *
         * @param notificationName the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
         * @param observer the <code>IObserver</code> to register
         */
	virtual void registerObserver( std::string notificationName, IObserverFunctor* observer ) = 0;
        /**
         * Remove an observer from the observer list for a given Notification name that has a context
         * object stored at <code>contextAddress</code>.
         * <p>
         * @param notificationName which observer list to remove from
         * @param contextAddress remove the observer with this address as the address of their notifyContext
         */
	virtual void removeObserver( std::string notificationName, unsigned int contextAddress ) = 0;
        /**
         * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
         *
         * <p>
         * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
         * list are notified and are passed a reference to the <code>INotification</code> in
         * the order in which they were registered.</p>
         *
         * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
         */
	virtual void notifyObservers( INotification* note ) = 0;
        /**
         * Register an <code>IMediator</code> instance with the <code>View</code>.
         *
         * <p>
         * Registers the <code>IMediator</code> so that it can be retrieved by name,
         * and further interrogates the <code>IMediator</code> for its
         * <code>INotification</code> interests.</p>
         * <p>
         * If the <code>IMediator</code> returns any <code>INotification</code>
         * names to be notified about, an <code>Observer</code> is created encapsulating
         * the <code>IMediator</code> instance's <code>handleNotification</code> method
         * and registering it as an <code>Observer</code> for all <code>INotifications</code> the
         * <code>IMediator</code> is interested in.</p>
         *
         * @param mediatorName the name to associate with this <code>IMediator</code> instance
         * @param mediator a reference to the <code>IMediator</code> instance
         */
	virtual void registerMediator( IMediatorRestricted* mediator ) = 0;
        /**
         * Retrieve an <code>IMediator</code> from the <code>View</code>.
         *
         * @param mediatorName the name of the <code>IMediator</code> instance to retrieve.
         * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
         */
	virtual IMediatorRestricted* retrieveMediator( std::string mediatorName ) = 0;
        /**
         * Remove an <code>IMediator</code> from the <code>View</code>.
         *
         * @param mediatorName name of the <code>IMediator</code> instance to be removed.
         * @return the <code>IMediator</code> that was removed from the <code>View</code>
         */
	virtual IMediatorRestricted* removeMediator( std::string mediatorName ) = 0;
        /**
         * Check if a Mediator is registered or not
         *
         * @param mediatorName
         * @return whether a Mediator is registered with the given <code>mediatorName</code>.
         */
	virtual bool hasMediator( std::string mediatorName ) = 0;
	virtual ~IView(){};
};
/**
 * The interface definition for a PureMVC Facade.
 *
 * <p>
 * The Facade Pattern suggests providing a single
 * class to act as a central point of communication
 * for a subsystem. </p>
 *
 * <p>
 * In PureMVC, the Facade acts as an interface between
 * the core MVC actors (Model, View, Controller) and
 * the rest of your application.</p>
 *
 * @see IModel
 * @see IView
 * @see IController
 * @see ICommand
 * @see INotification
 */
class IFacade : public INotifier
{
public:
        /**
         * Register an <code>IProxy</code> with the <code>Model</code> by name.
         *
         * @param proxy the <code>IProxy</code> to be registered with the <code>Model</code>.
         */
	virtual void registerProxy( IRegisterable* proxy ) = 0;
        /**
         * Retrieve a <code>IProxy</code> from the <code>Model</code> by name.
         *
         * @param proxyName the name of the <code>IProxy</code> instance to be retrieved.
         * @return the <code>IProxy</code> previously regisetered by <code>proxyName</code> with the <code>Model</code>.
         */
	virtual IRegisterable* retrieveProxy( std::string proxyName ) = 0;
        /**
         * Remove an <code>IProxy</code> instance from the <code>Model</code> by name.
         *
         * @param proxyName the <code>IProxy</code> to remove from the <code>Model</code>.
         * @return the <code>IProxy</code> that was removed from the <code>Model</code>
         */
	virtual IRegisterable* removeProxy( std::string proxyName ) = 0;
        /**
         * Check if a Proxy is registered
         *
         * @param proxyName
         * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
         */
	virtual bool hasProxy( std::string proxyName ) = 0;
        /**
         * Register an <code>ICommand</code> with the <code>Controller</code>.
         *
         * @param noteName the name of the <code>INotification</code> to associate the <code>ICommand</code> with.
         * @param commandClassRef a reference to the <code>Class</code> of the <code>ICommand</code>.
         */
	//void                    registerCommand	( std::string noteName, ICommand* commandClassRef );
        /**
         * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
         *
         * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
         */
	virtual void removeCommand( std::string notificationName ) = 0;
        /**
         * Check if a Command is registered for a given Notification
         *
         * @param notificationName
         * @return whether a Command is currently registered for the given <code>notificationName</code>.
         */
	virtual bool hasCommand( std::string notificationName ) = 0;
        /**
         * Register an <code>IMediator</code> instance with the <code>View</code>.
         *
         * @param mediator a reference to the <code>IMediator</code> instance
         */
	virtual void registerMediator( IMediatorRestricted* mediator ) = 0;
        /**
         * Retrieve an <code>IMediator</code> instance from the <code>View</code>.
         *
         * @param mediatorName the name of the <code>IMediator</code> instance to retrievve
         * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
         */
	virtual IMediatorRestricted* retrieveMediator( std::string mediatorName ) = 0;
        /**
         * Remove a <code>IMediator</code> instance from the <code>View</code>.
         *
         * @param mediatorName name of the <code>IMediator</code> instance to be removed.
         * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
         */
	virtual IMediatorRestricted* removeMediator( std::string mediatorName ) = 0;
        /**
         * Check if a Mediator is registered or not
         *
         * @param mediatorName
         * @return whether a Mediator is registered with the given <code>mediatorName</code>.
         */
	virtual bool hasMediator( std::string mediatorName ) = 0;
        /**
         * Notify <code>Observer</code>s.
         * <p>
         * This method is left public mostly for backward
         * compatibility, and to allow you to send custom
         * notification classes using the facade.</p>
         *<p>
         * Usually you should just call sendNotification
         * and pass the parameters, never having to
         * construct the notification yourself.</p>
         *
         * @param notification the <code>INotification</code> to have the <code>View</code> notify <code>Observers</code> of.
         */
	virtual void notifyObservers( INotification* notification ) = 0;
};

#endif	/* _PMVCPPBASE_H */

