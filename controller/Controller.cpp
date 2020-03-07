#include "Controller.h"

#include "WordCounter.h"
using namespace model;

#include <iostream>
using namespace std;

namespace controller
{

Controller::Controller()
{
    cout << "In Controller constructor" << endl;
}

Controller::~Controller()
{
    cout << "In Controller destructor" << endl;
}

void Controller::run()
{
    cout << "In run" << endl;
    WordCounter word_counter;
    map<string, int> words_and_count_to_add;
    map<string, int> words_and_count_to_remove;
    vector<string> words_to_completely_remove;
    int num_columns;
    int column_width;

    word_counter.generateWordCountTable("pass pass,pass pass#HeLLO.      there!! This's a  test' test ' of-this - thing test. -I \\n keep.testing things,so i'can pass keep.",
            words_and_count_to_add, words_and_count_to_remove, words_to_completely_remove, num_columns, column_width);
}

}
