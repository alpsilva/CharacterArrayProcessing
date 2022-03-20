#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// TODO: Create a function that reads the searchable text and separate it in lines.

string readStringFromFile(const char* fileName)
{
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if (!in)
    {
        cout << "couldn't open file" << endl;
        abort();
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
}