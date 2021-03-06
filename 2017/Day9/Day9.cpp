#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int nested = 0, total = 0, garbage = 0, gc = 0;
    char ch;
 
    ifstream myfile("Input.txt");

    if (myfile.is_open()) {
        while (myfile >> ch) {
            if (!garbage) {
                switch (ch) {
                case '<':
                    garbage = 1;
                    break;
                case '{':
                    ++nested;
                    break;
                case '}':
                    total += nested--;
                    break;
                }
            }
            else {
                switch (ch) {
                case '!':
					// Skip and get next char
                    myfile.get();
                    break;
                case '>':
                    garbage = 0;
                    break;
                default:
                    gc++;
                    break;
                }
            }
        }
    } else {
        cout << "cannot open file " << endl;
        return 0;
    }

    cout << "Part one: "<< total << endl;
    cout << "Part two: " << gc << endl;
	
    return 0;
}