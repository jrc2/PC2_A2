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
    //ctor
}

WordCounter::~WordCounter()
{
    //dtor
}

/**
    Generates a table showing the occurences of each word by count or starting letter. Characters that are not
    letters, `-`s or `'`s will be converted to spaces. `-`s and `'`s will be converted to spaces if not
    surrounded by letters.

    @param input - the string to count words in
    @param words_and_count_to_add - the words to add to the table (the int key associated with the string value
        tells how many of each word to add to the count)
    @param words_and_count_to_remove - the words to remove from the table (the int key associated with the string
        value tells how many of each word to remove from the count)
    @param words_to_completely_remove - the words to completely remove from the count
    @param num_columns - the max number of columns of words per row of the returned string
    @param column_width - the number of characters wide each column in the returned string should be
    @param sort_alphabetically - if false, the returned string will show words grouped by the number of occurences;
        if true, it will show words grouped by starting letter and will not show the number of occurences.

    @return a string showing the occurences of words, either by count or starting letter
*/
string WordCounter::generate_word_count_table(string input, map<string, int> &words_and_count_to_add,
        map<string, int> &words_and_count_to_remove, vector<string> &words_to_completely_remove,
        int num_columns, int column_width, bool sort_alphabetically)
{
    char before_curr, after_curr;
    for (int i = 0; i < input.size(); ++i) {
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
    regex non_letters ("[^A-Za-z'\\- ]");

    stringstream cleaned_input;
    //map<string, int> word_counts;
    vector<string> words;
    regex_replace(ostream_iterator<char>(cleaned_input), input.begin(), input.end(), non_letters, " ");

    while (cleaned_input)
    {
        string word;
        cleaned_input >> word;
        if (word.compare("") != 0)
        {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
            //word_counts[word]++;
        }
    }
    if (sort_alphabetically)
    {

    }
    else
    {
        this->generate_table_grouped_by_occurences(words, num_columns, column_width);
    }

    return ""; //TODO return actual output
}

string WordCounter::generate_table_grouped_by_occurences(vector<string> &words, int num_columns, int column_width)
{
    map<string, int> word_counts;
    for (const auto &word : words)
    {
        word_counts[word]++;
    }

    map<int, vector<string>> words_grouped_by_occurences;

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

        cout << endl << "Words appearing " << num_occurences << " " << time_indicator << endl; //TODO don't cout in model

        vector<string> words = word.second;
        cout << this->output_formatter(words, num_columns, column_width) << endl; //TODO don't cout in model
    }
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
