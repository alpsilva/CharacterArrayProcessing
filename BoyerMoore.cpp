#define ASCII 128

#include <iostream>
#include "utils.cpp"

using namespace std;

void preProcessBadCharacter(string pattern, int patternSize, int badChar[]){
    for (int i = 0; i < ASCII; i++){
        badChar[i] = -1;
    }
    /*
    The badChar array will work as a dictionary.
    Each character that occurs in the pattern will have its current position
    in the pattern logged in the badChar array, using the ascii value.
    Essentially, this implies that after this loop, the badChar array will have:
    The position where each character appeared last.
    -1 for characters that never occurred in the pattern.
    */
    for (int i = 0; i < patternSize; i++){
        char c = pattern[i];
        badChar[(int) c] = i;
    }
}

void searchBoyerMoore(string pattern, string text){
    //Test
    int patternSize = pattern.size();
    int textSize = text.size();

    int badChar[ASCII];

    preProcessBadCharacter(pattern, patternSize, badChar);

    int windowIndex = 0;

    while (windowIndex <= (textSize - patternSize)){
        // Initialize the pattern index on the last character of the pattern.
        int patternIndex = patternSize - 1;

        while (patternIndex >= 0 && pattern[patternIndex] == text[windowIndex + patternIndex]){
            patternIndex--;
        }

        // If the patternIndex became less than 0, then a match occurred in the current window.
        if (patternIndex < 0){
            cout << "pattern occurs at position = " << windowIndex << endl;

            int possibleIndexJump = windowIndex + patternSize;
            // Necessary check to avoid out of bounds.
            if (possibleIndexJump < textSize){
                char c = text[possibleIndexJump];
                int actualIndexJump = patternSize - badChar[(int) c];
                windowIndex += actualIndexJump;
            } else {
                windowIndex += 1;
            }

        } else {
            char c = text[windowIndex + patternIndex];
            int indexJump = patternIndex - badChar[(int) c];
            // If the last occurrence of the bad character is on the right of the current character, it will cause a negative jump.
            // Because of this, we take the max between the jump and 1.
            windowIndex += max(1, indexJump);
        }
    }

}

// TODO make this function accept the expected format.
int main(){
    
    /*
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
    */

    string text = "AABCDEABCDABABCDAABBCCDDEE";
    string pattern_ABCD = "ABCD";
    string pattern_AA = "AA";
    string pattern_AABBCCDDEE = "AABBCCDDEE";

    cout << "Text: "<< text << endl;
    cout << "pattern \"ABCD\":" << endl;
    searchBoyerMoore(pattern_ABCD, text);
    cout << "pattern \"AA\":" << endl;
    searchBoyerMoore(pattern_AA, text);
    cout << "pattern \"AABBCCDDEE\":" << endl;
    searchBoyerMoore(pattern_AABBCCDDEE, text);

}