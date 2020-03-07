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

void WordCounter::generateWordCountTable(string input, map<string, int> &words_and_count_to_add,
        map<string, int> &words_and_count_to_remove, vector<string> &words_to_completely_remove,
        int num_columns, int column_width)
{
    char before_curr, after_curr;
    for (int i = 0; i < input.size(); ++i) {
        if (i != 0)
        {
            before_curr = input[i - 1];
        }

        if (i != input.size())
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
    map<string, int> word_counts;
    regex_replace(ostream_iterator<char>(cleaned_input), input.begin(), input.end(), non_letters, " ");

    while (cleaned_input)
    {
        string word;
        cleaned_input >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_counts[word]++;
    }

    map<int, vector<string>> words_grouped_by_occurances;

    for (const auto &word_count_pair: word_counts)
    {
        string word = word_count_pair.first;
        int num_occurences = word_count_pair.second;
        words_grouped_by_occurances[num_occurences].push_back(word);
    }

    for (const auto &word : words_grouped_by_occurances)
    {
        int num_occurences = word.first;
        string time_indicator = "times";
        if (num_occurences == 1)
        {
            time_indicator = "time";
        }
        cout << endl << "Words appearing " << num_occurences << " " << time_indicator << endl;

        vector<string> words = word.second;
        for (const auto &word : words)
        {
            cout << word << endl;
        }
    }
}

}
