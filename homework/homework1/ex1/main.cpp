//
// Created by liu on 17-5-20.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ofstream out("1.tex");

    string caesar_cipher = "EVIRE";
    for (char i = 0; i < 26; i++) {
        string temp;
        for (auto ch:caesar_cipher) {
            temp += ((ch - 'A' + i) % 26 + 'A');
        }
        out << temp << endl;
    }
    return 0;
}