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

void stringSearch(const string& prefix, uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], 
    vector<uint64_t> errorMask, const int maxDist, const bool isCount)
{
    uint64_t totalOccurrences = 0;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;

    vector<uint64_t> lineOcurrences;
    
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++)
    {
        bool found = false;
        const uint64_t textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++)
        {
            vector<uint64_t> tempErrorMask;
            uint64_t temp = (errorMask[0] << 1) | charMask[text[lineCount][i]];
            tempErrorMask.push_back(temp);
            for(int q = 1; q <= maxDist; q++)
            {
                temp = ((errorMask[q] << 1) | charMask[text[lineCount][i]]) & (errorMask[q-1] << 1) 
                    & (tempErrorMask[q-1] << 1) & errorMask[q-1];
                tempErrorMask.push_back(temp);
            }
            errorMask.swap(tempErrorMask);
            if(!(errorMask[maxDist] & bitMaskMSB))
            {
                totalOccurrences++;
                found = true;
            }
        }
        if(found)
        {
            lineOcurrences.push_back(lineCount);
        }
    }

    if(isCount){
        cout << "The pattern " << prefix << " occurred (with a maximum edit cost of " << maxDist << ") " << totalOccurrences << " times in the given text." << endl;
    } else {
        for(uint64_t line: lineOcurrences){
            cout << text[line] << endl;
        }
    }
}

void wuManber(const string& prefix, const vector<string>& text, const int eMax, const bool isCount)
{
    uint64_t prefixLen = prefix.length();
    if(prefixLen >= 8)
    {
        cout << "Pattern too long, this algorithm is most efficient when the pattern is less than 9 characters, in a 64 bit computer. you should use another algorithm" << endl;
    }

    uint64_t charMask[ASCII];
    preProcessCharMask(prefix, prefixLen, charMask);

    vector<uint64_t> errorMask;
    const int maxDist = eMax;
    preProcessErrorMask(maxDist, errorMask);

    stringSearch(prefix , prefixLen-1, text, charMask, errorMask, maxDist, isCount);
}

