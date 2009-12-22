/* 
 * File:   common.h
 * Author: schell = Schell Scivally
 *
 * Created on December 21, 2009, 2:39 PM
 */

#ifndef _HTTPCOMMON_H
#define	_HTTPCOMMON_H

#include <string>
#include "pmvcpp.h"

//--------------------------------------
//  Notification Names & Types
//--------------------------------------
class n_name
{
public:
    enum name
    {
		NIL,
        STARTUP,                // triggers the app startup sequence
        PATTERNS_REGISTERED,	// alerts the app that proxies and mediators have been registered
        SET,			// sets something
        GET,			// makes a request to get something
        LISTEN,                 // start listening for connections
        DISPLAY,                // display something
        QUIT                    // quit the app
    };
    static std::map<int, std::string> toString;
    static void init()
    {
        n_name::toString[NIL] = "null";
        n_name::toString[STARTUP] = "startup";
        n_name::toString[PATTERNS_REGISTERED] = "patterns registered";
        n_name::toString[SET] = "set";
        n_name::toString[GET] = "get";
        n_name::toString[LISTEN] = "listen";
        n_name::toString[DISPLAY] = "display";
        n_name::toString[QUIT] = "quit";
    }
};
class n_type
{
public:
    enum type
    {
		NIL,        // nothing
        CLI_ARGS,   // the command line options
		TITLE,		// the mediator's response title
        REQUEST,    // a request
        RESPONSE    // a response
    };
    static std::map<int, std::string> toString;
    static void init()
    {
            n_type::toString[NIL] = "null";
            n_type::toString[CLI_ARGS] = "cliArgs";
            n_type::toString[REQUEST] = "request";
            n_type::toString[RESPONSE] = "response";
    }
};
//--------------------------------------
//  Notificaiton Body Definitions
//--------------------------------------
class CliArgs
{
public:
    CliArgs(){};
    CliArgs(int _argc, char** _argv) : argc(_argc), argv(_argv){};
    int get_argc()
    {
        return this->argc;
    };
    char** get_argv()
    {
        return this->argv;
    };
private:
    int argc;
    char** argv;
};
#endif	/* _HTTPCOMMON_H */

