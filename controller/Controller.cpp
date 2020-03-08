#include "Controller.h"
#include "WordCounter.h"

#include <iostream>

using namespace std;
using namespace model;

namespace controller
{

Controller::Controller()
{
    //ctor
}

Controller::~Controller()
{
    //dtor
}

void Controller::run(int args_count, char *args[])
{
    string word_count_table = this->word_counter.generate_word_count_table(args_count, args);

    if (word_count_table.compare("") == 0)
    {
        this->console_output.show_invalid_input_message();
    }
}

}
