//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>

#include "SocketProxy.h"

using namespace std;
using namespace PureMVC;

const string SocketProxy::NAME = "SocketProxy";
/*                                                                            */
SocketProxy::SocketProxy(){ }
/*                                                                            */
SocketProxy::SocketProxy(std::string name) : Proxy(name){ }
/*                                                                            */
void SocketProxy::onRegister()
{
    cout << "SocketProxy::onRegister()\n";
	_totalRequests = 0;
}
/*                                                                            */
void SocketProxy::onRemove()
{
    cout << "SocketProxy::onRemove()\n";
}
/*                                                                            */
void SocketProxy::setArgs(CliArgs* args)
{
    cout << "SocketProxy::setArgs()\n";
    this->_args = *args;
    char** argv = _args.get_argv();
    bool portSet = false;
    for (int i = 0; i < _args.get_argc(); i++)
    {
        string arg(*(argv + i));
        cout << "   " << arg << "\n";
		// get the port to bind to...
        if(arg == "-p")
        {
            string input(*(argv + ++i));
            stringstream converter(input);
            int value;
            if(converter >> value && value > 0)
            {
                cout << "   setting port to:" << input << "\n";
                _port = value;
            }
            else
            {
                cout << "   invalid port number:" << input << "\n";
                _port = SocketProxy::PORT_DEFAULT;
            }
            portSet = true;
        }
		// get the title to display...
		else if(arg == "-t")
		{
			string title(*(argv + ++i));
			sendNotification(n_name::SET, &title, n_type::TITLE);
		}
    }

    if(! portSet)
    {
        cout << "   port number not given, setting to:" << SocketProxy::PORT_DEFAULT << "\n";
        _port = SocketProxy::PORT_DEFAULT;
    }

    setup();
}
/*                                                                            */
void SocketProxy::setup()
{
    cout << "SocketProxy::setup()\n";
    cout << "   acquiring socket...\n";
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (_sockfd < 0)
        error("ERROR opening socket");

    _serverAddy.sin_family = AF_INET;
    _serverAddy.sin_addr.s_addr = INADDR_ANY;
    _serverAddy.sin_port = htons(_port);

    cout << "   binding socket...\n";
    if ( bind(_sockfd, (struct sockaddr *) &_serverAddy, sizeof(_serverAddy)) < 0)
          error("ERROR on binding");

    listen(_sockfd, 5);
    cout << "   listening on port " << _port << "...\n";
}
/*                                                                            */
void SocketProxy::beginListen()
{
    int clilen, n;
    char buffer[SocketProxy::BUFFER_SIZE];
	
	struct sockaddr_in clientAddy;
	// create the current context
	_clientAddyClassMap[_totalRequests].sin = clientAddy;
	// client stuff // testing
    clilen = sizeof(_clientAddyClassMap[_totalRequests]);
    _readSockfdMap[_totalRequests] = accept(_sockfd, (struct sockaddr *) &_clientAddyClassMap[_totalRequests], (socklen_t*) &clilen);
    if (_readSockfdMap[_totalRequests] < 0)
      error("ERROR on accept");

    n = read(_readSockfdMap[_totalRequests], buffer, SocketProxy::BUFFER_SIZE-1);

    if (n < 0)
        error("ERROR reading from socket");
	
	// creates a new thread to handle the request
	_requestMap[_totalRequests].context = _totalRequests;
	_requestMap[_totalRequests].data = buffer;
	printf("request accepted, creating response thread...\n");
    sendThreadedNotification(n_name::SET, &_requestMap[_totalRequests], n_type::REQUEST);
	printf("continuing to listen on port %i", _port);
	// increment total requests
	_totalRequests++;
    // start listening again
	beginListen();
}
/*                                                                            */
void SocketProxy::replyTo(int requestContext, string response)
{
	cout << "	replying to request #" << requestContext << "...\n";
    cout << "   writing to socket...\n";
    int n = write(_readSockfdMap[requestContext], response.c_str(), response.size());
    cout << "   wrote " << n << " chars to socket...\n";
    if (n < 0)
        error("ERROR writing to socket");

    cout << "   shutting down socket...\n";
    // close the socket
    shutdown(_readSockfdMap[requestContext], 2);
	// destroy the context
	cleanupContext(requestContext);
}
/**
 *
 */
void SocketProxy::cleanupContext(int context)
{
	// erase the context from our maps
	_readSockfdMap.erase(context);
	_clientAddyClassMap.erase(context);
	_requestMap.erase(context);
}
/*                                                                            */
void SocketProxy::error(string msg)
{
    msg = "SocketProxy::error()\n   " + msg;
    perror(msg.c_str());
    exit(1);
}