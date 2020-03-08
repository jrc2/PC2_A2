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

        void show_help_message();
        void show_invalid_input_message();

    protected:

    private:
};

}

#endif // CONSOLEOUTPUT_H
