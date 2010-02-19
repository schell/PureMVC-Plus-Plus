//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <fstream>

#include "HttpMediator.h"
#include "model/SocketProxy.h"
#include "view/components/Http.h"

using namespace std;
using namespace PureMVC;

const string HttpMediator::NAME = "HttpMediator";
/*                                                                            */
HttpMediator::HttpMediator(string name) : Mediator(name)
{
	_title = "Here is a response from HttpMediator...";
}
/*                                                                            */
void HttpMediator::onRegister()
{
    cout << "HttpMediator::onRegister()\n";
	_documentRoot = "./document_root";
}
/*                                                                            */
void HttpMediator::onRemove()
{
    cout << "HttpMediator::onRemove()\n";
}
/*                                                                            */
vector<int> HttpMediator::listNotificationInterests()
{
    vector<int> interests;

    interests.push_back(n_name::SET);

    return interests;
}
/*                                                                            */
void HttpMediator::handleNotification(INotification* note)
{
    int name = note->getName();
    void* body = note->getBody();
    int type = note->getType();

    cout << "HttpMediator::handleNotification(" << n_name::toString[name] << ")\n";
    switch(name)
    {
        case n_name::SET:
        {
            switch(type)
            {
				case n_type::CLI_ARGS:
				{
					CliArgs* cliargs = (CliArgs*) body;
					this->setArgs(cliargs);
				}
				break;
				
                case n_type::REQUEST:
                {
					Request requestBody = *(Request*) body;
                    string headerString = requestBody.data;

                    Http headers(headerString);
					string responseData;
					string responseHeaders;
					
					Response response;
					response.context = requestBody.context;
					
					// get the file
					string resource = _documentRoot + headers.getRequestResource();
					string excludeRoot = _documentRoot + "/";
					printf("	looking for resource '%s'...\n", resource.c_str());
					ifstream::pos_type bufferLen;
					ifstream file;
					file.open(resource.c_str(), ios::binary | ios::in | ios::ate);
					if(resource != excludeRoot && ! file.fail())
					{
						printf("	opened file...\n");
						bufferLen = file.tellg();
						file.seekg(0, ios::beg);
						// allocate the memory
						response.data = new char[bufferLen];
						file.read(response.data, bufferLen);
						file.close();
						
						cout << "	file contents (" << bufferLen << " chars)\n\n" << response.data << "\n";
						
						// create the headers for the response
	                    responseHeaders = "HTTP/1.x 200 OK\n";
	                    responseHeaders += "Server: Schell Scivally's httpserver v0.1\n";
	                    responseHeaders += "Accept-Ranges: bytes";
						responseHeaders += "\n\n";
						
						response.headers = new char[responseHeaders.size() + 1];
						strcpy(response.headers, responseHeaders.c_str());
						printf("	wrote headers to response\n");
						response.headerSize = responseHeaders.size();
						printf("	wrote data to response\n");
						response.dataSize = bufferLen;
					}
					else
					{
						printf("	could not find resource...\n");
						responseData = "<html><title>Welcome to the PureMVC example http server!</title><body>";
	                    responseData += "<h1>" + _title + "</h1><br />";
	                    responseData += " <b>request method:</b> " + headers.getRequestMethod() + "<br />";
	                    responseData += " <b>requested resource:</b> " + headers.getRequestResource() + "<br />";
	                    responseData += " <b>other headers:</b><br /><ul>";
						
						vector<string> headersString = headers.getHeaders();
	                    for(size_t i = 1; i < headersString.size() - 1; i++)
	                        responseData += "  <li>" + headersString.at(i) + "</li>";

	                    responseData += "</ul></body>";
	
						// create the headers for the response
	                    responseHeaders = "HTTP/1.x 404 Not Found\n";
	                    responseHeaders += "Server: Schell Scivally's httpserver v0.1\n";
	                    responseHeaders += "Accept-Ranges: bytes\n";
	                    responseHeaders += "Content-Type: text/html\n\n"; // add one more blank line
						
						response.headers = new char[responseHeaders.size()+1];
						strcpy(response.headers, responseHeaders.c_str());
						response.headerSize = responseHeaders.size();
						response.data = new char[responseData.size()+1];
						strcpy(response.data, responseData.c_str());
						response.dataSize = responseData.size();
					}
					
					file.close();
                    sendNotification(n_name::SET, &response, n_type::RESPONSE);
                }
                break;
            }
        }
        break;
    }
}

void HttpMediator::setArgs(CliArgs* args)
{
	cout << "HttpMediator::setArgs()\n";
	char** argv = args->get_argv();
	for (int i = 0; i < args->get_argc(); i++)
	{
	    string arg(*(argv + i));
	    cout << "   " << arg << "\n";
		// get the title to display...
		if(arg == "-t")
		{
			string title(*(argv + ++i));
			_title = title;
            printf("   setting title to: %s\n", _title.c_str());
		}
		else if(arg == "-r")
		{
			string root(*(argv + ++i));
			_documentRoot = root;
			printf("	setting document root to: %s\n", _documentRoot.c_str());
		}
	}
}