//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *	Sets things of different types.
 *
 *	@author schell
 *	@since  2009-12-21
 */

#ifndef _SET_
#define _SET_

#include "common.h"

class Set : public PureMVC::SimpleCommand
{
public:
    void execute(PureMVC::INotification* note);
};

#endif