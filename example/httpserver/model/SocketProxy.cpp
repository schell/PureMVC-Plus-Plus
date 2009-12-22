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

    bzero((char *) &_serverAddy, sizeof(_serverAddy));

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

    // client stuff // testing
    clilen = sizeof(_clientAddy);
    _readSockfd = accept(_sockfd, (struct sockaddr *) &_clientAddy, (socklen_t*) &clilen);
    if (_readSockfd < 0)
      error("ERROR on accept");
    bzero(buffer, SocketProxy::BUFFER_SIZE);

    n = read(_readSockfd, buffer, SocketProxy::BUFFER_SIZE-1);

    _request = buffer;

    if (n < 0)
        error("ERROR reading from socket");
    // increment total requests
    _totalRequests++;

    sendNotification(n_name::SET, &_request, n_type::REQUEST);
}
/*                                                                            */
void SocketProxy::reply(string response)
{
    // out
    cout << "   writing to socket...\n";
    int n = write(_readSockfd, response.c_str(), response.size());
    cout << "   wrote " << n << " chars to socket...\n";
    if (n < 0)
        error("ERROR writing to socket");

    cout << "   shutting down socket...\n";

    // close the socket
    shutdown(_readSockfd, 2);

    // start listening again
    sendNotification(n_name::LISTEN);
}
/*                                                                            */
void SocketProxy::error(string msg)
{
    msg = "SocketProxy::error()\n   " + msg;
    perror(msg.c_str());
    exit(1);
}