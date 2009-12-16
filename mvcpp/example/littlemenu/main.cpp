/**
 *	Application entry point for littlemenu.
 *	This is a tiny application that displays a menu using
 *	the C++ version of the PureMVC framework.
 *
 *	author Schell Scivally
 *	since 15.12.2009
 */
#include <iostream>
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
	/**
	 *	Notification types
	 */

};
// definitions for note names
const string NoteDefs::STARTUP = "startUp";
const string NoteDefs::PATTERNS_REGISTERED = "patternsRegistered";
const string NoteDefs::SET = "set";
const string NoteDefs::GET = "get";

//--------------------------------------
//  Commands
//--------------------------------------
class Set : public SimpleCommand
{
public:
	
};
//--------------------------------------
//  MAIN
//--------------------------------------

int main(int argc, char** argv)
{
	string applicationKey = "SomeKeyThatProbablyWillNotBeUsedBySomethingElse...";
	IFacade* facade = Facade::getInstance(applicationKey);
	return 0;
}