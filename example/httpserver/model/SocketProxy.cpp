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

	memset(&_serverAddy, 0, sizeof _serverAddy);

    _serverAddy.sin_family = AF_INET;
    _serverAddy.sin_addr.s_addr = INADDR_ANY;
    _serverAddy.sin_port = htons(_port);

    cout << "   binding socket...\n";
    if ( bind(_sockfd, (const struct sockaddr *) &_serverAddy, sizeof(struct sockaddr_in)) < 0)
          error("ERROR on binding");

    if(listen(_sockfd, 10) < 0)
		error("ERROR on listen");
		
    cout << "   listening on port " << _port << "...\n";
}
/*                                                                            */
void SocketProxy::beginListen()
{
	printf("SocketProxy::beginListen()\n");
    int clilen, n;
    char buffer[SocketProxy::BUFFER_SIZE];
	
	struct sockaddr_in clientAddy;
	// create the current context
	_clientAddyClassMap[_totalRequests].sin = clientAddy;
	// client stuff // testing
    clilen = sizeof(_clientAddyClassMap[_totalRequests]);
    _readSockfdMap[_totalRequests] = accept(_sockfd, (struct sockaddr *) &_clientAddyClassMap[_totalRequests], (socklen_t*) &clilen);
	printf("	created socket file descriptor...\n");
    if (_readSockfdMap[_totalRequests] < 0)
      error("ERROR on accept");

    n = read(_readSockfdMap[_totalRequests], buffer, SocketProxy::BUFFER_SIZE-1);
	printf("	request received...\n");
    if (n < 0)
        error("ERROR reading from socket");
	
	// creates a new thread to handle the request
	_requestMap[_totalRequests].context = _totalRequests;
	_requestMap[_totalRequests].data = new char[n+1];
	strcpy(_requestMap[_totalRequests].data, buffer);
	printf("request accepted, creating response thread...\n");
    sendThreadedNotification(n_name::SET, &_requestMap[_totalRequests], n_type::REQUEST);
	printf("continuing to listen on port %i\n", _port);
	// increment total requests
	_totalRequests++;
    // start listening again
	beginListen();
}
/*                                                                            */
void SocketProxy::reply(Response response)
{
	printf("SocketProxy::reply()\n");
	cout << "	replying to request #" << response.context << "...\n";
    cout << "   writing to socket...\n";
    int headerBytes = write(_readSockfdMap[response.context], response.headers, response.headerSize);
	int dataBytes = write(_readSockfdMap[response.context], response.data, response.dataSize);
	printf("   wrote %i chars to socket (headers:%i + data:%i)...\n", (headerBytes + dataBytes), headerBytes, dataBytes);
    if (headerBytes < 0 || dataBytes < 0)
        error("ERROR writing to socket");

    cout << "   shutting down socket...\n";
    // close the socket
    if(shutdown(_readSockfdMap[response.context], 2) < 0)
	{
		error("ERROR could not shutdown");
	}
	close(_readSockfdMap[response.context]);
	// destroy the context
	cleanupContext(response.context);
}
/**
 *
 */
void SocketProxy::cleanupContext(int context)
{
	printf("SocketProxy::cleanupContext() cleaning up #%i\n", context);
	// erase the context from our maps
	_readSockfdMap.erase(context);
	printf("	cleaned up _readSockfdMap\n");
	_clientAddyClassMap.erase(context);
	printf("	cleaned up _clientAddyClassMap\n");
	_requestMap.erase(context);
	printf("	cleaned up _requestMap\n");
}
/*                                                                            */
void SocketProxy::error(string msg)
{
    msg = "SocketProxy::error()\n   " + msg;
    perror(msg.c_str());
    exit(1);
}