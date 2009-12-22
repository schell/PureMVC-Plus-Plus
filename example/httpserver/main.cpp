/**
 *	Application entry point for httpserver.
 *	This is a tiny http server using
 *	the C++ version of the PureMVC framework.
 *
 *	author Schell Scivally
 *	since 15.12.2009
 *
 *	PureMVC++ - Copyright(c) 2009 Schell Scivally Enterprise, some rights reserved.
 *	Your reuse is governed by the Creative Commons Attribution 3.0 United States License
 *
 */
#include "controller/Startup.h"
#include "controller/Set.h"
#include "controller/Listen.h"
#include "pmvcpp.h"
#include "common.h"

using namespace PureMVC;
//--------------------------------------
//  Notification Names & Types
//--------------------------------------
std::map<int, std::string> n_name::toString;
std::map<int, std::string> n_type::toString;
//--------------------------------------
//  CommandRegistration
//--------------------------------------
void registerCommands(Facade* facade)
{
    facade->registerCommand<Startup>(n_name::STARTUP);
    facade->registerCommand<Set>(n_name::SET);
    facade->registerCommand<Listen>(n_name::LISTEN);
}
//--------------------------------------
//  MAIN
//--------------------------------------
int main(int argc, char** argv)
{
	std::cout << "\n-- littlemenu v0.1 by Schell Scivally --\n\n";
	// initialize our note names and types
	n_name::init();
	n_type::init();
	// set some key for the app, preferably one that won't collide
	// with some other one down the road
	std::string applicationKey = "httpserver";
	// create an instance of the facade
	Facade* facade = Facade::getInstance(applicationKey);
        // store our command line args
        CliArgs cliArgs(argc, argv);
	// register our commands through the facade
	registerCommands(facade);
	// startup the app by calling the startup command
	facade->sendNotification(n_name::STARTUP, &cliArgs);

	// cleanup the app for quitting
	Facade::removeCore(applicationKey);

	std::cout << "\n- bye!\n\n";
	return 0;
}