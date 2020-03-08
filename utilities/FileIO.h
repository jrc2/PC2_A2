#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>

using namespace std;

namespace utilities
{

class FileIO
{
    public:
        FileIO();
        virtual ~FileIO();

        string get_string_from_file(const string &file_path);

    protected:

    private:
};

}

#endif // FILEIO_H
