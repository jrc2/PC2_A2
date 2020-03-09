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
    string generate_word_count_table(int args_count, char *args[]);

private:
    FileIO file_io;
    const string help_arg = "--help";
    string infile;
    string outfile;
    map<string, int> words_and_count_to_add;
    map<string, int> words_and_count_to_remove;
    vector<string> words_to_completely_remove;
    int num_columns;
    int column_width;
    bool sort_alphabetically;
    bool ok_to_override;
    bool show_help;

    bool process_command_line_args(int args_count, char *args[]);
    void add_all(map<string, int> &map_to_add_to, const map<string, int> &map_to_add_from);
    void remove_all(map<string, int> &map_to_remove_from, const map<string, int> &map_to_remove_based_on);
    void remove_all_occurences(map<string, int> &map_to_remove_from, const vector<string> &words_to_remove);
    string get_input();
    stringstream clean_input(string &input);
    void add_stringstream_to_map(stringstream &input, map<string, int> &word_counts, int added_word_count);
    map<string, int> generate_word_count_map(stringstream &cleaned_input);
    string generate_table_grouped_alphabetically(map<string, int> &word_counts, int num_columns, int column_width);
    string generate_table_grouped_by_occurences(map<string, int> &word_counts, int num_columns, int column_width);
    string output_formatter(vector<string> &words_to_format, int num_columns, int column_width);
    void sort_output(map<string, int> word_counts, string &output);
};

}
#endif // WORDCOUNTER_H
