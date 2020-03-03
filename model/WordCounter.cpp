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
    stringstream cleaned_string;
    regex_replace(ostream_iterator<char>(cleaned_string), input.begin(), input.end(), non_letters, "");

    cout << cleaned_string.str() << endl; //this is for testing...don't use in production
}

}
