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

const int LEN = 10;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ":\n";
        int n;
        cin >> n;
        string s;
        cin >> s;
        char firstChar = s[0] == '.' ? '-' : '.';
        for (int i = 1; i < n; ++i) {
            cout << firstChar;
            for (int j = 0; j < LEN - 1; ++j) {
                if (i & (1 << j)) {
                    cout << "-";
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
