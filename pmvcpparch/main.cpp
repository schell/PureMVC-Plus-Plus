/* 
 * File:   main.cpp
 * Author: schell
 *
 * Created on November 16, 2009, 4:47 PM
 */

#include <stdlib.h>
#include "pmvcppbase.h"

class Note : public INotifier
{
public:
    virtual void sendNotification   ( std::string notificationName, IBody* body, std::string type)
    {
        printf("name:%s type:%s", notificationName.c_str(), type.c_str());
    }
    virtual void sendNotification   ( std::string notificationName, std::string type ) {};
    virtual void sendNotification   ( std::string notificationName, IBody* body ) {};
    virtual void sendNotification   ( std::string notificationName ) {};
    virtual void initializeNotifier ( std::string key ) {};
};

int main(int argc, char** argv)
{
    Note* note = new Note();
    note->sendNotification("someNotificationName", new IBody(), "sometype");
    return (EXIT_SUCCESS);
}

