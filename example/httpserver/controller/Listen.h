//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *	Starts listening on our socket.
 *
 *	@author Schell Scivally
 *	@since  2009-12-22
 */

#ifndef _LISTEN_
#define _LISTEN_

#include "common.h"

class Listen : public PureMVC::SimpleCommand
{
public:
	void execute(PureMVC::INotification* note);
};

#endif