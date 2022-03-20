#include "BoyerMoore.cpp"
#include "shiftor.cpp"


using namespace std;

int main(int argc, char *argv[]){
    
    string pattern = argv[1];
    uint patternSize = pattern.length();
    if(patternSize == 0){
        cout << "Please provide a pattern." << endl;
        return 0;
    } else if (patternSize >= 64){
        cout << "Pattern too long, max length is 64." << endl;
        return 0;
    }

    string text = readStringFromFile(argv[2]);

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