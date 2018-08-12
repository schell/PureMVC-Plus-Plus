/* 
 * File:   pmvcpp.h
 * Author: Schell Scivally - http://civiliansoftware.com
 *
 * Created on December 17, 2009, 12:56 PM
 * PureMVC++ - Copyright(c) 2009 Schell Scivally Enterprise, some rights reserved.
 * Your reuse is governed by the Creative Commons Attribution 3.0 United States License
 * 
 */

#ifndef _PMVCPP_H
#define	_PMVCPP_H

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<cstdlib>
#include<stdint.h>

/**
 *  The PureMVC namespace.
 **/
namespace PureMVC {
    /**
     *  A templated Multiton class.
     *  Multiton takes care of creating multitons of other classes.
     *  We use this instead implementing multiton code in Facade,
     *  Model, Controller, etc.
     */
    template <class T>
    class Multiton
    {
    public:
        /**
         *  Retrieve a default instance of T.
         *  Create a new default instance or return existing.
         *  @see instance(std::string key)
         */
        static T* instance()
        {
            std::string key = "key";
            return Multiton<T>::instance(key);
        }
        /**
         *  Retrieve a named instance of T.
         *  Create a new named instance of T or return one pointed to by key.
         *  @param key A string key
         */
        static T* instance(std::string key)
        {
            if(Multiton<T>::exists(key))
                return Multiton<T>::instanceMap[key];

            T* inst = new T();

            Multiton<T>::instanceMap[key] = inst;
            return inst;
        }
        /**
         *  Check existance.
         *  Check whether or not an instance of name key exists.
         *  @param key A string key
         */
        static bool exists(std::string key)
        {
            return Multiton<T>::instanceMap.find(key) != Multiton<T>::instanceMap.end();
        }
        /**
         *  Total instances.
         *  The total number of instances instantiated.
         */
        static size_t size()
        {
            return Multiton<T>::instanceMap.size();
        }
        /**
         *  Deletes an instance.
         *  Deletes one instance of key <code>key</code>.
         *
         */
        static void erase(std::string key)
        {
            Multiton<T>::instanceMap.erase(key);
        }
        /**
         *  Deletes instances.
         *  Deletes all instances, calls destructors.
         */
        static void clear()
        {
            Multiton<T>::instanceMap.clear();
        }
    private:
        Multiton();
        ~Multiton();
        Multiton(Multiton const&); // copy constructor
        Multiton& operator=(Multiton const&);
        static std::map<std::string, T*> instanceMap;
    };
    // define
    template <class T>
    std::map<std::string, T*> Multiton<T>::instanceMap;
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
        virtual void sendNotification   ( int notificationName, void* body, int notificationType) = 0;
		/**
		 * Send a <code>INotification</code>.
		 *
		 * <p>
		 * Convenience method to prevent having to construct new
		 * notification instances in our implementation code.</p>
		 *
		 * @param notificationName the name of the notification to send
		 * @param type the type of the notification (optional)
		 */
        virtual void sendNotification   ( int notificationName, int notificationType ) = 0;
		/**
         * Send a <code>INotification</code>.
         *
         * <p>
         * Convenience method to prevent having to construct new
         * notification instances in our implementation code.</p>
         *
         * @param notificationName the name of the notification to send
         * @param body the body of the notification (optional)
         */
        virtual void sendNotification   ( int notificationName, void* body ) = 0;
		/**
         * Send a <code>INotification</code>.
         *
         * <p>
         * Convenience method to prevent having to construct new
         * notification instances in our implementation code.</p>
         *
         * @param notificationName the name of the notification to send
         */
        virtual void sendNotification   ( int notificationName ) = 0;
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
            virtual int getName () = 0;
            /**
             * Set the body of the <code>INotification</code> instance
             */
            virtual void setBody( void* body ) = 0;
            /**
             * Get the body of the <code>INotification</code> instance
             */
            virtual void* getBody() = 0;
            /**
             * Set the type of the <code>INotification</code> instance
             */
            virtual void setType( int notificationType ) = 0;
            /**
             * Get the type of the <code>INotification</code> instance
             */
            virtual int getType() = 0;
            /**
             * Get the string representation of the <code>INotification</code> instance
             */
            virtual ~INotification(){};
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
            virtual void execute( INotification* notification ) = 0;
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
            //virtual void registerCommand( int notificationName, ICommand* commandClassRef )
            /**
             * Execute the <code>ICommand</code> previously registered as the
             * handler for <code>INotification</code>s with the given notification name.
             *
             * @param notification the <code>INotification</code> to execute the associated <code>ICommand</code> for
             */
            //virtual void executeCommand( INotification* notification ) = 0;
            /**
             * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
             *
             * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
             */
            virtual void removeCommand( int notificationName ) = 0;
            /**
             * Check if a Command is registered for a given Notification
             *
             * @param notificationName
             * @return whether a Command is currently registered for the given <code>notificationName</code>.
             */
            virtual bool hasCommand( int notificationName ) = 0;
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
    class IObserverRestricted
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
        virtual bool compareNotifyContext( intptr_t memoryAddress ) = 0;
        /**
         * for release
         */
        virtual ~IObserverRestricted() {}
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
    class IObserverTemplated : public IObserverRestricted
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

