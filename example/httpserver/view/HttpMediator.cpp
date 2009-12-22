//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////

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

    cout << "HttpMediator::handleNotification()\n";
    switch(name)
    {
        case n_name::SET:
        {
            switch(type)
            {
                case n_type::TITLE:
                    _title = *(string*) body;
                    cout << "   setting title to: " << _title << "\n";
                break;
				
                case n_type::REQUEST:
                {
                    cout << "   request:\n";

                    string headerString = *(string*) body;

                    cout << headerString << "\n";

                    Http request(headerString);

                    // here we could do something with the client's request
                    // and formulate a response, but instead we're just going
                    // to send their info back to them...

                    string responseBody = "<html><title>Welcome to the PureMVC example http server!</title><body>";
                    responseBody += "<h1>" + _title + "</h1><br />";
                    responseBody += " <b>request method:</b> " + request.getRequestMethod() + "<br />";
                    responseBody += " <b>requested resource:</b> " + request.getRequestResource() + "<br />";
                    responseBody += " <b>other headers:</b><br /><ul>";

                    vector<string> headers = request.getHeaders();
                    for(size_t i = 1; i < headers.size() - 1; i++)
                        responseBody += "  <li>" + headers.at(i) + "</li>";

                    responseBody += "</ul></body>";

                    // create the headers for the response
                    string responseHeaders = "HTTP/1.x 200 OK\n";
                    responseHeaders += "Server: PureMVC example httpserver v0.1\n";
                    responseHeaders += "Accept-Ranges: bytes\n";
                    responseHeaders += "Content-Type: text/html\n\n"; // add one more blank line
                    
                    string response = responseHeaders + responseBody;
                    
                    sendNotification(n_name::SET, &response, n_type::RESPONSE);
                }
                break;
            }
        }
        break;
    }
}