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
    word_counter.generateWordCountTable("#HeLLO.      there!! This's a  test' test ' of-this - thing test. -I \\n keep.testing things,so i'can pass.");
}

}
