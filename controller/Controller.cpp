#include "Controller.h"
#include "Utilities.h"
#include "WordCounter.h"
using namespace model;

#include <iostream>
using namespace std;

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
    WordCounter word_counter;
    const string help = "--help";
    string infile = "";
    string outfile = "";
    map<string, int> words_and_count_to_add;
    map<string, int> words_and_count_to_remove;
    vector<string> words_to_completely_remove;
    int num_columns = 4;
    int column_width = 15;
    bool sort_alphabetically = false;

    for (int i = 0; i < args_count; ++i)
    {
        Utilities utilities;
        string arg = args[i];
        if (arg.compare(help) == 0)
        {
            cout << utilities.get_help_message() << endl; //TODO check if cout help message here is ok
            return;
        }
        else if (arg.compare("-a") == 0)
        {
            string word = args[++i];
            string num_times = args[++i];
            if (word.compare(help) == 0 || num_times.compare(help) == 0)
            {
                cout << utilities.get_help_message() << endl;
                return;
            }
            cout << "adding " << word << " " << num_times << " times" << endl;
        }
        else if (arg.compare("-c") == 0)
        {
            string num_columns = args[++i];
            if (num_columns.compare(help) == 0)
            {
                cout << utilities.get_help_message() << endl;
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
                cout << utilities.get_help_message() << endl;
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
                cout << utilities.get_help_message() << endl;
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
                cout << utilities.get_help_message() << endl;
                return;
            }
            cout << "changing col width to " << column_width << endl;
        }
        else if (infile.compare(""))
        {
            infile = arg;
            cout << "INFILE: " << arg << endl;
        }
        else if (outfile.compare(""))
        {
            outfile = arg;
            cout << "OUTFILE: " << arg << endl;
        }
    }

    cout << word_counter.generate_word_count_table("pass pass,pass pass#HeLLO.      there!! This's a  four9two 9four four9 test' test ' of-this - thing test. -I \\n keep.testing things,so i'can pass keep.",
            words_and_count_to_add, words_and_count_to_remove, words_to_completely_remove, num_columns, column_width, sort_alphabetically) << endl;
            //TODO move cout out of controller
}

}
