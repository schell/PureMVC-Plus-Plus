/**
 *	Application entry point for threads.
 *	This is a tiny application that displays the
 *	results of multiple threads using the C++ 
 *	version of the PureMVC framework.
 *
 *	author Schell Scivally
 *	since 15.12.2009
 *
 *	PureMVC++ - Copyright(c) 2009 Schell Scivally Enterprise, some rights reserved.
 *	Your reuse is governed by the Creative Commons Attribution 3.0 United States License
 *
 */
#include <iostream>
#include <sstream>
#include <string>
#include <pthread.h>
#include <time.h>
#include "pmvcpp.h"

using namespace std;
using namespace PureMVC;

//--------------------------------------
//  Notification Definitions
//--------------------------------------
// let's enumerate our notification names and types
class n_name
{
public:
    enum name
    {
		NIL,					// nothing at all
        STARTUP,                // triggers the app startup sequence
        PATTERNS_REGISTERED,	// alerts the app that proxies and mediators have been registered
		CREATE,					// create something
        DISPLAY,				// display something
        QUIT                    // quit
	};
	static map<int, string> toString;
	static void init()
	{
		n_name::toString[NIL]					= "null";
		n_name::toString[STARTUP] 				= "startup";
        n_name::toString[PATTERNS_REGISTERED] 	= "patterns registered";
        n_name::toString[CREATE] 				= "create";			    
        n_name::toString[DISPLAY] 				= "display";			    
		n_name::toString[QUIT] 					= "quit";                       
	}
};
map<int, string> n_name::toString;
class n_type
{
public:
    enum type
    {
		NIL,	// nothing
		THREAD,	// a thread
		PROMPT	// some prompt
	};
	static map<int, string> toString;
	static void init()
	{
		n_type::toString[NIL] = "null";
		n_type::toString[THREAD] = "thread";
		n_type::toString[PROMPT] = "prompt";
	}
};
map<int, string> n_type::toString;
//--------------------------------------
//  Proxies
//--------------------------------------
/**
 *	ThreadProxy - holds references to our threads
 */
class ThreadProxy : public Proxy<int>
{
public:
	static const string NAME;
	
	ThreadProxy(string proxyName) : Proxy<int>(proxyName) {}
	void onRegister()
	{
		cout << "ThreadProxy::onRegister()\n";
		this->setData(0);
	}
	void onRemove()
	{
		cout << "ThreadProxy::onRemove()\n";
	}
	void createThreads(vector<int> threadList)
	{
		this->seconds = threadList;
		this->totalThreads = threadList.size();
		cout << "ThreadProxy::createThreads() creating " << threadList.size() << " threads...\n";
		// create the threads
		for(size_t i = 0; i < threadList.size(); ++i)
		{
			pthread_t thread;
			pthread_create(&thread, NULL, ThreadProxy::wait, (void*) this);
			this->threads.push_back(thread);
			cout << "	created " << i + 1 << " threads...\n";
		}
		// go back to displaying prompt while threads finish...
		this->sendNotification(n_name::DISPLAY);
	}
	int getTimeForNextThread()
	{
		int num = this->seconds.at(0);
		this->seconds.erase(this->seconds.begin());
		return num;
	}
	int complete()
	{
		return completeThreads == totalThreads;
	}
private:	
	// our vector of secthreads
	vector<pthread_t> threads;
	vector<int> seconds;
	int completeThreads;
	int totalThreads;
	
	static void* wait(void* ptr)
	{
		ThreadProxy* threadProxy = static_cast<ThreadProxy*>(ptr);
		int seconds = threadProxy->getTimeForNextThread();
		clock_t endwait;
		endwait = clock() + seconds * CLOCKS_PER_SEC;
		while(clock() < endwait)
		{
			// we're waiting
		}
		cout << seconds << " second thread done.\n";
		threadProxy->completeThreads++;
		return 0;
	}
};
// define the proxy's name
const string ThreadProxy::NAME = "ThreadProxy";
//--------------------------------------
//  Mediators
//--------------------------------------
/**
 *	CLIMediator - mediates interaction between the terminal and the user.
 */
class CLIMediator : public Mediator<bool>
{
public:
	static const string NAME;
	
