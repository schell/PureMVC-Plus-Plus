/**
 *	Application entry point for littlemenu.
 *	This is a tiny application that displays a menu using
 *	the C++ version of the PureMVC framework.
 *
 *	author Schell Scivally
 *	since 15.12.2009
 */
#include <iostream>
#include <sstream>
#include <string>
#include "pmvcpparch.h"

using namespace std;

//--------------------------------------
//  Notification Definitions
//--------------------------------------
class NoteDefs
{
public:
	/**
	 *	Notification names.
	 */
	static const string STARTUP;				// triggers the app startup sequence
	static const string PATTERNS_REGISTERED;	// alerts the app that proxies and mediators have been registered
	static const string SET;					// sets something
	static const string GET;					// makes a request to get something
	static const string DISPLAY;				// display something
	static const string QUIT;					// quit the app
	/**
	 *	Notification types
	 */
	static const string MENU;					// the menu
};
// definitions for note names
const string NoteDefs::STARTUP = "startUp";
const string NoteDefs::PATTERNS_REGISTERED = "patternsRegistered";
const string NoteDefs::SET = "set";
const string NoteDefs::GET = "get";
const string NoteDefs::DISPLAY = "display";
// definitions for note types
const string NoteDefs::MENU = "menu";
//--------------------------------------
//  Notification Body Definitions
//--------------------------------------
class MenuNotificationBody : public IBody
{
public:	
	vector<string> data;
	
	MenuNotificationBody(vector<string> menu) : data(menu) {}
	string getType()
	{
		return "MenuNotificationBody";
	}
};
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
	vector<string> listNotificationInterests()
	{
		vector<string> interests;
		
		interests.push_back(NoteDefs::PATTERNS_REGISTERED);
		interests.push_back(NoteDefs::DISPLAY);
		
		return interests;
	}
	// deal with interesting notifications
	void handleNotification(INotification* note)
	{
		cout << "CLIMediator::handleNotification(name:" << note->getName() << " type:" << note->getType() <<")\n";
		
		string name = note->getName();
		string type = note->getType();
		IBody* body = note->getBody();
		// handle the notification
		// if the app is ready, ask for the menu
		if(name == NoteDefs::PATTERNS_REGISTERED)
			this->sendNotification(NoteDefs::GET, NoteDefs::MENU);
		else if(name == NoteDefs::DISPLAY)
		{
			if(type == NoteDefs::MENU)
			{
				cout << "	menu received...\n";
				this->promptUser(dynamic_cast<MenuNotificationBody*>(body)->data);
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
		MenuNotificationBody* newMenu = new MenuNotificationBody(menu);
		// send it off to someone who needs it...
		this->sendNotification(NoteDefs::SET, newMenu, NoteDefs::MENU);
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
		facade->registerMediator(new CLIMediator(CLIMediator::NAME, false));
		// register proxies
		facade->registerProxy(new MenuProxy(MenuProxy::NAME));
		
		// now let the app know we're done registering things...
		facade->sendNotification(NoteDefs::PATTERNS_REGISTERED);
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
		cout << "Set::execute(type:" << note->getType() << ")\n";
		
		IFacade* facade = this->getFacade();
		string type = note->getType();
		// handle the request
		if(type == NoteDefs::MENU)
		{
			MenuNotificationBody* menuBody = dynamic_cast<MenuNotificationBody*>(note->getBody());
			vector<string> menu = menuBody->data;
			cout << "	adding " << menu.at(menu.size() - 1) << " to the menu...\n";
			// get the menu proxy
			MenuProxy* menuProxy = dynamic_cast<MenuProxy*>(facade->retrieveProxy(MenuProxy::NAME));
			menuProxy->setData(menu);
			menuBody->data = menuProxy->getData();
			// send the menu back out to be displayed
			facade->sendNotification(NoteDefs::DISPLAY, menuBody, NoteDefs::MENU);
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
		cout << "Get::execute(type:" << note->getType() << ")\n";
		
		IFacade* facade = this->getFacade();
		string type = note->getType();
		// handle the request
		if(type == NoteDefs::MENU)
		{
			cout << "	requested the menu...\n";
			// get the menu proxy
			MenuProxy* menuProxy = dynamic_cast<MenuProxy*>(facade->retrieveProxy(MenuProxy::NAME));
			vector<string> menu = menuProxy->getData();
			// send the menu out to who needs it...
			facade->sendNotification(NoteDefs::DISPLAY, new MenuNotificationBody(menu), NoteDefs::MENU);
		}
	}
};
/**
 *	Register our commands.
 */
void registerCommands(Facade* facade)
{
	// register the command to respond to notification definitions
	facade->registerCommand<Startup>(NoteDefs::STARTUP);
	facade->registerCommand<Set>(NoteDefs::SET);
	facade->registerCommand<Get>(NoteDefs::GET);
}
//--------------------------------------
//  MAIN
//--------------------------------------
int main(int argc, char** argv)
{
	cout << "\n-- littlemenu v0.1 by Schell Scivally --\n\n";
	// set some key for the app, preferably one that won't collide
	// with some other one down the road
	string applicationKey = "littlemenuApplicationKey123456";
	// create an instance of the facade
	Facade* facade = Facade::getInstance(applicationKey);
	// register our commands through the facade
	registerCommands(facade);
	// startup the app by calling the startup command
	facade->sendNotification(NoteDefs::STARTUP);
	
	// cleanup the app for quitting
	Facade::removeCore(applicationKey);
	
	cout << "\n- bye!\n\n";
	return 0;
}