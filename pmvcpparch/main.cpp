/* 
 * File:   main.cpp
 * Author: schell
 *
 * Created on November 16, 2009, 4:47 PM
 */

#include <stdlib.h>
#include "pmvcppbase.h"
#include "pmvcpparch.h"
#include "pmvcppexp.h"

class ApplicationFacade : public Facade
{
    
};

int main(int argc, char** argv)
{
    Note* note = new Note();
    note->sendNotification("someNotificationName", new IBody(), "sometype");
    return (EXIT_SUCCESS);
}

