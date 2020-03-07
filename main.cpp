#include <iostream>

using namespace std;

#include "Controller.h"
using namespace controller;

int main(int args_count, char *args[])
{
    Controller controller;
    controller.run(args_count, args);
    return 0;
}
