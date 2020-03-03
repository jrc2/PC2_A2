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

void WordCounter::generateWordCountTable(const string& input)
{
    regex non_letters ("[^A-Za-z'\\- ]");

    stringstream cleaned_input;
    map<string, int> word_counts;
    regex_replace(ostream_iterator<char>(cleaned_input), input.begin(), input.end(), non_letters, "");

    while (cleaned_input)
    {
        string word;
        cleaned_input >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_counts[word]++;
    }

    for (const auto& word_count: word_counts)
    {
        cout << word_count.first << " " << word_count.second << " times" << endl; //cout for testing only
    }
}

}
