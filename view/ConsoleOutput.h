#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <fstream>

using namespace std;

namespace view
{

class ConsoleOutput
{
    public:
        ConsoleOutput();
        virtual ~ConsoleOutput();

        string get_help_message();

    protected:

    private:
};

}

#endif // CONSOLEOUTPUT_H
