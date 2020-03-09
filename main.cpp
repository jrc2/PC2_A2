#include <iostream>

using namespace std;

#include "Controller.h"
using namespace controller;

/**
    Invokes the controller.

    @author John Chittam

    @param args_count - the number of command line arguments
    @param args - the array of all command line arguments
*/
int main(int args_count, char *args[])
{
    Controller controller;
    controller.run(args_count, args);
    return 0;
}
