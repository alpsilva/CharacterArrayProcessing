#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "charMask.h"
#define ASCII 128
using namespace std;


void stringSearchCountOcurrences(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII]){
    uint64_t mask = UINT64_MAX;
    uint64_t totalOccurrences = 0;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;

    vector<uint64_t> lineOcurrences;
    
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++){

        const uint64_t textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++){
            mask = (mask << 1) | charMask[text[lineCount][i]];
            if(!(mask & bitMaskMSB)){
                totalOccurrences++;
            }
        }
    }
    cout << "The pattern " << prefix << " occurred " << totalOccurrences << " times in the given text." << endl;
}

void stringSearch(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], bool isLineCount){
    uint64_t mask = UINT64_MAX;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;

    vector<uint64_t> lineOcurrences;
    
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++){
        bool found = false;
        const uint64_t textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++){
            mask = (mask << 1) | charMask[text[lineCount][i]];
            if(!(mask & bitMaskMSB)){
                lineOcurrences.push_back(lineCount);
                break;
            }
        }
    }
    
    if(isLineCount){
        cout << "The pattern " << prefix << " was found in " << lineOcurrences.size() << " lines in the given text." << endl;
        return;
    } 

    for(uint64_t line: lineOcurrences){
        cout << line + 1 << " - " << text[line] << endl;
    }
}

void shiftOr(const string& prefix, const vector<string>& text, bool isCount, bool isLineCount){
    uint64_t prefixLen = prefix.length();

    uint64_t charMask[ASCII];
    preProcessCharMask(prefix, prefixLen, charMask);

    if(isCount){
        stringSearchCountOcurrences(prefix, prefixLen-1, text, charMask);
        return;
    }
    stringSearch(prefix, prefixLen-1, text, charMask, isLineCount);
}