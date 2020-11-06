/*
https://codeforces.com/gym/101628/problem/I
Elevar una matriz
*/
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

const int MAXN = 102;
const lld M = 1e9 + 7;

int n, k;


vector<vector<lld>> multiply(vector<vector<lld>> a, vector<vector<lld>> b) {
    int r = a.size();
    int n = b.size();
    int c = b[0].size();
    vector<vector<lld>> matriz(r, vector<lld>(c, 0));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < n; ++k) {
                matriz[i][j] += (a[i][k] * b[k][j]) % M;
            }
            matriz[i][j] %= M;
        }
    }
    return matriz;
}

vector<vector<lld>> powMatrix(vector<vector<lld>>& matriz, int e) {
    if (e == 1) return matriz;
    vector<vector<lld>> x = powMatrix(matriz, e / 2);
    x = multiply(x, x);
    if (e & 1) {
        x = multiply(x, matriz);
    }
    return x;
}

lld exp_mod(lld num, lld e) {
    if (e == 0) return 1ll;
    lld x = exp_mod(num, e / 2);
    x *= x;
    x %= M;
    if (e & 1) {
        x *= num;
        x %= M;
    }
    return x;
}

lld inv(lld num) {
    return exp_mod(num, M-2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    vector<vector<lld>> matriz(n, vector<lld>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matriz[i][j];
        }
    }

    matriz = powMatrix(matriz, k);

    lld ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += ((lld)(i+1) * matriz[0][i]);
        ans %= M;
    }
    ans *= exp_mod(inv(1e6), k);
    ans %= M;

    cout << ans << "\n";
    return 0;
}