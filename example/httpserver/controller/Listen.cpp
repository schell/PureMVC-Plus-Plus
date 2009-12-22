//C++///////////////////////////////////////////////////////////////////////////
//
// Copyright 2009
//
////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "Listen.h"
#include "model/SocketProxy.h"

using namespace std;
using namespace PureMVC;

void Listen::execute(INotification* note)
{
    cout << "Listen::execute()\n";
    SocketProxy* socketP = (SocketProxy*) getFacade()->retrieveProxy(SocketProxy::NAME);
    socketP->beginListen();
}