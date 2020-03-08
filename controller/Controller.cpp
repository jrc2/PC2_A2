#include "Controller.h"
#include "WordCounter.h"

#include <iostream>

using namespace std;
using namespace model;

namespace controller
{

Controller::Controller()
{
    this->infile = "";
    this->outfile = "";
    this->num_columns = 4;
    this->column_width = 15;
    this->sort_alphabetically = false;
}

Controller::~Controller()
{
    //dtor
}

void Controller::run(int args_count, char *args[])
{
    for (int i = 0; i < args_count; ++i)
    {
        string arg = args[i];
        if (i == 0)
        {
            continue;
        }
        else if (arg.compare(help) == 0)
        {
            this->console_output.show_help_message();
            return;
        }
        else if (arg.compare("-a") == 0)
        {
            string word = args[++i];
            string num_times = args[++i];
            if (word.compare(help) == 0 || num_times.compare(help) == 0)
            {
                this->console_output.show_help_message();
                return;
            }
            cout << "adding " << word << " " << num_times << " times" << endl;
        }
        else if (arg.compare("-c") == 0)
        {
            if (args_count < i + 2)
            {
                cout << "ERROR" << endl;
            }
            string num_columns = args[++i];
            if (num_columns.compare(help) == 0)
            {
                this->console_output.show_help_message();
                return;
            }
            cout << "changing num cols to " << num_columns << endl;
        }
        else if (arg.compare("-d") == 0)
        {
            string word = args[++i];
            string num_times = args[++i];
            if (word.compare(help) == 0 || num_times.compare(help) == 0)
            {
                this->console_output.show_help_message();
                return;
            }
            cout << "deleting " << word << " " << num_times << " times" << endl;
        }
        else if (arg.compare("-oa") == 0)
        {
            sort_alphabetically = true;
        }
        else if (arg.compare("-r") == 0)
        {
            string word_to_remove = args[++i];
            if (word_to_remove.compare(help) == 0)
            {
                this->console_output.show_help_message();
                return;
            }
            cout << "removing completely " << word_to_remove << endl;
        }
        else if (arg.compare("-o") == 0)
        {
            cout << "overriding output file with no prompt" << endl;
        }
        else if (arg.compare("-w") == 0)
        {
            string column_width = args[++i];
            if (column_width.compare(help) == 0)
            {
                this->console_output.show_help_message();
                return;
            }
            cout << "changing col width to " << column_width << endl;
        }
        else if (infile.compare("") == 0)
        {
            this->infile = arg;
        }
        else if (outfile.compare("") == 0)
        {
            this->outfile = arg;
            cout << "OUTFILE: " << arg << endl;
        }
    }

    string input = this->file_io.get_string_from_file(infile);
    cout << word_counter.generate_word_count_table(input, words_and_count_to_add, words_and_count_to_remove,
            words_to_completely_remove, num_columns, column_width, sort_alphabetically) << endl;
}

}
