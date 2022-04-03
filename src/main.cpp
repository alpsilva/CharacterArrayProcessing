#include <iostream>
#include "BoyerMoore.cpp"
#include "shiftOr.cpp"
#include "Sellers.cpp"

using namespace std;

#define VERSION 0.1

void parseAlgorithmName(const string algorithmName, const vector<string>& patternList, const string& pattern, const vector<string>& textList, const int eMax, bool isCount){
    
    string treatedAlgorithmName = "";
    // convert string to lower case
    for (char c : algorithmName){
        treatedAlgorithmName.push_back(tolower(c));
    }

    if(treatedAlgorithmName == "shiftor"){
        for(string pattern: patternList){
            shiftOr(pattern, textList);
        }
    }
    else if(treatedAlgorithmName == "sellers"){
        for(string pattern: patternList){
            searchSellers(pattern, textList, eMax, isCount);
        }
    }
    else if(treatedAlgorithmName == "boyermoore"){
        for(string pattern: patternList){
            searchBoyerMoore(pattern, textList, isCount);
        }
    }
    else if(treatedAlgorithmName == "wumanber"){

    }
    else{
        cout << "please provide one of these algorithms: BoyerMoore, ShiftOr, Sellers, WuManber." << endl;
        exit(0);
    }
}

void chooseExactAlgorithm(const vector<string>& patternList, const string& pattern, const vector<string>& textList, bool isCount){
    for (string pattern : patternList){
        if (pattern.size() <= 8){
            shiftOr(pattern, textList);
        } else {
            searchBoyerMoore(pattern, textList, isCount);
        }
    }
}

void chooseApproximateAlgorithm(const vector<string>& patternList, const string& pattern, const vector<string>& textList, const int eMax, bool isCount){
    for (string p : patternList){
        if (p.size() <= 8){
            // Use wumanber
        } else {
            searchSellers(pattern, textList, eMax, isCount);
        }
    }

}

int main(int argc, char *argv[]){
    // TODO: Create the help text.
    string helpText = "";
    // Obligatory
    string pattern = "";
    string textFile = "";
    
    // Optional
    int eMax = 0;
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
                asked_help = true;
            } else if (arg == "-v" || arg == "--version") {
                asked_version = true;
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
    vector<string> patternList;
    if (patternFile.size() > 0){
        patternList = readStringFromFile(patternFile.data());
    } else {
        patternList.push_back(pattern);
    }
    vector<string> textList = readStringFromFile(textFile.data());

    if (algorithmName.size() > 0){
        parseAlgorithmName(algorithmName, patternList, pattern, textList, eMax, isCount);
    } else {
        // Choose the best algo
        if (eMax > 0){
            chooseApproximateAlgorithm(patternList, pattern, textList, eMax, isCount);
        } else {
            chooseExactAlgorithm(patternList, pattern, textList, isCount);         
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