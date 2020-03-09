#include "Controller.h"

using namespace std;
using namespace model;

namespace controller
{

/**
    The program controller.

    @author John Chittam
*/

/**
    Runs the program controller

    @param args_count - the number of command line arguments, including the call to the application
    @param args - the array of all args, including the call to the application
*/
void Controller::run(int args_count, char *args[])
{
    if (args_count <= 1)
    {
        string no_infile = "No infile given";
        this->output.show_error_message(no_infile);
        return;
    }

    try
    {
        string word_count_table = this->word_counter.generate_word_count_table(args_count, args);

        word_count_table.compare("") == 0 ? this->output.show_help_message() : this->output.show_message(word_count_table);
    }
    catch(invalid_argument &e)
    {
        string error_message = e.what();
        this->output.show_error_message(error_message);
    }
}

}
