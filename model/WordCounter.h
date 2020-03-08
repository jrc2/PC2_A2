#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <map>
#include <vector>

#include "FileIO.h"

using namespace std;
using namespace utilities;

namespace model
{

class WordCounter
{
public:
    WordCounter();
    virtual ~WordCounter();
    string generate_word_count_table(int args_count, char *args[]);

protected:

private:
    FileIO file_io;
    const string help = "--help";
    string infile;
    string outfile;
    map<string, int> words_and_count_to_add;
    map<string, int> words_and_count_to_remove;
    vector<string> words_to_completely_remove;
    int num_columns;
    int column_width;
    bool sort_alphabetically;
    string input;

    bool process_command_line_args(int args_count, char *args[]);
    stringstream clean_input(string &input);
    map<string, int> generate_word_count_map(stringstream &cleaned_input);
    string generate_table_grouped_alphabetically(map<string, int> &word_counts, int num_columns, int column_width);
    string generate_table_grouped_by_occurences(map<string, int> &word_counts, int num_columns, int column_width);
    string output_formatter(vector<string> &words_to_format, int num_columns, int column_width);
};

}
#endif // WORDCOUNTER_H
