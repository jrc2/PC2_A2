#include "FileIO.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace utilities
{

/**
    FileIO helper methods.

    @author John Chittam
*/

/**
    Generates a string based on the given text file's content.

    @param file_path - the absolute or relative path of the text file.

    @return the file's content as a string
*/
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

/**
    Writes the given content to a file at the given path. If the file already exists, it will be
    overwritten unless ok_to_override is false and the user does not confirm overwriting.

    @param contents - the string to write to the file
    @param file_path - the absolute or relative path of the text file.
    @param ok_to_override - true if the file can be overwritten without confirmation, false if not
*/
void FileIO::write_string_to_file(const string &contents, const string &file_path, bool ok_to_override)
{
    if (this->check_if_file_exists(file_path) && !ok_to_override)
    {
        ok_to_override = this->prompt_to_override();
    }
    else
    {
        ok_to_override = true;
    }

    if (ok_to_override)
    {
        ofstream output_file;
        output_file.open(file_path, ios::trunc);
        output_file << contents << endl;
        output_file.close();
    }
}

bool FileIO::check_if_file_exists(const string &file_path)
{
    ifstream file (file_path);
    return file.good();
}

bool FileIO::prompt_to_override()
{
    char answer;
    string override_confirmation_message = "Would you like to override the output file? [y/n] ";

    do
    {
        cout << override_confirmation_message;
        cin >> answer;
        answer = tolower(answer);
    } while (answer != 'y' && answer != 'n');

    return answer == 'y';
}

}
