#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
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

const int INF = 1e7;

vector<vector<int>> multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int r = A.size();
    int n = A[0].size();
    int c = B[0].size();
    vector<vector<int>> C(r, vector<int>(c, INF));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
    return C;
}

vector<vector<int>> powMatrix(const vector<vector<int>>& matriz, int e) {
    if (e == 1) return matriz;
    vector<vector<int>> x = powMatrix(matriz, e/2);
    x = multiply(x, x);
    if (e & 1) {
        x = multiply(x, matriz);
    }
    return x;
}

bool evenCycle(const vector<vector<int>>& Pk) {
    int n = Pk.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (Pk[i][j] + Pk[j][i] < 0) return true;
    return false;
}

bool oddCycle(const vector<vector<int>>& P, const vector<vector<int>>& Pk) {
    int n = Pk.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                if (P[i][j] + Pk[j][k] + Pk[k][i] < 0) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> P(n, vector<int>(n, INF));
    for (int i = 0; i < m; ++i) {
        int a, b, c_ab, c_ba;
        cin >> a >> b >> c_ab >> c_ba;
        P[a-1][b-1] = -c_ab;
        P[b-1][a-1] = -c_ba;
    }

    int l = 1, r = (n + 1) / 2;
    while (l < r) {
        int med = (l + r) / 2;
        vector<vector<int>> Pk = powMatrix(P, med);
        if (evenCycle(Pk) || oddCycle(P, Pk))
            r = med;
        else
            l = med + 1;
    }

    vector<vector<int>> Pl = powMatrix(P, l);
    if (evenCycle(Pl)) {
        cout << 2*l << "\n";
    } else if (oddCycle(P, Pl)) {
        cout << 2*l + 1 << "\n";
    } else {
        cout << "0\n";
    }
    return 0;
}