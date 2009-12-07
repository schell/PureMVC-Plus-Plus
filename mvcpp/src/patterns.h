/* 
 * File:   patterns.h
 * Author: schell = Schell Scivally
 *
 * Created on November 24, 2009, 11:41 AM
 */
#ifndef _PATTERNS_H
#define	_PATTERNS_H

#include <string>
#include <map>

/**
 *  A generic object class.
 *  This is mostly used in testing.
 */
class Object
{
public:
    /**
     *  Constructor.
     *  Creates the Object instance.
     */
    Object(){}
};

/**
 *  A templated Multiton class.
 *  Multiton takes care of creating multitons of other classes.
 *  We use this instead implementing multiton code in Facade,
 *  Model, Controller, etc.
 */
template <class T>
class Multiton
{
public:
    /**
     *  Retrieve a default instance of T.
     *  Create a new default instance or return existing.
     *  @see instance(std::string key)
     */
    static T* instance()
    {
        std::string key = "key";
        return Multiton<T>::instance(key);
    }
    /**
     *  Retrieve a named instance of T.
     *  Create a new named instance of T or return one pointed to by key.
     *  @param key A string key
     */
    static T* instance(std::string key)
    {
        if(Multiton<T>::exists(key))
            return Multiton<T>::instanceMap[key];

        T* inst = new T();
        
        Multiton<T>::instanceMap[key] = inst;
        return inst;
    }
    /**
     *  Check existance.
     *  Check whether or not an instance of name key exists.
     *  @param key A string key
     */
    static bool exists(std::string key)
    {
        return Multiton<T>::instanceMap.find(key) != Multiton<T>::instanceMap.end();
    }
    /**
     *  Total instances.
     *  The total number of instances instantiated.
     */
    static size_t size()
    {
        return Multiton<T>::instanceMap.size();
    }
    /**
     *  Deletes instances.
     *  Deletes all instances, calls destructors.
     */
    static void clear()
    {
        Multiton<T>::instanceMap.clear();
    }
private:
    Multiton();
    ~Multiton();
    Multiton(Multiton const&); // copy constructor
    Multiton& operator=(Multiton const&);
    static std::map<std::string, T*> instanceMap;
};
// define
template <class T>
std::map<std::string, T*> Multiton<T>::instanceMap;
#endif	/* _PATTERNS_H */