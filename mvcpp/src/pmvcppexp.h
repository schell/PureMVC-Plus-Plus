/* 
 * File:   pmvcexp.h
 * Author: Schell Scivally
 *
 * Exceptions for the pmvcpp architecture.
 *
 * Created on November 23, 2009, 3:54 PM
 */

#ifndef _PMVCPPEXP_H
#define	_PMVCPPEXP_H

#include <stdexcept>

//--------------------------------------
//  Multiton
//--------------------------------------
class MultitonInstantiationException : public std::runtime_error
{
public:
    MultitonInstantiationException(const std::string &err) : runtime_error(err){}
};

class MultitonExistsException : public std::runtime_error
{
public:
    MultitonExistsException( const std::string &err ) : runtime_error (err) {}
};
#endif	/* _PMVCPPEXP_H */