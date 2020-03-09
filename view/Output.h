#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>

using namespace std;

namespace view
{

class Output
{
    public:
        void show_help_message();
        void show_error_message(string &message);
        void show_message(const string &message);
};

}

#endif // CONSOLEOUTPUT_H
