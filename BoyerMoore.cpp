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

void preProcessGoodSuffix(string pattern, int patternSize, int goodSuffixes[], int borderPosition[]){

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

int searchBoyerMoore(string pattern, string text){
    
    int totalOccurrences = 0;

    int patternSize = pattern.size();
    int textSize = text.size();

    int badChar[ASCII];
    int goodSuffixes[patternSize];
    int borderPosition[patternSize];

    preProcessBadCharacter(pattern, patternSize, badChar);
    preProcessGoodSuffix(pattern, patternSize, goodSuffixes, borderPosition);

    int windowIndex = 0;

    while (windowIndex <= (textSize - patternSize)){
        // Initialize the pattern index on the last character of the pattern.
        int patternIndex = patternSize - 1;

        while (patternIndex >= 0 && pattern[patternIndex] == text[windowIndex + patternIndex]){
            patternIndex--;
        }

        // If the patternIndex became less than 0, then a match occurred in the current window.
        if (patternIndex < 0){
            // TODO: Instead of printing this position, just mark the line as having an occurrence and print it after.
            cout << "pattern occurs at position = " << windowIndex << endl;

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

// TODO: Instead of printing the position of the text where the pattern occurred,
// Print the whole line where it occurred (only one time, even with multiple occurrences in the same line).
// Also, return the total times it occurred

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

    int totalOccurrences = searchBoyerMoore(pattern, text);
    cout << "Total Occurrences of the supplied pattern in the text: " << totalOccurrences << endl;
    
}