	CLIMediator(string mediatorName, bool viewComponent) : Mediator<bool>(mediatorName, viewComponent) {}
	void onRegister()
	{
		cout << "CLIMediator::onRegister()\n";
	}
	void onRemove()
	{
		cout << "CLIMediator::onRemove()\n";
	}
	// list all of the notifications we're interested in
	vector<int> listNotificationInterests()
	{
		vector<int> interests;
		
		interests.push_back(n_name::PATTERNS_REGISTERED);
		interests.push_back(n_name::DISPLAY);
		
		return interests;
	}
	// deal with interesting notifications
	void handleNotification(INotification* note)
	{	
		int name = note->getName();
		int type = note->getType();
		
		cout << "CLIMediator::handleNotification(name:" << n_name::toString[name] << " type:" << n_type::toString[type] <<")\n";
			
		// handle the notification
		switch(name)
		{
			case n_name::PATTERNS_REGISTERED:
			case n_name::DISPLAY:
				this->promptUser();
			break;
			
			default:
			{}
		}
	}
	void promptUser()
	{
		cout << "\n\n";
		int numThreads = this->getNumThreads();;
		vector<int> secondList;
		string input;
		for(int i = 0; i < numThreads; ++i)
		{
			secondList.push_back(this->getSeconds(i));
		}
		cout << "\n";
		
		if(numThreads != 0)
			this->sendNotification(n_name::CREATE, (void*) &secondList, n_type::THREAD);
	}
	int getNumThreads()
	{
		int threads;
		string input = "";
		while(true) 
		{
			cout << "How many threads should I create? [0-10]:";
			getline(cin, input);
			if(input == "q")
			{
				this->sendNotification(n_name::QUIT);
				return 0;
			}
			stringstream inputStream(input);
			if(inputStream >> threads && threads >= 0 && threads <= 10)
				return threads;
		}
	}
	int getSeconds(int num)
	{
		int seconds;
		string input = "";
		while(true) 
		{
			cout << "How many seconds should thread #" << num + 1 << " operate before terminating? [1-60]:";
			getline(cin, input);
			if(input == "q")
			{
				this->sendNotification(n_name::QUIT);
				return 0;
			}
			stringstream inputStream(input);
			if(inputStream >> seconds && seconds >= 1 && seconds <= 60)
				return seconds;
		}
	}
};
// define the mediator's name
const string CLIMediator::NAME = "CLIMediator";
//--------------------------------------
//  Commands
//--------------------------------------
/**
 *	Startup - registers our proxies and mediators.
 */
class Startup : public SimpleCommand
{
public:
	void execute(INotification* note)
	{
		cout << "Startup::execute()\n";
		IFacade* facade = this->getFacade();
		// register mediators
		facade->registerMediator(new CLIMediator(CLIMediator::NAME, false));
		// register proxies
		facade->registerProxy(new ThreadProxy(ThreadProxy::NAME));
		
		// now let the app know we're done registering things...
		facade->sendNotification(n_name::PATTERNS_REGISTERED);
	}
};
/**
 *	Create - gets things (threads).
 */
class Create : public SimpleCommand
{
public:
	void execute(INotification* note)
	{	
		IFacade* facade = this->getFacade();
		int type = note->getType();
		
		cout << "Get::execute(type:" << n_type::toString[type] << ")\n";
		
		// handle the request
		if(type == n_type::THREAD)
		{
			ThreadProxy* threadProxy = static_cast<ThreadProxy*>(facade->retrieveProxy(ThreadProxy::NAME));
			vector<int> threadList = *((vector<int>*) note->getBody());
			threadProxy->createThreads(threadList);
		}
	}
};
/**
 *	Register our commands.
 */
void registerCommands(Facade* facade)
{
	// register the command to respond to notification definitions
	facade->registerCommand<Startup>(n_name::STARTUP);
	facade->registerCommand<Create>(n_name::CREATE);
}
//--------------------------------------
//  MAIN
//--------------------------------------
int main(int argc, char** argv)
{
	cout << "\n-- threads v0.1 by Schell Scivally --\n";
	cout << "	entering 'q' quits the program\n\n";
	
	// initialize our note names and types
	n_name::init();
	n_type::init();
	// set some key for the app, preferably one that won't collide
	// with some other one down the road
	string applicationKey = "threadsApplicationKey123456";
	// create an instance of the facade
	Facade* facade = Facade::getInstance(applicationKey);
	// register our commands through the facade
	registerCommands(facade);
	// startup the app by calling the startup command
	facade->sendNotification(n_name::STARTUP);
	
	// cleanup the app for quitting
	Facade::removeCore(applicationKey);
	
	cout << "\n- bye!\n\n";
	return 0;
}