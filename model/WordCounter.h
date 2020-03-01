#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

using namespace std;

namespace model {

class WordCounter
{
    public:
        WordCounter();
        virtual ~WordCounter();
        void string& generateWordCountTable(string& input);

    protected:

    private:
};

}
#endif // WORDCOUNTER_H
