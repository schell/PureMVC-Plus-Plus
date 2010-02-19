//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////

#include "Set.h"
#include "common.h"
#include "model/SocketProxy.h"

using namespace std;
using namespace PureMVC;

void Set::execute(INotification* note)
{
    int type = note->getType();
    void* body = note->getBody();

    cout << "Set::execute(type:"<< n_type::toString[type] << ")\n";

    IFacade* facade = getFacade();
    SocketProxy* socketP = (SocketProxy*) facade->retrieveProxy(SocketProxy::NAME);
    
    switch(type)
    {
        case n_type::CLI_ARGS:
        {
            CliArgs* cliargs = (CliArgs*) body;
            socketP->setArgs(cliargs);
        }
        break;

        case n_type::RESPONSE:
        {
			Response response = *(Response*) body;
            socketP->reply(response);
        }
        break;
    }
}