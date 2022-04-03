#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "charMask.h"
#define ASCII 128
using namespace std;


void stringSearch(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], bool isCount){
    uint64_t mask = UINT64_MAX;
    uint64_t totalOccurrences = 0;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;

    vector<uint64_t> lineOcurrences;
    
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++){
        bool found = false;
        const uint64_t textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++){
            mask = (mask << 1) | charMask[text[lineCount][i]];
            if(!(mask & bitMaskMSB)){
                totalOccurrences++;
                found = true;
            }
        }
        if(found){
            lineOcurrences.push_back(lineCount);
        }
    }
    
    if(isCount){
        cout << "The pattern " << prefix << " occurred " << totalOccurrences << " times in the given text." << endl;
    } else {
        for(uint64_t line: lineOcurrences){
            cout << text[line] << endl;
        }
    }
}

void shiftOr(const string& prefix, const vector<string>& text, bool isCount){
    uint64_t prefixLen = prefix.length();
    if(prefixLen > 8){
        cout << "Pattern too long, max efficient length is 8." << endl;
    }
    uint64_t charMask[ASCII];
    preProcessCharMask(prefix, prefixLen, charMask);
    stringSearch(prefix, prefixLen-1, text, charMask, isCount);
}