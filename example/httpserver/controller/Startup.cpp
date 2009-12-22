//C++///////////////////////////////////////////////////////////////////////////
//
// Copyright 2009
//
////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "Startup.h"
#include "model/SocketProxy.h"
#include "view/HttpMediator.h"

using namespace std;
using namespace PureMVC;

void Startup::execute(INotification* note)
{
    cout << "Startup::execute()\n";
    // get the command line args from the body
    CliArgs* cliargs = (CliArgs*) note->getBody();
    // trace it
    int argc = cliargs->get_argc();
    char** argv = cliargs->get_argv();
    cout << "   argc:" << argc << "\n";
    for (int i = 0; i < argc; i++)
    {
        cout << "   argv:" << *(argv + i) << "\n";
    }

    // get our facade
    IFacade* facade = this->getFacade();
    // register our mediators
    facade->registerMediator(new HttpMediator(HttpMediator::NAME));
    // register our proxies
    facade->registerProxy(new SocketProxy(SocketProxy::NAME));

    // tell things we're done with registrations
    sendNotification(n_name::PATTERNS_REGISTERED);
    // send out the cliargs
    sendNotification(n_name::SET, cliargs, n_type::CLI_ARGS);
    // tell the Socket proxy to start listening
    sendNotification(n_name::LISTEN);
}