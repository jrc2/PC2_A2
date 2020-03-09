#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WordCounter.h"
#include "Output.h"

using namespace view;
using namespace utilities;
using namespace model;

namespace controller
{

class Controller
{
public:
    void run(int args_count, char *args[]);

private:
    WordCounter word_counter;
    Output output;
};

}
#endif // CONTROLLER_H
