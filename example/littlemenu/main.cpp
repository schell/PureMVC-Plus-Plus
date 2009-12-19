/**
 *	Application entry point for littlemenu.
 *	This is a tiny application that displays a menu using
 *	the C++ version of the PureMVC framework.
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
		NIL,
        STARTUP,                // triggers the app startup sequence
        PATTERNS_REGISTERED,	// alerts the app that proxies and mediators have been registered
        SET,					// sets something
        GET,					// makes a request to get something
        DISPLAY,				// display something
        QUIT                    // quit the app
	};
	static map<int, string> toString;
	static void init()
	{
		n_name::toString[NIL]					= "null";
		n_name::toString[STARTUP] 				= "startup";
        n_name::toString[PATTERNS_REGISTERED] 	= "patterns registered";
        n_name::toString[SET] 					= "set";
        n_name::toString[GET] 					= "get";				    
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
        MENU    // the menu
	};
	static map<int, string> toString;
	static void init()
	{
		n_type::toString[NIL] = "null";
		n_type::toString[MENU] = "menu";
	}
};
map<int, string> n_type::toString;
//--------------------------------------
//  Proxies
//--------------------------------------
/**
 *	MenuProxy - holds the choices for our menu.
 */
class MenuProxy : public Proxy<vector<string> >
{
public:
	static const string NAME;
	
	MenuProxy(string proxyName) : Proxy<vector<string> >(proxyName) {}
	void onRegister()
	{
		cout << "MenuProxy::onRegister()\n";
		this->setData(this->getMenu());
	}
	void onRemove()
	{
		cout << "MenuProxy::onRemove()\n";
	}
	vector<string> getMenu()
	{
		cout << "MenuProxy::getMenu()\n";
		vector<string> menu;
		menu.push_back("Fox");
		menu.push_back("Bear");
		menu.push_back("Mountain Lion");
		menu.push_back("Lynx");
		menu.push_back("Bobcat");
		menu.push_back("Terradactyl");
		menu.push_back("Wolf");
		menu.push_back("Other...");
		return menu;
	}
};
// define the proxy's name
const string MenuProxy::NAME = "MenuProxy";
//--------------------------------------
//  Mediators
//--------------------------------------
/**
 *	CLIMediator - mediates interaction between the terminal and the user.
 */
class CLIMediator : public Mediator
{
public:
	static const string NAME;
	
	CLIMediator(string mediatorName) : Mediator(mediatorName) {}
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
			
		void* body = note->getBody();
		// handle the notification
		// if the app is ready, ask for the menu
		if(name == n_name::PATTERNS_REGISTERED)
			this->sendNotification(n_name::GET, n_type::MENU);
		else if(name == n_name::DISPLAY)
		{
			if(type == n_type::MENU)
			{
				cout << "	menu received...\n";
                                vector<string> menu = *((vector<string>*) body);
				this->promptUser(menu);
			}
		}
	}
	void promptUser(vector<string> menu)
	{
		size_t choices = menu.size();
		int choice = 0;
		string input = "";
		while(choice != (int) choices)
		{
			cout << "\n- What is your favorite forest creature? -\n";
			for(size_t i = 1; i <= choices; ++i)
			{
				cout << "	" << i << ". " << menu.at(i-1) << "\n";
			}
			cout << "[1 - " << choices << " or 'q']:";
			while(true)
			{
				getline(cin, input);
				
				if(input == "q")
					return this->quit();
					
				stringstream myStream(input);
				if(myStream >> choice && choice <= (int) choices && choice > 0)
					break;
				cout << "- Wait, what? -\n[1 - " << choices << " or 'q']:";
			}
			if(choice < (int) choices)
				cout << "\n- A " << menu.at(choice - 1) << " is pretty. -\n";
		}
		cout << "\n- You like some other animal? -\nAdd your favorite animal [some animal]:";
		getline(cin, input);
		cout << "\n";
		
		// add the new animal to the list
		string other = menu.at(choices - 1);
		// swap so "Other.." stays last
		menu.at(choices - 1) = input;
		menu.push_back(other);
		// send it off to someone who needs it...
		this->sendNotification(n_name::SET, (void*) &menu, n_type::MENU);
	}
	void quit()
	{
		// there's nothing keeping control besides this mediator, so this is enough to quit.
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
		facade->registerMediator(new CLIMediator(CLIMediator::NAME));
		// register proxies
		facade->registerProxy(new MenuProxy(MenuProxy::NAME));
		
		// now let the app know we're done registering things...
		facade->sendNotification(n_name::PATTERNS_REGISTERED);
	}
};
/**
 *	Set - sets things.
 */
class Set : public SimpleCommand
{
public:
	void execute(INotification* note)
	{	
		IFacade* facade = this->getFacade();
		int type = note->getType();
		
		cout << "Set::execute(type:" << n_type::toString[type] << ")\n";
			
		// handle the request
		if(type == n_type::MENU)
		{
			vector<string> menu = *((vector<string>*) note->getBody());
			cout << "	adding " << menu.at(menu.size() - 1) << " to the menu...\n";
			// get the menu proxy
			MenuProxy* menuProxy = dynamic_cast<MenuProxy*>(facade->retrieveProxy(MenuProxy::NAME));
			menuProxy->setData(menu);
			// send the menu back out to be displayed
			facade->sendNotification(n_name::DISPLAY, (void*) &menu, n_type::MENU);
		}
	}
};
/**
 *	Get - gets things.
 */
class Get : public SimpleCommand
{
public:
	void execute(INotification* note)
	{	
		IFacade* facade = this->getFacade();
		int type = note->getType();
		
		cout << "Get::execute(type:" << n_type::toString[type] << ")\n";
		
		// handle the request
		if(type == n_type::MENU)
		{
			cout << "	requested the menu...\n";
			// get the menu proxy
			MenuProxy* menuProxy = dynamic_cast<MenuProxy*>(facade->retrieveProxy(MenuProxy::NAME));
			vector<string> menu = menuProxy->getData();
			// send the menu out to who needs it...
			facade->sendNotification(n_name::DISPLAY, (void*) &menu, n_type::MENU);
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
	facade->registerCommand<Set>(n_name::SET);
	facade->registerCommand<Get>(n_name::GET);
}
//--------------------------------------
//  MAIN
//--------------------------------------
int main(int argc, char** argv)
{
	cout << "\n-- littlemenu v0.1 by Schell Scivally --\n\n";
	// initialize our note names and types
	n_name::init();
	n_type::init();
	// set some key for the app, preferably one that won't collide
	// with some other one down the road
	string applicationKey = "littlemenuApplicationKey123456";
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