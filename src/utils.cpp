#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <regex.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

// TODO: Create a function that reads the searchable text and separate it file lines.

vector<string> readStringFromFile(const char* fileName){
    std::ifstream file(fileName);
    if (!file)
    {
        cout << "couldn't open file" << endl;
        abort();
    }
    vector<string> contents;
    string buffer;
    while(getline(file, buffer))
    {
        contents.push_back(buffer);
    }
    file.close();
    return(contents);
}

vector<vector<string>> readFilesWildcard(const char* wildcard, uint8_t position, uint16_t wildcardLength){
    string regexExp = "";
    
    for(uint16_t i = 0; i < position; i++){
        if(wildcard[i] == '.'){
            regexExp.append("[.]");
        } else {
            regexExp.push_back(wildcard[i]);
        }
        
    }

    regexExp.append(".*");
    for(uint16_t i = position+1; i < wildcardLength; i++){
        if(wildcard[i] == '.'){
            regexExp.append("[.]");
        } else {
            regexExp.push_back(wildcard[i]);
        }
    }

    regex_t regexComp;
    int i = regcomp(&regexComp, regexExp.data(), REG_EXTENDED|REG_NOSUB);
    if(i != 0){
        cout << "couldn't create regex, exiting." << endl;
        exit(0);
    }

    DIR* dir;
    struct dirent* ent;
    char dirName[256];
    getcwd(dirName, 256);
    vector<vector<string>> textFiles; 

    if ((dir = opendir (dirName)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            i = regexec(&regexComp, ent->d_name, 0, NULL, 0);
            if(i == 0){
                textFiles.push_back(readStringFromFile(ent->d_name));
            }
        }
        closedir (dir);
    } else {
        cout << "couldn't open directory, exiting." << endl;
        exit(0);
    }
    return textFiles;
}