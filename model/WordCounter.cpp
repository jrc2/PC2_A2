#include "WordCounter.h"
#include "CommandLineParser.h"

#include <regex>
#include <sstream>
#include <string>

using namespace std;

namespace model
{

/**
    WordCounter constructor

    @author John Chittam
*/
WordCounter::WordCounter()
{
    this->infile = "";
    this->outfile = "";
    this->num_columns = 4;
    this->column_width = 15;
    this->sort_alphabetically = false;
    this->ok_to_override = false;
    this->show_help = false;
}

/**
    Generates a table showing the occurences of each word by count or starting letter. Characters that are not
    letters, `-`s or `'`s will be converted to spaces. `-`s and `'`s will be converted to spaces if not
    surrounded by letters.

    @param args_count - the number of arguments, including the initial call
    @param args - the arguments, including the initial call

    @return an empty string if help message should be shown, otherwise a string showing the occurences of words,
        either by count or starting letter

    @throws invalid_argument if a command line argument is not valid.
*/
string WordCounter::generate_word_count_table(int args_count, char *args[])
{
    string output;

    if (!this->process_command_line_args(args_count, args))
    {
        return "";
    }

    this->get_input();

    stringstream cleaned_input = this->clean_input();
    map<string, int> word_counts = this->generate_word_count_map(cleaned_input);

    this->add_all(word_counts, this->words_and_count_to_add);
    this->remove_all(word_counts, this->words_and_count_to_remove);
    this->remove_all_occurences(word_counts, this->words_to_completely_remove);
    this->sort_output(word_counts, output);

    if (this->outfile.compare("") != 0)
    {
        this->file_io.write_string_to_file(output, this->outfile, ok_to_override);
    }

    return output;
}

/**
    Helper method to process command line arguments.

    @return false if unable to process or --help is found, true otherwise.
*/
bool WordCounter::process_command_line_args(int args_count, char *args[])
{
    CommandLineParser parser;
    for (int i = 0; i < args_count; ++i)
    {
        string arg = args[i];
        if (i == 0)
        {
            continue;
        }
        else if (arg.compare(help_arg) == 0)
        {
            return false;
        }
        else if (arg.compare("-a") == 0)
        {
            if (!parser.parse_add(args_count, args, i, this->words_and_count_to_add))
            {
                return false;
            }
        }
        else if (arg.compare("-c") == 0)
        {
            if (!parser.parse_num_columns(args_count, args, i, this->num_columns))
            {
                return false;
            }
        }
        else if (arg.compare("-d") == 0)
        {
            if (!parser.parse_delete_num_of_word(args_count, args, i, this->words_and_count_to_remove))
            {
                return false;
            }
        }
        else if (arg.compare("-oa") == 0)
        {
            sort_alphabetically = true;
        }
        else if (arg.compare("-r") == 0)
        {
            if (!parser.parse_remove_all_of_word(args_count, args, i, this->words_to_completely_remove))
            {
                return false;
            }
        }
        else if (arg.compare("-o") == 0)
        {
            this->ok_to_override = true;
        }
        else if (arg.compare("-w") == 0)
        {
            if (!parser.parse_column_width_arg(args_count, args, i, this->column_width))
            {
                return false;
            }
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

void WordCounter::add_all(map<string, int> &map_to_add_to, const map<string, int> &map_to_add_from)
{
    for (const auto &word_count_pair : map_to_add_from)
    {
        string word = word_count_pair.first;
        int count = word_count_pair.second;
        map_to_add_to[word] += count;
    }
}

void WordCounter::remove_all(map<string, int> &map_to_remove_from, const map<string, int> &map_to_remove_based_on)
{
    for (const auto &word_count_pair : map_to_remove_based_on)
    {
        string word = word_count_pair.first;
        int count = word_count_pair.second;
        if (map_to_remove_from[word] - count > 0)
        {
            map_to_remove_from[word] -= count;
        }
        else if (map_to_remove_from[word] - count == 0)
        {
            map_to_remove_from.erase(word);
        }
    }
}

void WordCounter::remove_all_occurences(map<string, int> &map_to_remove_from, const vector<string> &words_to_remove)
{
    for (const auto &word : words_to_remove)
    {
        map_to_remove_from.erase(word);
    }
}

void WordCounter::get_input()
{
    this->input = this->file_io.get_string_from_file(infile);

    if (this->input.compare("") == 0)
    {
        throw invalid_argument("Invalid input file");
    }
}

stringstream WordCounter::clean_input()
{
    char before_curr, after_curr;

    for (unsigned i = 0; i < this->input.size(); ++i)
    {
        if (i > 0)
        {
            before_curr = this->input[i - 1];
        }

        if (i < this->input.size())
        {
            after_curr = this->input[i + 1];
        }

        if ((before_curr == ' ' || after_curr == ' ') && (this->input[i] == '\'' || this->input[i] == '-'))
        {
            this->input[i] = ' ';
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

void WordCounter::sort_output(map<string, int> word_counts, string &output)
{
    if (this->sort_alphabetically)
    {
        output = this->generate_table_grouped_alphabetically(word_counts, this->num_columns, this->column_width);
    }
    else
    {
        output = this->generate_table_grouped_by_occurences(word_counts, this->num_columns, this->column_width);
    }
}

}
