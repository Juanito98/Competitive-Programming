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

bool haveToSwitchHand(char c, int hand) {
    return (c == 'X' && hand == 1) || (c == 'O' && hand == 0);
}

int calcula(const string& s, int hand) {
    int curr = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (haveToSwitchHand(s[i], hand)) {
            hand ^= 1;
            curr++;
        }
    }
    return curr;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        int n;
        string s;
        cin >> n >> s;
        cout << min(calcula(s, 0), calcula(s, 1)) << "\n";
    }

    return 0;
}