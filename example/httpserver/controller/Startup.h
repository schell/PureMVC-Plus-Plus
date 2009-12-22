//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *	Startup starts up the application.
 *
 *	@author Schell Scivally
 *	@since  2009-12-21
 */

#ifndef _STARTUP_
#define _STARTUP_

#include "common.h"

class Startup : public PureMVC::SimpleCommand
{
public:
        void execute(PureMVC::INotification* note);
};

#endif