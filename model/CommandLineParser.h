#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <map>
#include <vector>

using namespace std;

namespace model
{

class CommandLineParser
{
    public:
        bool parse_add(int args_count, char *args[], int &curr_arg_index, map<string, int> &words_and_count_to_add);
        bool parse_num_columns(int args_count, char *args[], int &curr_arg_index, int &num_columns);
        bool parse_delete_num_of_word(int args_count, char *args[], int &curr_arg_index, map<string, int> &words_and_count_to_remove);
        bool parse_remove_all_of_word(int args_count, char *args[], int &curr_arg_index, vector<string> &words_to_completely_remove);
        bool parse_column_width_arg(int args_count, char *args[], int &curr_arg_index, int &column_width);

    private:
        const int one_additional_arg = 2;
        const string help_arg = "--help";
};

}

#endif // COMMANDLINEPARSER_H
