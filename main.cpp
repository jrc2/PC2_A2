#include <iostream>

using namespace std;

#include "Controller.h"
using namespace controller;

int main(int args_count, char *args[])
{
    cout << "Num args: " << args_count << endl;
    cout << "Args:" << endl;
    for (int i = 0; i < args_count; i++)
    {
        cout << args[i] << endl;
    } //for debugging command line args

    Controller controller;
    controller.run();
    return 0;
}
