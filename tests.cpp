#include <BoyerMoore.cpp>

using namespace std;

int main(){

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