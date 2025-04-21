// Program Name: stringMatchHorspool.cpp
// Program Description: Uses Horspool's algorithm to locate a matching 
//                      substring within a given text and counts comparisons.
// Based on work by: Mihail Chitorog
// Date: April 19, 2025

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// function to generate shift table for Horspool's algorithm
unordered_map<char, int> buildShiftTable(const string& pattern) {
    int m = pattern.length();
    unordered_map<char, int> shiftTable;

    // default shift is pattern length for characters not in pattern
    for (int i = 0; i < 128; i++) {
        shiftTable[static_cast<char>(i)] = m;
    }

    // for characters in pattern (except last), set their shift values
    for (int i = 0; i < m - 1; i++) {
        shiftTable[pattern[i]] = m - 1 - i;
    }

    return shiftTable;
}

// function to print shift table
void printShiftTable(const unordered_map<char, int>& shiftTable, const string& pattern) {
    cout << "Shift Table:" << endl;
    cout << "-----------" << endl;

    // print only characters in pattern (once each)
    for (size_t i = 0; i < pattern.length(); i++) {
        char c = pattern[i];
        bool already_printed = false;
        for (size_t j = 0; j < i; j++) {
            if (pattern[j] == c) {
                already_printed = true;
                break;
            }
        }

        if (!already_printed) {
            cout << "'" << c << "': " << shiftTable.at(c) << endl;
        }
    }

    // show default shift value for characters not in pattern
    cout << "Default: " << pattern.length() << endl;
    cout << "-----------" << endl;
}

// horspool's algorithm for string searching
void horspool(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m > n || m == 0) {
        cout << "No matches found." << endl;
        return;
    }

    // build shift table
    unordered_map<char, int> shiftTable = buildShiftTable(pattern);

    // print shift table
    printShiftTable(shiftTable, pattern);

    int comparisons = 0;
    vector<int> matches;

    // start with the end of pattern aligned at position m - 1 in text
    int i = m - 1;

    while (i < n) {
        int k = 0;

        // try to match pattern from right to left
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            comparisons++;
            k++;
        }

        // if k equals m, a match was found
        if (k == m) {
            matches.push_back(i - m + 1);
        } else {
            comparisons++;  // count comparison that led to mismatch
        }

        // get shift value from table
        char c = (i < n) ? text[i] : ' ';
        int shift = shiftTable[c];

        // make sure we always make progress
        i += (shift > 0) ? shift : 1;
    }

    cout << "Number of matches found: " << matches.size() << endl;

    if (!matches.empty()) {
        cout << "Matches located at positions: ";
        for (size_t j = 0; j < matches.size(); j++) {
            cout << matches[j];
            if (j < matches.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "Total number of character comparisons: " << comparisons << endl;
}

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    cout << "\n==============================================\n";
    cout << "Text: \"" << text << "\"\n";
    cout << "Pattern: \"" << pattern << "\"\n";
    cout << "==============================================\n";

    horspool(text, pattern);

    return 0;
}
