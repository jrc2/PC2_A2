#include "WordCounter.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
using namespace std;

namespace model {

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
    regex_replace(ostream_iterator<char>(cleaned_input), input.begin(), input.end(), non_letters, "");

    while (cleaned_input)
    {
        string word;
        cleaned_input >> word;
        cout << word << endl; //for testing -- don't leave cout in model...return whatever needs to be printed instead
    }
}

}
