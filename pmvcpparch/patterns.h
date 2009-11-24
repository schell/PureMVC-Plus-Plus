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

class Object
{
public:
    Object(){}
};

template <class T>
class Multiton
{
public:
    static T* instance()
    {
        std::string key = "key";
        return Multiton<T>::instance(key);
    }
    static T* instance(std::string key)
    {
        if(Multiton<T>::exists(key))
            return Multiton<T>::instanceMap[key];

        T* inst = new T();
        Multiton<T>::instanceMap[key] = inst;
        return inst;
    }
    static bool exists(std::string key)
    {
        return Multiton<T>::instanceMap.find(key) != Multiton<T>::instanceMap.end();
    }
    static size_t size()
    {
        return Multiton<T>::instanceMap.size();
    }
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

