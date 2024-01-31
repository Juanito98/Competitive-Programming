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

int mostSignificantDistinctBit(lld x, lld y) {
    for (int i = 63; i >= 0; --i) {
        if (((x >> i) & 1) != ((y >> i) & 1)) {
            return i;
        }
    }
    return -1;
}


/*
Given x >= y, find min (x^z - y^z)
such that 0 <= z <= r and x^z - y^z >=0
*/
lld solve(lld x, lld y, lld r) {
    if (x == y) {
        return 0;
    }
    int msdb = mostSignificantDistinctBit(x, y);
    // Optimal are the bits of x that are 1 and y that are 0
    // without the msdb
    lld optimal = (x ^ y) & (x ^ (1ll << msdb));
    lld z = 0;
    // Optimal then should be less or equal than r
    for (int i = 63; i >= 0; --i) {
        if ((optimal >> i) & 1) {
            if ((z ^ (1ll << i)) <= r) {
                z ^= (1ll << i);
            }
        }
    }
    return (x ^ z) - (y ^ z);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; --T) {
        lld x, y, r;
        cin >> x >> y >> r;
        if (x < y) {
            swap(x, y);
        }
        lld ans = solve(x, y, r);
        int msdb = mostSignificantDistinctBit(x, y);
        if (msdb != -1 && (1ll << msdb) <= r) {
            int msdb = mostSignificantDistinctBit(x, y);
            lld yy = x ^ (1ll << msdb);
            lld xx = y ^ (1ll << msdb);
            lld rr = r - (1ll << msdb);
            ans = min(ans, solve(xx, yy, rr));
        }
        cout << ans << "\n";
    }

    return 0;
}
