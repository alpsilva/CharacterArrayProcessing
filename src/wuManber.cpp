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

void preProcessCharMask(const string& prefix, uint prefixLen, uint64_t charMask[ASCII])
{
    fillCharMask(charMask);

    for(uint16_t i = 0; i < prefixLen; i++)
    {
        charMask[prefix[i]] &= ~(1 << i); 
    }
}

void preProcessErrorMask(uint16_t maxDist, vector<uint64_t>& errorMask)
{
    errorMask.push_back(UINT64_MAX);
    for(uint16_t q = 1; q <= maxDist; q++)
    {
        errorMask.push_back(errorMask[q-1] << 1);
    }
}

void print_binary(uint64_t number)
{
    if (number >> 1) {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}


void stringSearch(uint mostSignificantBit, const vector<string>& text, uint64_t charMask[ASCII], 
    vector<uint64_t> errorMask, uint16_t maxDist)
{
    uint64_t mask = UINT64_MAX;
    uint64_t count = 0;

    uint64_t vectorLength = text.size();
    const uint64_t bitMaskMSB = 1 << mostSignificantBit;
    uint64_t countLine = 0;
    for(uint64_t lineCount = 0; lineCount < vectorLength; lineCount++)
    {
        bool found = false;
        const uint textLen = text[lineCount].length();
        for(uint64_t i = 0; i < textLen; i++)
        {
            vector<uint64_t> tempErrorMask;
            uint64_t temp = (errorMask[0] << 1) | charMask[text[lineCount][i]];
            tempErrorMask.push_back(temp);
            for(uint16_t q = 1; q <= maxDist; q++)
            {
                temp = ((errorMask[q] << 1) | charMask[text[lineCount][i]]) & (errorMask[q-1] << 1) 
                    & (tempErrorMask[q-1] << 1) & errorMask[q-1];
                tempErrorMask.push_back(temp);
            }
            errorMask.swap(tempErrorMask);
            if(!(errorMask[maxDist] & bitMaskMSB))
            {
                //count++;
                found = true;
            }
        }
        if(found)
        {
            //countLine++;
            cout << text[lineCount] << endl;
        }
    }
    //cout << countLine << endl;
    //cout << "number of ocurrences is: " << count << endl;
}

int main(int argc, char *argv[])
{
    string prefix = argv[1];
    uint prefixLen = prefix.length();
    if(prefixLen == 0)
    {
        cout << "Please provide a pattern." << endl;
        return 0;
    }

    vector<string> text = readStringFromFile(argv[2]);
    if(prefixLen >= 8)
    {
        cout << "Pattern too long, this algorithm is most efficient when the pattern is less than 9 characters, in a 64 bit computer. you should use another algorithm" << endl;
    }


    uint64_t charMask[ASCII];
    preProcessCharMask(prefix, prefixLen, charMask);

    vector<uint64_t> errorMask;
    uint16_t maxDist = 1;
    preProcessErrorMask(maxDist, errorMask);

    stringSearch(prefixLen-1, text, charMask, errorMask, maxDist);
}

