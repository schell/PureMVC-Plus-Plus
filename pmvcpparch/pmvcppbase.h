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
//  INotifier
//--------------------------------------
class INotifier
{
public:
    virtual void sendNotification   ( std::string notificationName, IBody* body, std::string type) = 0;
    virtual void sendNotification   ( std::string notificationName, std::string type ) = 0;
    virtual void sendNotification   ( std::string notificationName, IBody* body ) = 0;
    virtual void sendNotification   ( std::string notificationName ) = 0;
    virtual void initializeNotifier ( std::string key ) = 0;
    virtual 	 ~INotifier         (){};
};

class INotification
{
public:
	virtual std::string getName         () = 0;
	virtual void        setBody         ( IBody* body ) = 0;
	virtual IBody*      getBody         () = 0;
	virtual void        setType         ( std::string type ) = 0;
	virtual std::string getType         () = 0;
	virtual             ~INotification  (){};
};

class ICommand : public INotifier
{
public:
	virtual void execute	( INotification* notification ) = 0;
	virtual      ~ICommand	(){};
};

class IController
{
public:
                void registerCommand( std::string notificationName, ICommand* commandClassRef );
	virtual void executeCommand ( INotification* notification ) = 0;
	virtual void removeCommand  ( std::string notificationName ) = 0;
	virtual bool hasCommand     ( std::string notificationName ) = 0;
	virtual      ~IController   (){};
};

class IObserver
{
public:
	virtual void setNotifyMethod        ( void (*notifyMethod) (INotification*) ) = 0;
	virtual void setNotifyContext       ( IBody* notifyContext ) = 0;
	virtual void notifyObserver         ( INotification* notification ) = 0;
	virtual bool compareNotifyContext   ( IBody* obj ) = 0;
	virtual      ~IObserver             (){};
};

class IProxy : public INotifier
{
public:
	virtual std::string getProxyName() = 0;
	virtual void        setData	( IBody* data ) = 0;
	virtual IBody*      getData	() = 0;
	virtual void        onRegister	() = 0;
	virtual void        onRemove	() = 0;

};

class IModel
{
public:
	virtual void 	registerProxy	( IProxy* proxy ) = 0;
	virtual IProxy* retrieveProxy	( std::string proxyName ) = 0;
	virtual IProxy* removeProxy	( std::string proxyName ) = 0;
	virtual bool 	hasProxy	( std::string proxyName ) = 0;
	virtual 	~IModel		(){};
};

class IMediator : public INotifier
{
public:
	virtual std::string              getMediatorName            () = 0;
	virtual IBody*                   getViewComponent           () = 0;
	virtual void                     setViewComponent           ( IBody* viewComponent ) = 0;
	virtual std::vector<std::string> listNotificationInterests  () = 0;
	virtual void                     handleNotification         ( INotification* notification ) = 0;
	virtual void 			 onRegister                 () = 0;
	virtual void 			 onRemove                   () = 0;
	virtual 			 ~IMediator                 ();

};

class IView
{
public:
	virtual void 		registerObserver( std::string notificationName, IObserver* observer ) = 0;
	virtual void 		removeObserver	( std::string notificationName, IBody* notifyContext ) = 0;
	virtual void 		notifyObservers	( INotification* note ) = 0;
	virtual void 		registerMediator( IMediator* mediator ) = 0;
	virtual IMediator* 	retrieveMediator( std::string mediatorName ) = 0;
	virtual IMediator* 	removeMediator	( std::string mediatorName ) = 0;
	virtual bool 		hasMediator	( std::string mediatorName ) = 0;
	virtual 		~IView();
};

class IFacade : public INotifier
{
public:
	virtual void 		registerProxy	( IProxy* proxy ) = 0;
	virtual IProxy* 	retrieveProxy	( std::string proxyName ) = 0;
	virtual IProxy* 	removeProxy	( std::string proxyName ) = 0;
	virtual bool 		hasProxy	( std::string proxyName ) = 0;
	void                    registerCommand	( std::string noteName, ICommand* commandClassRef );
	virtual void 		removeCommand	( std::string notificationName ) = 0;
	virtual bool 		hasCommand	( std::string notificationName ) = 0;
	virtual void 		registerMediator( IMediator* mediator ) = 0;
	virtual IMediator* 	retrieveMediator( std::string mediatorName ) = 0;
	virtual IMediator* 	removeMediator	( std::string mediatorName ) = 0;
	virtual bool 		hasMediator	( std::string mediatorName ) = 0;
	virtual void 		notifyObservers	( INotification* notification ) = 0;
};

#endif	/* _PMVCPPBASE_H */

