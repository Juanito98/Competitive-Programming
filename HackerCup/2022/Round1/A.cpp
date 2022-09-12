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

const int MAXN = 500002;

vector<int> build_PI(vector<int> &P) {
    vector<int> PI(P.size());
    PI[0] = 0;
    int k = 0;
    for (int i = 1; i < P.size(); ++i) {
        while (k > 0 && P[k] != P[i]) {
            k = PI[k-1];
        }
        if (P[k] == P[i]) {
            k++;
        }
        PI[i] = k;
    }
    return PI;
}

bool KMP_Match(vector<int>& T, vector<int>& P) {
    vector<int> PI = build_PI(P);
    int q = 0;
    for (int i = 0; i < T.size(); ++i) {
        while (q > 0 && P[q] != T[i]) {
            q = PI[q - 1];
        }
        if (P[q] == T[i]) {
            q++;
        }
        if (q == P.size()) {
            return true;
        }
    }
    return false;
}

int n, k;
vector<int> A, B;

bool possible() {
    if (n == 2) {
        if (A[0] == A[1]) {
            return true;
        }
        if (A == B) {
            return (k & 1) == 0;
        } else {
            return (k & 1) == 1;
        }
    }
    if (A == B) {
        return k != 1;
    }
    if (k == 0) {
        return false;
    }
    B.resize(2 * n);
    for (int i = 0; i < n; ++i) {
        B[i + n] = B[i];
    }
    
    return KMP_Match(B, A);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        cin >> n >> k;
        A.resize(n);
        B.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> B[i];
        }
        cout << (possible() ? "YES" : "NO") << "\n";
    }

    return 0;
}
