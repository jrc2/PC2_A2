#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <map>
#include <vector>
using namespace std;

namespace model
{

class WordCounter
{
public:
    WordCounter();
    virtual ~WordCounter();
    void generateWordCountTable(string input, map<string, int> &words_and_count_to_add,
            map<string, int> &words_and_count_to_remove, vector<string> &words_to_completely_remove,
            int num_columns, int column_width, bool sort_alphabetically);

protected:

private:
};

}
#endif // WORDCOUNTER_H
