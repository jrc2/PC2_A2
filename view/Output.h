#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>

using namespace std;

namespace view
{

class Output
{
    public:
        Output();
        virtual ~Output();

        void show_help_message();
        void show_error_message(string &message);
        void show_message(string &message);

    protected:

    private:
};

}

#endif // CONSOLEOUTPUT_H
