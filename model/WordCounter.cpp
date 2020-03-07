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

void WordCounter::generateWordCountTable(string input)
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

    map<int, vector<string>> output;

    for (const auto &word_count: word_counts)
    {
        string word = word_count.first;
        int num_occurences = word_count.second;
        output[num_occurences].push_back(word);
    }

    for (const auto &word : output)
    {
        int num_occurences = word.first;
        cout << "Words appearing " << num_occurences << " time(s):" << endl;

        vector<string> words = word.second;
        for (const auto &output : words)
        {
            cout << output << endl;
        }
    }
}

}
