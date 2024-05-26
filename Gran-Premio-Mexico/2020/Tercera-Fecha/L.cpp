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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    set<string> S;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        string lower = s;
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j+1 < s.size(); ++j)
                swap(s[j], s[j+1]);
            if (lower > s) lower = s;
        }
        S.insert(lower);
    }

    cout << S.size() << "\n";

    return 0;
}