            virtual ~IObserverTemplated(){};
    };
    /**
     * 
     * <p>In PureMVC, <code>IProxy</code> implementors assume these responsibilities:</p>
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
             * Called by the Model when the Proxy is registered
             */
            virtual void onRegister() = 0;
            /**
             * Called by the Model when the Proxy is removed
             */
            virtual void onRemove() = 0;
            /**
             * Set the data object
             *
             * @param data the data object
             */
            virtual void setData( void* data ) = 0;
            /**
             * Get the data object
             *
             * @return the data as type Object
             */
            virtual void* getData() = 0;
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
            virtual void registerProxy( IProxy* proxy ) = 0;
            /**
             * Retrieve an <code>IProxy</code> instance from the Model.
             *
             * @param proxyName
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
             */
            virtual IProxy* retrieveProxy( std::string proxyName ) = 0;
            /**
             * Remove an <code>IProxy</code> instance from the Model.
             *
             * @param proxyName name of the <code>IProxy</code> instance to be removed.
             * @return the <code>IProxy</code> that was removed from the <code>Model</code>
             */
            virtual IProxy* removeProxy( std::string proxyName ) = 0;
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
     * 
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
    class IMediator : public virtual INotifier, public INotificationHandler
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
            virtual std::vector<int> listNotificationInterests() = 0;
            /**
             * Get the <code>IMediator</code>'s view component.
             *
             * @return Object the view component
             */
            virtual void* getViewComponent() = 0;
            /**
             * Set the <code>IMediator</code>'s view component.
             *
             * @param Object the view component
             */
            virtual void setViewComponent( void* viewComponent ) = 0;
            /**
             * Called by the View when the Mediator is registered
             */
            virtual void onRegister() = 0;
            /**
             * Called by the View when the Mediator is removed
             */
            virtual void onRemove() = 0;

            virtual ~IMediator(){};
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
            virtual void registerObserver( int notificationName, IObserverRestricted* observer ) = 0;
            /**
             * Remove an observer from the observer list for a given Notification name that has a context
             * object stored at <code>contextAddress</code>.
             * <p>
             * @param notificationName which observer list to remove from
             * @param contextAddress remove the observer with this address as the address of their notifyContext
             */
            virtual IObserverRestricted* removeObserver( int notificationName, intptr_t contextAddress ) = 0;
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
            virtual void registerMediator( IMediator* mediator ) = 0;
            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediatorName the name of the <code>IMediator</code> instance to retrieve.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
             */
            virtual IMediator* retrieveMediator( std::string mediatorName ) = 0;
            /**
             * Remove an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediatorName name of the <code>IMediator</code> instance to be removed.
             * @return the <code>IMediator</code> that was removed from the <code>View</code>
             */
            virtual IMediator* removeMediator( std::string mediatorName ) = 0;
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
    class IFacade : public INotifier, public virtual IMultitonKeyHeir
    {
    public:
            /**
             * Register an <code>IProxy</code> with the <code>Model</code> by name.
             *
             * @param proxy the <code>IProxy</code> to be registered with the <code>Model</code>.
             */
            virtual void registerProxy( IProxy* proxy ) = 0;
            /**
             * Retrieve a <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxyName the name of the <code>IProxy</code> instance to be retrieved.
             * @return the <code>IProxy</code> previously regisetered by <code>proxyName</code> with the <code>Model</code>.
             */
            virtual IProxy* retrieveProxy( std::string proxyName ) = 0;
            /**
             * Remove an <code>IProxy</code> instance from the <code>Model</code> by name.
             *
             * @param proxyName the <code>IProxy</code> to remove from the <code>Model</code>.
             * @return the <code>IProxy</code> that was removed from the <code>Model</code>
             */
            virtual IProxy* removeProxy( std::string proxyName ) = 0;
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
            virtual void removeCommand( int notificationName ) = 0;
            /**
             * Check if a Command is registered for a given Notification
             *
             * @param notificationName
             * @return whether a Command is currently registered for the given <code>notificationName</code>.
             */
            virtual bool hasCommand( int notificationName ) = 0;
            /**
             * Register an <code>IMediator</code> instance with the <code>View</code>.
             *
             * @param mediator a reference to the <code>IMediator</code> instance
             */
            virtual void registerMediator( IMediator* mediator ) = 0;
            /**
             * Retrieve an <code>IMediator</code> instance from the <code>View</code>.
             *
             * @param mediatorName the name of the <code>IMediator</code> instance to retrievve
             * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
             */
            virtual IMediator* retrieveMediator( std::string mediatorName ) = 0;
            /**
             * Remove a <code>IMediator</code> instance from the <code>View</code>.
             *
             * @param mediatorName name of the <code>IMediator</code> instance to be removed.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
             */
            virtual IMediator* removeMediator( std::string mediatorName ) = 0;
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
        int name;
        int type;
        void* body;
        /**
         * Constructor.
         *
         * @param name name of the <code>Notification</code> instance. (required)
         * @param body the <code>Notification</code> body. (optional)
         * @param type the type of the <code>Notification</code> (optional)
         */
        Notification(int notificationName, void* body, int notificationType);
        Notification(int notificationName, void* body);
        Notification(int notificationName, int notificationType);
        Notification(int notificationName);
        /**
         * Get the name of the <code>Notification</code> instance.
         *
         * @return the name of the <code>Notification</code> instance.
         */
        int getName();
        /**
         * Set the body of the <code>Notification</code> instance.
         */
        void setBody( void* body );
        /**
         * Get the body of the <code>Notification</code> instance.
         *
         * @return the body object.
         */
        void* getBody();
        /**
         * Set the type of the <code>Notification</code> instance.
         */
        void setType( int notificationType );
        /**
         * Get the type of the <code>Notification</code> instance.
         *
         * @return the type
         */
        int getType();
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
        /**
         * Create and send an <code>INotification</code>.
         *
         * <P>
         * Keeps us from having to construct new INotification
         * instances in our implementation code.
         * @param notificationName the name of the notiification to send
         * @param body the body of the notification (optional)
         * @param type the type of the notification (optional)
         */
        void sendNotification   ( int notificationName, void* body, int notificationType);
        void sendNotification   ( int notificationName, int notificationType );
        void sendNotification   ( int notificationName, void* body );
        void sendNotification   ( int notificationName );
        /**
         * Initialize this INotifier instance.
         * <P>
         * This is how a Notifier gets its multitonKey.
         * Calls to sendNotification or to access the
         * facade will fail until after this method
         * has been called.</P>
         *
         * <P>
         * Mediators, Commands or Proxies may override
         * this method in order to send notifications
         * or access the Multiton Facade instance as
         * soon as possible. They CANNOT access the facade
         * in their constructors, since this method will not
         * yet have been called.</P>
         *
         * @param key the multitonKey for this INotifier to use
         */
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
        virtual void execute(INotification* notification) = 0;
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
    class Observer : public IObserverTemplated<T>
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
         * Compare the given memory address with the stored context's address.
         *
         * @param compareContextMemoryAddress the object to compare's memory address
         * @return boolean indicating if the object and the notification context are the same
         */
        bool compareNotifyContext( intptr_t compareContextMemoryAddress )
        {
            return compareContextMemoryAddress == (intptr_t) &*this->getNotifyContext();
        }
    };
    //--------------------------------------
    //  Proxy
    //--------------------------------------
    class Proxy : public IProxy, public Notifier
    {
    public:
        /**
         * A base <code>IProxy</code> implementation.
         *
         * <P>
         * In PureMVC, <code>Proxy</code> classes are used to manage parts of the
         * application's data model. </P>
         *
         * <P>
         * A <code>Proxy</code> might simply manage a reference to a local data object,
         * in which case interacting with it might involve setting and
         * getting of its data in synchronous fashion.</P>
         *
         * <P>
         * <code>Proxy</code> classes are also used to encapsulate the application's
         * interaction with remote services to save or retrieve data, in which case,
         * we adopt an asyncronous idiom; setting data (or calling a method) on the
         * <code>Proxy</code> and listening for a <code>Notification</code> to be sent
         * when the <code>Proxy</code> has retrieved the data from the service. </P>
         *
         * @see org.puremvc.as3.multicore.core.Model Model
         */

        /**
         * Constructor
         */
        Proxy();
        Proxy(std::string proxyName, void* data);
        Proxy(std::string proxyName);
        Proxy(void* data);
        /**
         * Get the proxy name
         */
        std::string getProxyName();

        /**
         * Set the data object. Keep in mind that this sets
         * a pointer to your data object. If your object's
         * life is shorter than the life of this pointer,
         * this pointer will point to garbage. Make sure
         * the data object is stored somewhere safe.
         */
        void setData( void* data );

        /**
         * Get the data object
         */
        void* getData();

        static std::string NAME;

    protected:
        // the proxy name
        std::string proxyName;

        // the data object
        void* data;
    };
    //--------------------------------------
    //  Mediator
    //--------------------------------------
    class Mediator : public IMediator, public Notifier
    {
    public:
        /**
         * Constructor.
         */
        Mediator( std::string mediatorName, void* viewComponent );
        Mediator( std::string mediatorName );
        Mediator( void* viewComponent );
        
        /**
         * Get the name of the <code>Mediator</code>.
         * @return the Mediator name
         */
        std::string getMediatorName();

        /**
         * Set the <code>IMediator</code>'s view component.
         *
         * @param Object the view component
         */
        void setViewComponent( void* viewComponent );

        /**
         * Get the <code>Mediator</code>'s view component.
         *
         * <P>
         * Additionally, an implicit getter will usually
         * be defined in the subclass that casts the view
         * object to a type, like this:</P>
         *
         * <listing>
         *        private function get comboBox : mx.controls.ComboBox
         *        {
         *            return viewComponent as mx.controls.ComboBox;
         *        }
         * </listing>
         *
         * @return the view component
         */
        void* getViewComponent();

        /**
         * List the <code>INotification</code> names this
         * <code>Mediator</code> is interested in being notified of.
         *
         * @return Array the list of <code>INotification</code> names
         */
        virtual std::vector<int> listNotificationInterests() = 0;

        /**
         * Handle <code>INotification</code>s.
         *
         * <P>
         * Typically this will be handled in a switch statement,
         * with one 'case' entry per <code>INotification</code>
         * the <code>Mediator</code> is interested in.
         */
        virtual void handleNotification( INotification* notification ) = 0;

        /**
         * Called by the View when the Mediator is registered
         */
        virtual void onRegister() = 0;

        /**
         * Called by the View when the Mediator is removed
         */
        virtual void onRemove() = 0;

        /**
         *  Returns the name of the Mediator.
         *
         *  @return string the name
         */
        std::string getName();

    protected:
        // the mediator name
        std::string mediatorName;

        // The pointer to the view component
        void* viewComponent;
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
         * Unlike the AS3 version of PMVC, if you are going to subclass
         * Model, you should stick your initialization code in your subclass
         * constructor. Keep in mind though, that the MultitonKey for this
         * instance does not get set until after the constructor is called
         * from <code>getInstance</code>.
         *
         */
        Model();

        /**
         *  <code>Model</code> Multiton Factory method.
         *
         *  @return the instance for this Multiton key
         */
        static IModel* getInstance(std::string key);
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
        static void removeModel( std::string key );

    protected:
        // Mapping of proxyNames to IProxy instances
        std::map <std::string, IProxy*> proxyMap;
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
         * Factory method <code>View.getInstance( multitonKey )</code>.
         * Unlike the AS3 version of PMVC, if you are going to subclass
         * View, you should stick your initialization code in your subclass
         * constructor. Keep in mind though, that the MultitonKey for this
         * instance does not get set until after the constructor is called
         * from <code>getInstance</code>.
         *
         *
         */
        View( );
        /**
         * View Singleton Factory method.
         *
         * @return the Singleton instance of <code>View</code>
         */
        static IView* getInstance( std::string key );
        /**
         * Register an <code>IObserverRestricted</code> to be notified
         * of <code>INotifications</code> with a given name.
         *
         * @param notificationName the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
         * @param observer the <code>IObserverRestricted</code> to register
         */
        void registerObserver ( int notificationName, IObserverRestricted* observer );
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
         * @param contextAddress remove the observer with this memory address as its notifyContext's address
         */
        IObserverRestricted* removeObserver( int notificationName, intptr_t contextAddress );

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
        // Mapping of Mediator names to Mediator instances
        std::map<std::string, IMediator*> mediatorMap;

        // Mapping of Notification names to Observer lists
        std::map<int, std::vector<IObserverRestricted*> > observerMap;

    private:
        bool existsObserversInterestedIn(int notificationName);
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
         * <code>Controller</code> Multiton Factory method.
         *
         * @return the Multiton instance of <code>Controller</code>
         */
        static IController* getInstance( std::string key );
        /**
         * If an <code>ICommand</code> has previously been registered
         * to handle a the given <code>INotification</code>, then it is executed.
         *
         * @param note an <code>INotification</code>
         */
        template<class T>
        void executeCommand( INotification* note )
        {
            // this is a special to c++ function,
            // i feel like we're cheating here, but
            // it's nice, but we had to get rid of
            // executeCommand and registerCommand
            // from IController for it... ...if you
            // can think of a better way to keep this
            // commands stateless through this execution
            // then be my guest to revise this. - Schell
            int name = note->getName();
            // if this command isn't listed, abort
            if(! this->hasCommand(name))
                return;
            // make a new instance of the command
            ICommand* command = new T();
            command->initializeNotifier(this->getMultitonKey());
            command->execute(note);
            // get rid of the evidence
            delete command;
        };
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
         * @template commandClassRef the <code>Class</code> of the <code>ICommand</code>
         * @param notificationName the name of the <code>INotification</code>
         */
        //void registerCommand( int notificationName, ICommand* commandClassRef );
        template<class T>
        void registerCommand(int notificationName)
        {
            // if we've already registered a command for this notification
            // abort
            if(this->hasCommand(notificationName))
                return;
            // create an observer for this command
            Observer<Controller>* observer = new Observer<Controller>(&Controller::executeCommand<T>, this);
            // register the observer with the view
            this->view->registerObserver(notificationName, observer);
            // give the commanMap something to chew on
            commandMap[notificationName] = (T*) 0;
        };
        /**
         * Check if a Command is registered for a given Notification
         *
         * @param notificationName
         * @return whether a Command is currently registered for the given <code>notificationName</code>.
         */
        bool hasCommand( int notificationName );

        /**
         * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
         *
         * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
         */
        void removeCommand( int notificationName );

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
         * <P>Called automatically by the getInstance</P>
         *
         * @return void
         */
        void initializeController();

        // Local reference to View
        IView* view;

        // Mapping of Notification names to Command Class references
        std::map<int, ICommand*> commandMap;
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
         *  <code>Facade</code> multiton factory method.
         *
         *  @return the Multiton instance of the Facade
         */
        static Facade* getInstance(std::string);
        /**
         * Register an <code>ICommand</code> with the <code>Controller</code> by Notification name.
         *
         * @template commandClassRef a reference to the Class of the <code>ICommand</code>
         * @param notificationName the name of the <code>INotification</code> to associate the <code>ICommand</code> with
         */
        template<class T>
        void registerCommand( int notificationName )
        {
            dynamic_cast<Controller*>(this->controller)->registerCommand<T>(notificationName);
        };

        /**
         * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
         *
         * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
         */
        void removeCommand( int notificationName );

        /**
         * Check if a Command is registered for a given Notification
         *
         * @param notificationName
         * @return whether a Command is currently registered for the given <code>notificationName</code>.
         */
        bool hasCommand( int notificationName );

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
        void sendNotification( int notificationName, void* body, int notificationType );
        void sendNotification( int notificationName, void* body );
        void sendNotification( int notificationName, int notificationType );
        void sendNotification( int notificationName );
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
         * Not called directly, but instead when getInstance
         * is invoked.
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
         * Called automatically by getInstance.
         */
        void initializeFacade();

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

}

#endif	/* _PMVCPP_H */
