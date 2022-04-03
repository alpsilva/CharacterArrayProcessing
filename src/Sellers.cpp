#include <iostream>
#include <vector>

using namespace std;

int levDistance(string s, string t, int maximumError){
    // Function to calculate the Levenshtein Distance between 2 given strings

    const int sSize = s.size() + 1;
    const int tSize = t.size() + 1;

    int matrix[sSize][tSize];

    for (int i = 0; i < sSize; i++){
        for (int j = 0; j < tSize; j++){
            matrix[i][j] = 0;
        }
    }

    // First, we calculate the distance from each s preffix to the empty string,
    // and also from each t preffix to an empty string.

    for (int i = 1; i < sSize; i++){
        matrix[i][0] = i;
    }

    for (int j = 1; j < tSize; j++){
            matrix[0][j] = j;
    }

    for (int j = 1; j < tSize; j++){
        for (int i = 1; i < sSize; i++){
            int substitutionCost = 1;
            if (s[i-1] == t[j-1]){
                substitutionCost = 0;
            }

            matrix[i][j] = min(
                min(
                    matrix[i-1][j] + 1, //Deletion
                    matrix[i][j-1] + 1  //Insertion
                ),
                matrix[i-1][j-1] + substitutionCost // Substitution
            );
        }
    }
    // Debugging
    // for (int i = 0; i < sSize; i++){
    //     for (int j = 0; j < tSize; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // This point of the matrix is the levshentein distance between the two strings. 
    return matrix[sSize-1][tSize-1];
}

int countSellers(string pattern, string text, int maximumError){
    // This functions returns the amount of times the pattern occurs
    // in the text with an edit cost, at most, equal to maximumError.

    int totalOccurrences = 0;

    const int patternSize = pattern.size() + 1;
    const int textSize = text.size() + 1;

    int matrix[patternSize][textSize];

    for (int i = 0; i < patternSize; i++){
        for (int j = 0; j < textSize; j++){
            matrix[i][j] = 0;
        }
    }

    // An empty pattern can be transformed into any text preffix by adding all the characters.
    for (int i = 1; i < patternSize; i++){
        matrix[i][0] = i;
    }
    
    // In the Sellers algorithm, we dont do this step, because we consider free the drop of characters
    // to turn the text into an empty string, so we can identify the preffixes and suffixes.
    // Any pattern can be transformed into an empty text prefix by dropping all characters
    // for (int j = 1; j < textSize; j++){
    //         matrix[0][j] = j;
    // }

    for (int j = 1; j < textSize; j++){
        for (int i = 1; i < patternSize; i++){
            int substitutionCost = 1;
            if (pattern[i-1] == text[j-1]){
                substitutionCost = 0;
            }

            matrix[i][j] = min(
                min(
                    matrix[i-1][j] + 1, //Deletion
                    matrix[i][j-1] + 1  //Insertion
                ),
                matrix[i-1][j-1] + substitutionCost // Substitution
            );
        }
    }

    // Debugging
    // for (int i = 0; i < patternSize; i++){
    //     for (int j = 0; j < textSize; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "  ";
    // for (int j = 0; j < textSize; j++){
    //         cout << text[j] << " ";
    // }
    // cout << endl;
    // for (int j = 0; j < textSize; j++){
    //         cout << j << " ";
    // }

    // We go through the last line of the matrix, looking for preffixes where the distance is less than
    // or equal to the maximumError.
    for (int j = 0; j < textSize; j++){
            if (matrix[patternSize-1][j] <= maximumError){
                totalOccurrences += 1;
            }
    }
    return totalOccurrences;
}

bool checkSellers(string pattern, string text, int maximumError){
    // This functions returns true if the pattern occurs at least once in the text,
    // with an edit cost, at most, equal to maximumError.
    // Otherwise, returns false.

    const int patternSize = pattern.size() + 1;
    const int textSize = text.size() + 1;

    int matrix[patternSize][textSize];

    for (int i = 0; i < patternSize; i++){
        for (int j = 0; j < textSize; j++){
            matrix[i][j] = 0;
        }
    }

    // An empty pattern can be transformed into any text preffix by adding all the characters.
    for (int i = 1; i < patternSize; i++){
        matrix[i][0] = i;
    }
    
    // In the Sellers algorithm, we dont do this step, because we consider free the drop of characters
    // to turn the text into an empty string, so we can identify the preffixes and suffixes.
    // Any pattern can be transformed into an empty text prefix by dropping all characters
    // for (int j = 1; j < textSize; j++){
    //         matrix[0][j] = j;
    // }

    for (int j = 1; j < textSize; j++){
        for (int i = 1; i < patternSize; i++){
            int substitutionCost = 1;
            if (pattern[i-1] == text[j-1]){
                substitutionCost = 0;
            }

            matrix[i][j] = min(
                min(
                    matrix[i-1][j] + 1, //Deletion
                    matrix[i][j-1] + 1  //Insertion
                ),
                matrix[i-1][j-1] + substitutionCost // Substitution
            );
        }
    }

    // Debugging
    // for (int i = 0; i < patternSize; i++){
    //     for (int j = 0; j < textSize; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "  ";
    // for (int j = 0; j < textSize; j++){
    //         cout << text[j] << " ";
    // }
    // cout << endl;
    // for (int j = 0; j < textSize; j++){
    //         cout << j << " ";
    // }

    // We go through the last line of the matrix, looking for preffixes where the distance is less than
    // or equal to the maximumError.
    for (int j = 0; j < textSize; j++){
            if (matrix[patternSize-1][j] <= maximumError){
                // Match with edit cost of, at most, maximum error.
                return true;
            }
    }
    return false;
}

void searchSellers(string pattern, vector<string> textList, int maximumError, bool isCount){
    // Wrapper function that calls the main searching ones.
    if (isCount){
        int totalOccurrences = 0;
        for (string text : textList) {
            totalOccurrences += countSellers(pattern, text, maximumError);
        }
        cout << "The pattern occurred " << totalOccurrences << " times in the given text." << endl;
    
    } else {
        for (string text : textList) {
            if(checkSellers(pattern, text, maximumError)){
                cout << text << endl;
            }
        }
    }
}