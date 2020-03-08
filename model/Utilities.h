#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using namespace std;

namespace model
{

class Utilities
{
    public:
        Utilities();
        virtual ~Utilities();
        string get_help_message();
        string get_string_from_file(const string &file_path);

    protected:

    private:
};

}

#endif // UTILITIES_H
