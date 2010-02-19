//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *  Takes care of forming a valid http response.
 *
 *  @author Schell Scivally
 *  @since  2009-12-22
 */

#ifndef _HTTPMEDIATOR_
#define _HTTPMEDIATOR_

#include "common.h"
#include <vector>
#include <map>

class HttpMediator : public PureMVC::Mediator
{
public:
    static const std::string NAME;

    HttpMediator(std::string name);
    void onRegister();
    void onRemove();
    std::vector<int> listNotificationInterests();
    void handleNotification(PureMVC::INotification* note);
	void setArgs(CliArgs* args);
private:
    std::string _title;
	std::string _documentRoot;
	std::map<int, Response> _responseMap;
};

#endif