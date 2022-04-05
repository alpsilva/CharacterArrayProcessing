#include "utils.cpp"
#include "BoyerMoore.cpp"
#include "shiftor.cpp"
#include "Sellers.cpp"
#include "wuManber.cpp"



using namespace std;

#define VERSION 0.1

void parseAlgorithmName(const string algorithmName, const vector<string>& patternList, const vector<string>& textList, const int eMax, bool isCount, bool isCountLines){
    
    string treatedAlgorithmName = "";
    // convert string to lower case
    for (char c : algorithmName){
        treatedAlgorithmName.push_back(tolower(c));
    }

    if(treatedAlgorithmName == "shiftor"){
        for(string pattern : patternList){
            if(pattern.size() > 64){
                cout << "this algorithm won't to work with a pattern size of more than 64. Skipping..." << endl;
            } else {
                shiftOr(pattern, textList, isCount, isCountLines);
            }      
        }
    }
    else if(treatedAlgorithmName == "sellers"){
        if (eMax > 0){
            for(string pattern : patternList){
                searchSellers(pattern, textList, eMax, isCount, isCountLines);
            }
        } else {
            cout << "To use the approximate matching algorithms, you need to specify a maximum edit cost with \"-e INT or --edit INT\"." << endl;
        }
    }
    else if(treatedAlgorithmName == "boyermoore"){
        for(string pattern : patternList){
            searchBoyerMoore(pattern, textList, isCount, isCountLines);
        }
    }
    else if(treatedAlgorithmName == "wumanber"){
        if (eMax > 0){
            for(string pattern : patternList){
                if(pattern.size() > 64){
                    cout << "this algorithm won't to work with a pattern size of more than 64. Skipping..." << endl;
                } else {
                    wuManber(pattern, textList, eMax, isCount, isCountLines);
                } 
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

void chooseExactAlgorithm(const vector<string>& patternList, const vector<string>& textList, bool isCount, bool isCountLines){
    for (string pattern : patternList){
        if (pattern.size() <= 8){
            shiftOr(pattern, textList, isCount, isCountLines);
        } else {
            searchBoyerMoore(pattern, textList, isCount, isCountLines);
        }
    }
}

void chooseApproximateAlgorithm(const vector<string>& patternList, const vector<string>& textList, const int eMax, bool isCount, bool isCountLines){
    for (string pattern : patternList){
        if (pattern.size() <= 8){
            wuManber(pattern, textList, eMax, isCount, isCountLines);
        } else {
            searchSellers(pattern, textList, eMax, isCount, isCountLines);
        }
    }
}



int main(int argc, char *argv[]){
    string helpText = R"(
        -h or --help -> Information about PMT.
        -v or --version -> Current version of PMT.

        Optional operational args:

        -e or --edit        -> Receives the next integer. Informs PMT that the user wants an approximate search, with edit cost at most the value passed.
        -c or --count       -> Informs PMT to return the amount of occurrences that match the given pattern(s).
        -l or --lines       -> Informs PMT to return the amount of lines where at least one occurrence happened that matchs the given pattern(s).
        -a or --algorithm   -> Receives the next string. Informs PMT to use the appointed algorithm in the search.
        -p or --patten      -> Receives the next string. Informs PMT to use the appointed file to read a list of patterns and use them in the search.

        How to use PMT:
        PMT [options] <pattern> <textFilePath>

        If the optional patternFile option is used, there is no need to pass an explicit pattern:
        PMT [other options] -p <patternFilePath> <textFilePath>
    )";
    // Obligatory
    string pattern = "";
    string textFile = "";
    
    // Optional
    int eMax = 0;
    string patternFile = "";
    string algorithmName = "";
    bool isCount = false;
    bool isCountLines = false;
    bool asked_help = false;
    bool asked_version = false;
    bool providedPatternFile = false;

    if (argc < 3) {
        if (argc == 2){
            string arg = argv[1];
            if (arg == "-h" || arg == "--help"){
                cout << helpText << endl;
            } else if (arg == "-v" || arg == "--version"){
                cout << "PMT by André Luiz (alps2@cin.ufpe.br), Lucas Vinicius (lvas@cin.ufpe.br).\nVersion: " << VERSION << endl;
            }
            return 0;
        } else {
            cout << "You have to provide at least a pattern and a text file." << endl;
            return 0;
        }
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
        } else if (arg == "-l" || arg == "--lines") {
            isCountLines = true;
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
        cout << "PMT by André Luiz (alps2@cin.ufpe.br), Lucas Vinicius (lvas@cin.ufpe.br).\nVersion: " << VERSION << endl;
    }
    vector<string> patternList;
    if (patternFile.size() > 0){
        patternList = readStringFromFile(patternFile.data());
    } else {
        patternList.push_back(pattern);
    }

    
    bool wildcardFound = false;
    uint16_t wildcardPosition;
    for(uint16_t i = 0; i < textFile.size(); i++){
        if(textFile[i] == '*'){
            wildcardPosition = i;
            wildcardFound = true;
            break;
        }
    }

    if(!wildcardFound){
        vector<string> textList = readStringFromFile(textFile.data());
        if (algorithmName.size() > 0){
            parseAlgorithmName(algorithmName, patternList, textList, eMax, isCount, isCountLines);
        } else {
            // Choose the best algo
            if (eMax > 0){
                chooseApproximateAlgorithm(patternList, textList, eMax, isCount, isCountLines);
            } else {
                chooseExactAlgorithm(patternList, textList, isCount, isCountLines);         
            }
        }
    } else {
        vector<vector<string>> textList;
        textList = readFilesWildcard(textFile.data(), wildcardPosition, textFile.size());
        for(vector<string> text: textList){
            if (algorithmName.size() > 0){
                parseAlgorithmName(algorithmName, patternList, text, eMax, isCount, isCountLines);
            } else {
                // Choose the best algo
                if (eMax > 0){
                    chooseApproximateAlgorithm(patternList, text, eMax, isCount, isCountLines);
                } else {
                    chooseExactAlgorithm(patternList, text, isCount, isCountLines);         
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