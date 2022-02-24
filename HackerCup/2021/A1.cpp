#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

bool isVowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

bool isConsonant(char c) {
    return !isVowel(c);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        string s;
        cin >> s;

        unordered_map<char, int> keys;
        for (char c : s) {
            keys[c]++;
        }
        
        int mfv = 0;
        char v = 'a';
        int mfc = 0;
        char c = 'b';
        for (auto it : keys) {
            if (isVowel(it.first) && mfv < it.second) {
                mfv = it.second;
                v = it.first;
            } else if (isConsonant(it.first) && mfc < it.second) {
                mfc = it.second;
                c = it.first;
            }
        }

        int ansV = 0, ansC = 0;
        for (char u : s) {
            // Hacerla mfv
            if (isVowel(u)) {
                if (u != v) ansV += 2;
            } else {
                ansV++;
            }
            // Hacerla mfc
            if (isConsonant(u)) {
                if (u != c) ansC += 2;
            } else {
                ansC++;
            }
        }

        cout << "Case #" << caso << ": ";
        cout << min(ansC, ansV) << "\n";
    }

    return 0;
}