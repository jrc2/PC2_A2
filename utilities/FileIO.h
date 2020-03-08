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
        void write_string_to_file(const string contents, const string file_path, bool ok_to_override);

    protected:

    private:
        bool check_if_file_exists(const string &file_path);
        bool prompt_to_override();
};

}

#endif // FILEIO_H
