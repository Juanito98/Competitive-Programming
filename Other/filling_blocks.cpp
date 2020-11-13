/*
    DP estilo tetris
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

const int MAXN = 100;
int memo[MAXN][3][3][3][3];
bool vis[MAXN][3][3][3][3];

int dp(int i, vector<int> a) {
    if (i < 0) return 0;
    int mayor = max(max(a[0], a[1]), max(a[2], a[3]));
    if (i == 0 && mayor == 0) return 1;
    if (!vis[i][a[0]][a[1]][a[2]][a[3]]) {
        vis[i][a[0]][a[1]][a[2]][a[3]] = true;
        int j = 0;
        for (j = 0; mayor != a[j]; ++j)
            ;
        // ponerla horizontal
        int recorre = 2 - a[j];
        vector<int> b = a;
        for (int k = 0; k < b.size(); ++k)
            b[k] += recorre;
        b[j] = 0;
        memo[i][a[0]][a[1]][a[2]][a[3]] += dp(i - recorre, b);

        // ponerlo vertical
        if (j < 3 && a[j] == a[j + 1]) {
            b = a;
            if (a[j] == 0) {
                // se recorre
                for (int k = 0; k < b.size(); ++k)
                    b[k]++;
                b[j] = b[j + 1] = 0;
                memo[i][a[0]][a[1]][a[2]][a[3]] += dp(i - 1, b);
            } else {
                // no se recorre
                b[j]--;
                b[j + 1]--;
                memo[i][a[0]][a[1]][a[2]][a[3]] += dp(i, b);
            }
        }
    }
    return memo[i][a[0]][a[1]][a[2]][a[3]];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << dp(n, {0, 0, 0, 0}) << "\n";

    return 0;
}