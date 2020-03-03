#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
using namespace std;

namespace model
{

class WordCounter
{
public:
    WordCounter();
    virtual ~WordCounter();
    void generateWordCountTable(const string &input);

protected:

private:
};

}
#endif // WORDCOUNTER_H
