#include "WordCounter.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

namespace model
{

WordCounter::WordCounter()
{
    this->infile = "";
    this->outfile = "";
    this->num_columns = 4;
    this->column_width = 15;
    this->sort_alphabetically = false;
    this->ok_to_override = false;
}

WordCounter::~WordCounter()
{
    //dtor
}

/**
    Generates a table showing the occurences of each word by count or starting letter. Characters that are not
    letters, `-`s or `'`s will be converted to spaces. `-`s and `'`s will be converted to spaces if not
    surrounded by letters.

    @param TODO

    @return an empty string if help message should be shown, otherwise a string showing the occurences of words,
        either by count or starting letter
*/
string WordCounter::generate_word_count_table(int args_count, char *args[])
{
    string output;
    bool args_result_help = this->process_command_line_args(args_count, args);
    if (!args_result_help)
    {
        return "";
    }

    this->get_input();

    stringstream cleaned_input = this->clean_input(input);
    map<string, int> word_counts = this->generate_word_count_map(cleaned_input);

    if (sort_alphabetically)
    {
        output = this->generate_table_grouped_alphabetically(word_counts, num_columns, column_width);
    }
    else
    {
        output = this->generate_table_grouped_by_occurences(word_counts, num_columns, column_width);
    }

    if (this->outfile.compare("") != 0)
    {
        this->file_io.write_string_to_file(output, this->outfile, ok_to_override);
    }

    return output;
}

bool WordCounter::process_command_line_args(int args_count, char *args[])
{
    int one_additional_arg = 2;
    for (int i = 0; i < args_count; ++i)
    {
        string arg = args[i];
        if (i == 0)
        {
            continue;
        }
        else if (arg.compare(help) == 0)
        {
            return false;
        }
        else if (arg.compare("-a") == 0)
        {
            string word = args[++i];
            string num_times = args[++i];
            if (word.compare(help) == 0 || num_times.compare(help) == 0)
            {
                return false;
            }
            this->words_and_count_to_add[word] += stoi(num_times);
        }
        else if (arg.compare("-c") == 0)
        {
            if (args_count < i + one_additional_arg)
            {
                throw invalid_argument("No number given after -c");
            }
            string num_columns = args[++i];
            if (num_columns.compare(help) == 0)
            {
                return false;
            }
            this->num_columns = stoi(num_columns);
        }
        else if (arg.compare("-d") == 0)
        {
            if (args_count < i + one_additional_arg + 1)
            {
                throw invalid_argument("A word and number of times are required after -d");
            }
            string word = args[++i];
            string num_times = args[++i];
            if (word.compare(help) == 0 || num_times.compare(help) == 0)
            {
                return false;
            }
            words_and_count_to_remove[word] -= stoi(num_times);
        }
        else if (arg.compare("-oa") == 0)
        {
            sort_alphabetically = true;
        }
        else if (arg.compare("-r") == 0)
        {
            if (args_count < i + one_additional_arg)
            {
                throw invalid_argument("No word given after -r");
            }
            string word_to_remove = args[++i];
            if (word_to_remove.compare(help) == 0)
            {
                return false;
            }
            this->words_to_completely_remove.push_back(word_to_remove);
        }
        else if (arg.compare("-o") == 0)
        {
            this->ok_to_override = true;
        }
        else if (arg.compare("-w") == 0)
        {
            if (args_count < i + one_additional_arg)
            {
                throw invalid_argument("No number given after -w");
            }
            string column_width = args[++i];
            if (column_width.compare(help) == 0)
            {
                return false;
            }
            this->column_width = stoi(column_width);
        }
        else if (infile.compare("") == 0)
        {
            this->infile = arg;
        }
        else if (outfile.compare("") == 0)
        {
            this->outfile = arg;
        }
    }

    return true;
}

void WordCounter::get_input()
{
    this->input = this->file_io.get_string_from_file(infile);

    if (this->input.compare("") == 0)
    {
        throw invalid_argument("Invalid input file");
    }
}

stringstream WordCounter::clean_input(string &input)
{
    char before_curr, after_curr;

    for (unsigned i = 0; i < input.size(); ++i)
    {
        if (i > 0)
        {
            before_curr = input[i - 1];
        }

        if (i < input.size())
        {
            after_curr = input[i + 1];
        }

        if ((before_curr == ' ' || after_curr == ' ') && (input[i] == '\'' || input[i] == '-'))
        {
            input[i] = ' ';
        }
    }

    regex non_letters ("[^A-Za-z0-9'\\- ]");
    stringstream cleaned_input;
    regex_replace(ostream_iterator<char>(cleaned_input), input.begin(), input.end(), non_letters, " ");

    return cleaned_input;
}

map<string, int> WordCounter::generate_word_count_map(stringstream &cleaned_input)
{
    map<string, int> word_counts;

    while (cleaned_input)
    {
        string word;
        cleaned_input >> word;
        if (word.compare("") != 0)
        {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            word_counts[word]++;
        }
    }

    return word_counts;
}

string WordCounter::generate_table_grouped_alphabetically(map<string, int> &word_counts, int num_columns, int column_width)
{
    map<char, vector<string>> words_grouped_alphabetically;
    stringstream output;

    for (const auto &word_count_pair: word_counts)
    {
        string word = word_count_pair.first;
        char first_letter = word[0];
        words_grouped_alphabetically[first_letter].push_back(word);
    }

    for  (const auto &words_starting_with_letter : words_grouped_alphabetically)
    {
        char first_letter = words_starting_with_letter.first;
        vector<string> words = words_starting_with_letter.second;
        output << endl << "Words starting with " << first_letter << ":" << endl;
        output << this->output_formatter(words, num_columns, column_width) << endl;
    }

    return output.str();
}

string WordCounter::generate_table_grouped_by_occurences(map<string, int> &word_counts, int num_columns, int column_width)
{

    map<int, vector<string>> words_grouped_by_occurences;
    stringstream output;

    for (const auto &word_count_pair: word_counts)
    {
        string word = word_count_pair.first;
        int num_occurences = word_count_pair.second;
        words_grouped_by_occurences[num_occurences].push_back(word);
    }

    for (const auto &word : words_grouped_by_occurences)
    {
        int num_occurences = word.first;
        string time_indicator = "times";
        if (num_occurences == 1)
        {
            time_indicator = "time";
        }

        output << endl << "Words occuring " << num_occurences << " " << time_indicator << ":" << endl;

        vector<string> words = word.second;
        output << this->output_formatter(words, num_columns, column_width) << endl;
    }

    return output.str();
}

string WordCounter::output_formatter(vector<string> &words_to_format, int num_columns, int column_width)
{
    stringstream formatted_output;
    int counter = 0;

    for (const auto &word : words_to_format)
    {
        if (counter == num_columns)
        {
            formatted_output << endl;
            counter = 0;
        }
        formatted_output << word << " ";
        int num_spaces = column_width - word.length() - 1;
        for (int i = 0; i < num_spaces; i++)
        {
            formatted_output << " ";
        }
        counter++;
    }

    return formatted_output.str();
}

}
