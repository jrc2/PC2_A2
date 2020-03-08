#include "Controller.h"
#include "WordCounter.h"

#include <iostream>

using namespace std;
using namespace model;

namespace controller
{

Controller::Controller()
{
    //ctor
}

Controller::~Controller()
{
    //dtor
}

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
