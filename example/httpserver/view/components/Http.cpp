//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////

#include "Http.h"

using namespace std;

/*                                                                            */
Http::Http(string header)
{
    splitLines(header);
}
/*                                                                            */
Http::Http(){ }
/*                                                                            */
void Http::splitLines(string s)
{
    stringstream request(s);
    string line;
    while(getline(request, line))
        _lines.push_back(line);
}
/*                                                                            */
string Http::getRequestMethod()
{
    string line = _lines.at(0);
    stringstream request(line);
    string method;
    getline(request, method, ' ');
    return method;
}
/*                                                                            */
string Http::getRequestResource()
{
    string line = _lines.at(0);
    stringstream request(line);
    string method;
    getline(request, method, ' ');
    getline(request, method, ' ');
    return method;
}
/*                                                                            */
vector<string> Http::getHeaders()
{
    vector<string> headers = _lines;
    return headers;
}
/*                                                                            */
void Http::setHeaders(vector<string> headers)
{
    _lines = headers;
}
/*                                                                            */
string Http::toString()
{
    string s;
    for(size_t i = 0; i < _lines.size(); i++)
    {
        s += _lines.at(i);
    }
    return s;
}