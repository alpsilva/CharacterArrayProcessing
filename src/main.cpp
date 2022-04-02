#include <iostream>
#include <list>
#include "BoyerMoore.cpp"
#include "shiftOr.cpp"
#include "Sellers.cpp"

using namespace std;

#define VERSION 0.1

int main(int argc, char *argv[]){
    // TODO: Create the help text.
    string helpText = "";
    // Obligatory
    string pattern = "";
    string textFile = "";
    
    // Optional
    string eMax = 0;
    string patternFile = "";
    string algorithmName = "";
    bool isCount = false;
    bool asked_help = false;
    bool asked_version = false;

    if (argc < 3) {
        cout << "You have to provide at least a pattern and a text file." << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++){
        if (i == argc - 2){
            // TODO: This may break the code if no pattern is passed
            pattern = argv[i];
            textFile = argv[i+1];
        } else {
            string arg = argv[i];
            if (arg == "-e" || arg == "--edit"){
                eMax = stoi(argv[i++]);
            } else if (arg == "-p" || arg == "--pattern") {
                patternFile = argv[i++];
            } else if (arg == "-a" || arg == "--algorithm") {
                algorithmName = argv[i++];
            } else if (arg == "-c" || arg == "--count") {
                isCount = true;
            } else if (arg == "-h" || arg == "--help") {
                isCount = true;
            } else if (arg == "-v" || arg == "--version") {
                isCount = true;
            } else {
                cout << "Option does not exist: " << arg << endl;
                return 0;
            }
        }


    }

    if (asked_help){
        cout << helpText << endl;
    }
    if (asked_version){
        cout << "PMT by André Luiz, Lucas Vinicius.\nVersion: " << VERSION << endl;
    }
    list<string> patternList;
    if (patternFile.size() > 0){
        patternList = readStringFromFile(patternFile);
    } else {
        patternList.push_back(pattern);
    }
    list<string> textList = readStringFromFile(textFile);

    if (algorithmName.size() > 0){
        // use the given algo
    } else {
        // Choose the best algo
        if (eMax > 0){
            // Aproximate matching
            for (string p : patternList){
                 for (string t : textList){
                     
                 }
            }
        } else {
            // Exact matching
            for (string p : patternList){
                 for (string t : textList){
                     if (p.size() <= 8){
                         // Use ShiftOr
                     } else {
                         // user BoyerMoore
                     }
                 }
            }
        }
    }


    /*
    Todo:
    Options for count,
    Options for choosing exact or approximate matching (the user should give us an eMax for the maximum approximation),
    Issuing a patter_file path, where each line will be a pattern to be searched.
    Options for "algorithm_name". Our project should be able to choose the best algo for each input automatically,
    but we should also give an option for the user to choose wich algo they want specfically.
    https://www.gnu.org/prep/standards/html_node/Command_002dLine-Interfaces.html
    */
    // Process given options

    // Choose algo



    
}