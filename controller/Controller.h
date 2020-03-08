#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WordCounter.h"
#include "FileIO.h"
#include "ConsoleOutput.h"

using namespace view;
using namespace utilities;
using namespace model;

namespace controller
{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    void run(int args_count, char *args[]);

protected:

private:
    ConsoleOutput console_output;
    FileIO file_io;
};

}
#endif // CONTROLLER_H
