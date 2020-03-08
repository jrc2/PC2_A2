#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WordCounter.h"
#include "FileIO.h"
#include "ConsoleOutput.h"

using namespace view;
using namespace utilities;
using namespace model;

namespace controller
{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    void run(int args_count, char *args[]);

protected:

private:
    ConsoleOutput console_output;
    FileIO file_io;
    WordCounter word_counter;
    const string help = "--help";
    string infile;
    string outfile;
    map<string, int> words_and_count_to_add;
    map<string, int> words_and_count_to_remove;
    vector<string> words_to_completely_remove;
    int num_columns;
    int column_width;
    bool sort_alphabetically;
};

}
#endif // CONTROLLER_H
