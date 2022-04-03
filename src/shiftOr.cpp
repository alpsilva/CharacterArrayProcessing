#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include "utils.cpp"
#define ASCII 128
using namespace std;

void fillCharMask(uint64_t charMask[ASCII])
{
    for(uint16_t i = 0; i < ASCII; i++)
    {
        charMask[i] = UINT64_MAX;
    }
}

void preProcess(const string& prefix, uint64_t prefixLen, uint64_t charMask[ASCII])
{
    fillCharMask(charMask);

    for(uint16_t i = 0; i < prefixLen; i++)
    {
        charMask[prefix[i]] &= ~(1 << i); 
    }
}

void stringSearch(uint64_t mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII])
{
    uint64_t mask = UINT64_MAX;
    uint64_t count = 0;

    uint64_t vectorLength = text.size();
    uint64_t bitMaskMSB = 1 << mostSignificantBit;
    
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++)
    {
        bool found = false;
        const uint64_t textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++)
        {
            mask = (mask << 1) | charMask[text[lineCount][i]];
            if(!(mask & bitMaskMSB))
            {
                count++;
                found = true;
            }
        }

    }
    
    cout << "number of ocurrences is: " << count << endl;
}

int shiftOr(const string& prefix, const vector<string>& text)
{
    uint64_t prefixLen = prefix.length();
    if(prefixLen > 8)
    {
        cout << "Pattern too long, max efficient length is 8." << endl;
    }
    uint64_t charMask[ASCII];
    preProcess(prefix, prefixLen, charMask);
    stringSearch(prefixLen-1, text, charMask);
}