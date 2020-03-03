#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WordCounter.h"
using namespace model;

namespace controller
{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    void run();

protected:

private:
};

}
#endif // CONTROLLER_H
