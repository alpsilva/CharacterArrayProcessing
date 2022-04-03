#include "utils.cpp"
#include "BoyerMoore.cpp"
#include "shiftor.cpp"
#include "Sellers.cpp"
#include "wuManber.cpp"

using namespace std;

#define VERSION 0.1

void parseAlgorithmName(const string algorithmName, const vector<string>& patternList, const vector<string>& textList, const int eMax, bool isCount){
    
    string treatedAlgorithmName = "";
    // convert string to lower case
    for (char c : algorithmName){
        treatedAlgorithmName.push_back(tolower(c));
    }

    if(treatedAlgorithmName == "shiftor"){
        for(string pattern : patternList){
            shiftOr(pattern, textList, isCount);
        }
    }
    else if(treatedAlgorithmName == "sellers"){
        if (eMax > 0){
            for(string pattern : patternList){
                searchSellers(pattern, textList, eMax, isCount);
            }
        } else {
            cout << "To use the approximate matching algorithms, you need to specify a maximum edit cost with \"-e INT or --edit INT\"." << endl;
        }

    }
    else if(treatedAlgorithmName == "boyermoore"){
        for(string pattern : patternList){
            cout << pattern << endl;
            searchBoyerMoore(pattern, textList, isCount);
            cout << "finished the previous" << endl;
        }
    }
    else if(treatedAlgorithmName == "wumanber"){
        if (eMax > 0){
            for(string pattern : patternList){
                wuManber(pattern, textList, eMax, isCount);
            }
        } else {
            cout << "To use the approximate matching algorithms, you need to specify a maximum edit cost with \"-e INT or --edit INT\"." << endl;
        }
    }
    else{
        cout << "please provide one of these algorithms: BoyerMoore, ShiftOr, Sellers, WuManber." << endl;
        exit(0);
    }
}

void chooseExactAlgorithm(const vector<string>& patternList, const vector<string>& textList, bool isCount){
    for (string pattern : patternList){
        if (pattern.size() <= 8){
            shiftOr(pattern, textList, isCount);
        } else {
            searchBoyerMoore(pattern, textList, isCount);
        }
    }
}

void chooseApproximateAlgorithm(const vector<string>& patternList, const vector<string>& textList, const int eMax, bool isCount){
    for (string pattern : patternList){
        if (pattern.size() <= 8){
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
    bool providedPatternFile = false;

    if (argc < 3) {
        cout << "You have to provide at least a pattern and a text file." << endl;
        return 0;
    }

    int optionalArgs = argc - 2;
    for (int i = 1; i < optionalArgs; i++){
        string arg = argv[i];
        if (arg == "-e" || arg == "--edit"){
            eMax = stoi(argv[++i]);
        } else if (arg == "-p" || arg == "--pattern") {
            patternFile = argv[++i];
            providedPatternFile = true;
            optionalArgs++;
        } else if (arg == "-a" || arg == "--algorithm") {
            algorithmName = argv[++i];
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
    textFile = argv[argc-1];
    if (!providedPatternFile){
        pattern = argv[argc-2];
    }
    
    // Debugging
    // cout << "Params" << endl;
    // cout << "pattern: " << pattern << endl;
    // cout << "patternFile: " << patternFile << endl;
    // cout << "textFile: " << textFile << endl;
    // cout << "editCost: " << eMax << endl;
    // cout << "count: " << isCount << endl;
    // cout << "algorithmName: " << algorithmName << endl;

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
        parseAlgorithmName(algorithmName, patternList, textList, eMax, isCount);
    } else {
        // Choose the best algo
        if (eMax > 0){
            chooseApproximateAlgorithm(patternList, textList, eMax, isCount);
        } else {
            chooseExactAlgorithm(patternList, textList, isCount);         
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