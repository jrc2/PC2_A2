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
        cout << "No infile given" << endl;
        this->output.show_help_message();
        return;
    }

    try
    {
        pair<string, string> table_outfile_pair = this->word_counter.generate_word_count_table(args_count, args);
        string word_count_table = table_outfile_pair.first;
        string outfile = table_outfile_pair.second;

        cout << word_count_table << endl;

        if (word_count_table.compare("") == 0)
        {
            this->output.show_help_message();
        }
    }
    catch(invalid_argument &e)
    {
        cout << e.what() << endl;
        this->output.show_help_message();
    }
}

}
