#include <iostream>
#include <vector>
#define ASCII 128
using namespace std;

void preProcessBadCharacter(const string& pattern, int patternSize, int badChar[]){
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
        badChar[c] = i;
    }
}

void preProcessGoodSuffix(const string& pattern, int patternSize, vector<int> goodSuffixes, vector<int> borderPosition){

    for (int i = 0; i < patternSize; i++){
        goodSuffixes[i] = 0;
    }

    for (int i = patternSize, j = patternSize + 1; i > 0; i--, j--){
        borderPosition[i] = j;
        while (j <= patternSize && pattern[i-1] != pattern[j-1]){
            if (goodSuffixes[j] == 0){
                goodSuffixes[j] = j - i;
            }
            j = borderPosition[j];
        }
    }

    int j = borderPosition[0];
    for (int i = 0; i <= patternSize; i++){
        // Set the border position of the first character of the pattern
        // to all indices in goodSuffixes having goodSuffixes[i] = 0
        if (goodSuffixes[i] == 0){
            goodSuffixes[i] = j;
        }
        // If the suffix becomes too short for the borderPosition of the first character,
        // use the position of the next widest border.
        if (i == j){
            j = borderPosition[j];
        }
    }
}

int countBoyerMoore(const string& pattern, const string& text, int badChar[], vector<int> goodSuffixes, vector<int> borderPosition){
    // This functions returns the amount of times the pattern occurs in the text.
    
    int totalOccurrences = 0;

    int patternSize = pattern.size();
    int textSize = text.size();

    int windowIndex = 0;

    while (windowIndex <= (textSize - patternSize)){
        // Initialize the pattern index on the last character of the pattern.
        int patternIndex = patternSize - 1;

        while (patternIndex >= 0 && pattern[patternIndex] == text[windowIndex + patternIndex]){
            patternIndex--;
        }

        // If the patternIndex became less than 0, then a match occurred in the current window.
        if (patternIndex < 0){
            totalOccurrences += 1;

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
            int goodSuffixJump = goodSuffixes[patternIndex];
            // If the last occurrence of the bad character is on the right of the current character, it will cause a negative jump.
            // Because of this, we take the max between the jump and 1.
            // Plus, we use both heuristics to choose the max possible jump
            windowIndex += max(goodSuffixJump, max(1, indexJump));
        }
    }

    return totalOccurrences;
}

bool checkBoyerMoore(const string& pattern, const string& text, int badChar[], vector<int> goodSuffixes, vector<int> borderPosition){
    // This functions returns true if the pattern occurs at least once in the text.
    // Otherwise, returns false.
    int patternSize = pattern.size();
    int textSize = text.size();

    int windowIndex = 0;

    while (windowIndex <= (textSize - patternSize)){
        // Initialize the pattern index on the last character of the pattern.
        int patternIndex = patternSize - 1;

        while (patternIndex >= 0 && pattern[patternIndex] == text[windowIndex + patternIndex]){
            patternIndex--;
        }

        // If the patternIndex became less than 0, then a match occurred in the current window.
        if (patternIndex < 0){
            return true;
        } else {
            char c = text[windowIndex + patternIndex];
            int indexJump = patternIndex - badChar[(int) c];
            int goodSuffixJump = goodSuffixes[patternIndex];
            // If the last occurrence of the bad character is on the right of the current character, it will cause a negative jump.
            // Because of this, we take the max between the jump and 1.
            // Plus, we use both heuristics to choose the max possible jump
            windowIndex += max(goodSuffixJump, max(1, indexJump));
        }
    }

    return false;
}

void searchBoyerMoore(const string& pattern, const vector<string>& textList, bool isCount){
    // Wrapper function that calls the main searching ones.
    int patternSize = pattern.size();

    int badChar[ASCII];
    vector<int> goodSuffixes(patternSize);
    vector<int> borderPosition(patternSize);

    preProcessBadCharacter(pattern, patternSize, badChar);
    preProcessGoodSuffix(pattern, patternSize, goodSuffixes, borderPosition);

    if (isCount){
        int totalOccurrences = 0;
        for (string text : textList) {
            totalOccurrences += countBoyerMoore(pattern, text, badChar, goodSuffixes, borderPosition);
        }
        cout << "The pattern " << pattern << " occurred " << totalOccurrences << " times in the given text." << endl;
    } else {
        for (string text : textList) {
            if(checkBoyerMoore(pattern, text, badChar, goodSuffixes, borderPosition)){
                cout << text << endl;
            }
        }
    }
}