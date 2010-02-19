//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *	Takes care of creating and tracking the life of a socket.
 *
 *	@author schell
 *	@since  2009-12-21
 */

#ifndef _SOCKETPROXY_
#define _SOCKETPROXY_

#include "common.h"

class SocketProxy : public PureMVC::Proxy
{
public:
    enum
    {
        PORT_DEFAULT = 666,
        BUFFER_SIZE = 1024
    };
    static const std::string NAME;
    
    SocketProxy();
    SocketProxy(std::string name);
    void onRegister();
    void onRemove();
    /**
     *  Set command line arguments.
     *  Sets the initial arguments for the proxy.
     *
     */
    void setArgs(CliArgs* args);
    /**
     *  Creates the socket.
     *  Starts up the SocketProxy.
     *
     */
    void setup();
    /**
     *  Starts the listening process.
     *
     */
    void beginListen();
    /**
     *  Makes a reply to a given request context.
     *
     */
    void reply(Response response);
private:
    /// holds our args
    CliArgs _args;
    /// the port we'll listen on
    int _port;
    /// the socket file descriptor
    int _sockfd;
    /// the total number of requests (used as a request id)
    int _totalRequests;
    /// ther server address
    struct sockaddr_in _serverAddy;
    /// the incoming socket file descriptor
    std::map<int, int> _readSockfdMap;
    /// the client address
    std::map<int, SockAddr_in> _clientAddyClassMap;
    /// a string to hold a request
    std::map<int, Request> _requestMap;
	/**
	 *	Cleans up a context.
	 */
		void cleanupContext(int context);
    /**
     *  Sends an error.
     *  Displays a certain error message.
     *
     */
    void error(std::string msg);
};

#endif