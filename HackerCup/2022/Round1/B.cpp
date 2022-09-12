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

const lld MOD = 1000000007;
const int MAXN = 500002;

vector<lld> Ax, Bx, Ay, By;

void read(vector<lld>& X, vector<lld>& Y) {
    int n;
    cin >> n;
    X.resize(n);
    Y.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> X[i] >> Y[i];
    }
}

lld pmod(lld a, lld b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

lld smod(lld a, lld b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

lld mmod(lld a, lld b) {
    return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

lld sum(const vector<lld>& arr) {
    lld s = 0;
    for (int i = 0; i < arr.size(); ++i) {
        s += arr[i];
    }
    return s % MOD;
}

lld sumSquares(const vector<lld>& arr) {
    lld s = 0;
    for (int i = 0; i < arr.size(); ++i) {
        s += pmod(arr[i], arr[i]);
    }
    return s % MOD;
}

lld sumSquareDiff(vector<lld>& A, vector<lld>& B) {
    int n = A.size(), m = B.size();
    lld one = pmod(m, sumSquares(A));
    lld two = pmod(2, pmod(sum(A), sum(B)));
    lld three = pmod(n, sumSquares(B));
    return mmod(smod(one, three), two);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        read(Ax, Ay);
        read(Bx, By);
        lld ans = smod(
            sumSquareDiff(Ax, Bx),
            sumSquareDiff(Ay, By)
        );
        cout << ans << "\n";
    }

    return 0;
}
