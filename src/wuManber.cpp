#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include "charMask.h"

using namespace std;

void preProcessErrorMask(uint16_t maxDist, vector<uint64_t>& errorMask)
{
    errorMask.push_back(UINT64_MAX);
    for(int q = 1; q <= maxDist; q++)
    {
        errorMask.push_back(errorMask[q-1] << 1);
    }
}

void stringSearchCountOcurrences(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], 
    vector<uint64_t>& errorMask, const int maxDist)
{
    uint64_t totalOccurrences = 0;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;

    
    for (uint64_t lineCount = 0; lineCount < vectorLength; lineCount++)
    {
        bool found = false;
        const uint64_t textLen = text[lineCount].length();
        for (uint64_t i = 0; i < textLen; i++)
        {
            vector<uint64_t> tempErrorMask(maxDist+1);
            tempErrorMask[0] = (errorMask[0] << 1) | charMask[text[lineCount][i]];
            for (int q = 1; q <= maxDist; q++)
            {
                tempErrorMask[q] = ((errorMask[q] << 1) | charMask[text[lineCount][i]]) & (errorMask[q - 1] << 1)
                    & (tempErrorMask[q - 1] << 1) & errorMask[q - 1];
            }
            errorMask.swap(tempErrorMask);
            if (!(errorMask[maxDist] & bitMaskMSB))
            {
                totalOccurrences++;
            }
        }
    }
    cout << "The pattern " << prefix << " occurred (with a maximum edit cost of " << maxDist << ") " << totalOccurrences << " times in the given text." << endl;
}

void stringSearch(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], 
    vector<uint64_t> errorMask, const int maxDist, const bool isCountLines)
{
    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;
    vector<uint64_t> lineOcurrences;
    
    for (uint64_t lineCount = 0; lineCount < vectorLength; lineCount++){
        const uint64_t textLen = text[lineCount].length();
        for (uint64_t i = 0; i < textLen; i++)
        {
            vector<uint64_t> tempErrorMask(maxDist+1);
            tempErrorMask[0] = (errorMask[0] << 1) | charMask[text[lineCount][i]];
            for (int q = 1; q <= maxDist; q++)
            {
                tempErrorMask[q] = ((errorMask[q] << 1) | charMask[text[lineCount][i]]) & (errorMask[q - 1] << 1)
                    & (tempErrorMask[q - 1] << 1) & errorMask[q - 1];
            }
            errorMask.swap(tempErrorMask);
            if (!(errorMask[maxDist] & bitMaskMSB))
            {
                lineOcurrences.push_back(lineCount);
                break;
            }
        }
    }

    if (isCountLines) {
        cout << "The pattern " << prefix << " (with a maximum edit cost of " << maxDist << ") was found in " << lineOcurrences.size() << " lines in the given text." << endl;
        return;
    }

    for(uint64_t line: lineOcurrences){
        cout << line + 1 << " - " << text[line] << endl;
    } 
}

void wuManber(const string& prefix, const vector<string>& text, const int eMax, const bool isCount, const bool isLineCount)
{
    uint64_t prefixLen = prefix.length();

    uint64_t charMask[ASCII];
    preProcessCharMask(prefix, prefixLen, charMask);

    vector<uint64_t> errorMask;
    const int maxDist = eMax;
    preProcessErrorMask(maxDist, errorMask);

    if(isCount){
        stringSearchCountOcurrences(prefix , prefixLen-1, text, charMask, errorMask, maxDist);
        return;
    }
    stringSearch(prefix , prefixLen-1, text, charMask, errorMask, maxDist, isLineCount);
}

