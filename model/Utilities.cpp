#include "Utilities.h"

#include <fstream>
#include <iterator>
#include <iostream>
using namespace std;

namespace model
{

Utilities::Utilities()
{
    //ctor
}

Utilities::~Utilities()
{
    //dtor
}

string Utilities::get_help_message()
{
    string help_message = "usage: wordcount infile [outfile] [options]\n"
        "by John Chittam\n"
        "Counts and outputs the number of words in the infile.\n"
        "   infile              The input file to count the words.\n"
        "   outfile             The output file to write the output to.\n"
        "options:\n"
        "   --help              Displays this information\n"
        "   -a <word count>     Add the specified count of the word to the output.\n"
        "                       E.g., -a apple 3 would add three occurrences of apple.\n"
        "   -c <number>         Changes the number of output columns to the number specified.\n"
        "                       The default number of columns is 4.\n"
        "   -d <word count>     Deletes the specified count of the word from the output.\n"
        "                       E.g., -a apple 3 would delete 3 occurrences of apple.\n"
        "   -oa                 Displays the output in alphabetic order instead of by frequency\n"
        "                       which is the default output format.\n"
        "   -r <word>           Removes the word completely from the output.\n"
        "   -o                  Automatically overwrites the outfile without prompting, if the outfile\n"
        "                       already exists. If this option is not specified and the outfile exists\n"
        "                       the user will be prompted on whether to overwrite the outfile.\n"
        "   -w <number>         Changes the column width for the output columns.\n"
        "                       The default column width is 15.\n";

    return help_message;
}

string Utilities::get_string_from_file(const string &file_path)
{
    ifstream input_file (file_path);
    string input { istreambuf_iterator<char>(input_file), istreambuf_iterator<char>() };
    //TODO fix file in
    input_file.close();
}
}
