//C++///////////////////////////////////////////////////////////////////////////
// 
// Copyright 2009 
// 
////////////////////////////////////////////////////////////////////////////////


/**
 *  Takes a header string and parses it into a header class object.
 *
 *  @author Schell Scivally
 *  @since  2009-12-22
 */

#ifndef _HTTP_
#define _HTTP_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

class Http
{
public:
    Http(std::string request);
    Http();
    std::string getRequestMethod();
    std::string getRequestResource();
    std::vector<std::string> getHeaders();

    void setHeaders(std::vector<std::string>);
    std::string toString();
private:
    std::vector<std::string> _lines;

    void splitLines(std::string s);
};

#endif