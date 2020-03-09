#include "CommandLineParser.h"

using namespace std;

namespace model
{

/**
    Parses command line arguments

    @author John Chittam
*/

/**
    Parses arguments to add a given count of a word to the output table.

    @param args_count - the total number of command line arguments, including program execution.
    @param args - the array of all arguments, including program execution.
    @param curr_arg_index - the index of the option invoked in the args array.
    @param words_and_count_to_add - the reference to the words_and_count_to_add map in the program

    @return false if interrupted by --help; true if succesfully parsed args

    @throws invalid_argument if argument is invalid
*/
bool CommandLineParser::parse_add(int args_count, char *args[], int &curr_arg_index, map<string, int> &words_and_count_to_add)
{
    if (args_count < curr_arg_index + this->one_additional_arg + 1)
    {
        throw invalid_argument("There must be a word and count after -a");
    }

    string word = args[++curr_arg_index];
    string num_times_string = args[++curr_arg_index];

    if (word.compare(this->help_arg) == 0 || num_times_string.compare(this->help_arg) == 0)
    {
        return false;
    }

    int num_times = stoi(num_times_string);

    if (num_times < 1)
    {
        throw invalid_argument("Number of times after -a must be at least 1");
    }

    words_and_count_to_add[word] += num_times;

    return true;
}

/**
    Parses arguments to change the number of columns of the output table.

    @param args_count - the total number of command line arguments, including program execution.
    @param args - the array of all arguments, including program execution.
    @param curr_arg_index - the index of the option invoked in the args array.
    @param num_columns - the reference to num_columns in the program.

    @return false if interrupted by --help; true if succesfully parsed args

    @throws invalid_argument if argument is invalid
*/
bool CommandLineParser::parse_num_columns(int args_count, char *args[], int &curr_arg_index, int &num_columns)
{
    if (args_count < curr_arg_index + this->one_additional_arg)
    {
        throw invalid_argument("No number given after -c");
    }

    string num_columns_string = args[++curr_arg_index];

    if (num_columns_string.compare(this->help_arg) == 0)
    {
        return false;
    }

    num_columns = stoi(num_columns_string) > 0 ? stoi(num_columns_string) : 1;

    return true;
}

/**
    Parses arguments to remove the given number of a word in the output table.

    @param args_count - the total number of command line arguments, including program execution.
    @param args - the array of all arguments, including program execution.
    @param curr_arg_index - the index of the option invoked in the args array.
    @param words_and_count_to_remove - the reference to the words_and_count_to_remove map in the program.

    @return false if interrupted by --help; true if succesfully parsed args

    @throws invalid_argument if argument is invalid
*/
bool CommandLineParser::parse_delete_num_of_word(int args_count, char *args[], int &curr_arg_index, map<string, int> &words_and_count_to_remove)
{
    if (args_count < curr_arg_index + this->one_additional_arg + 1)
    {
        throw invalid_argument("A word and number of times are required after -d");
    }

    string word = args[++curr_arg_index];
    string num_times_string = args[++curr_arg_index];

    if (word.compare(this->help_arg) == 0 || num_times_string.compare(this->help_arg) == 0)
    {
        return false;
    }

    int num_times = stoi(num_times_string);

    if (num_times < 1)
    {
        throw invalid_argument("Number of times after -d must be at least 1");
    }

    words_and_count_to_remove[word] += num_times;

    return true;
}

/**
    Parses arguments to remove all instances of a word in the output table.

    @param args_count - the total number of command line arguments, including program execution.
    @param args - the array of all arguments, including program execution.
    @param curr_arg_index - the index of the option invoked in the args array.
    @param words_to_completely_remove - the reference to the words_to_completely_remove vector in the program.

    @return false if interrupted by --help; true if succesfully parsed args

    @throws invalid_argument if argument is invalid
*/
bool CommandLineParser::parse_remove_all_of_word(int args_count, char *args[], int &curr_arg_index, vector<string> &words_to_completely_remove)
{
    if (args_count < curr_arg_index + this->one_additional_arg)
    {
        throw invalid_argument("No word given after -r");
    }

    string word_to_remove = args[++curr_arg_index];

    if (word_to_remove.compare(this->help_arg) == 0)
    {
        return false;
    }

    words_to_completely_remove.push_back(word_to_remove);

    return true;
}

/**
    Parses arguments to column width of the output table.

    @param args_count - the total number of command line arguments, including program execution.
    @param args - the array of all arguments, including program execution.
    @param curr_arg_index - the index of the option invoked in the args array.
    @param column_width - the reference to column_width in the program.

    @return false if interrupted by --help; true if succesfully parsed args

    @throws invalid_argument if argument is invalid
*/
bool CommandLineParser::parse_column_width_arg(int args_count, char *args[], int &curr_arg_index, int &column_width)
{
    if (args_count < curr_arg_index + this->one_additional_arg)
    {
        throw invalid_argument("No number given after -w");
    }

    string column_width_string = args[++curr_arg_index];

    if (column_width_string.compare(this->help_arg) == 0)
    {
        return false;
    }

    column_width = stoi(column_width_string);

    return true;
}

}
