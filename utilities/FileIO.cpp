#include "FileIO.h"

#include <fstream>
#include <sstream>

using namespace std;

namespace utilities
{

FileIO::FileIO()
{
    //ctor
}

FileIO::~FileIO()
{
    //dtor
}

string FileIO::get_string_from_file(const string &file_path)
{
    ifstream input_file (file_path);
    if (input_file)
    {
        stringstream input_stream;
        string line;
        while (getline(input_file, line))
        {
            input_stream << line << endl;
        }
        input_file.close();
        return input_stream.str();
    }

    return "";
}

}
