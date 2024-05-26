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

const int MAXN = 100002;
const lld M = 1e9 + 7;

lld exp(lld b, lld e) {
    if (e == 0) return 1;
    lld x = exp(b, e / 2);
    x *= x;
    x %= M;
    if (e & 1) {
        x *= b;
        x %= M;
    }
    return x;
}
lld inv(lld x) { return exp(x, M-2); }

int n;
vector<int> adj[MAXN];

bool vis[MAXN][2];
lld memo[MAXN][2];
lld dp(int node, bool known) {
    if (adj[node].empty()) return 1;
    if (!vis[node][known]) {
        vis[node][known] = true;
        // Obtener el producto de conocer todos
        vector<lld> L(adj[node].size()), R(adj[node].size());
        for (int i = 0; i < adj[node].size(); ++i) {
            int h = adj[node][i];
            L[i] = R[i] = dp(h, 0);
        }
        for (int i = 1; i < adj[node].size(); ++i) {
            L[i] = (L[i] * L[i-1]) % M;
            R[adj[node].size() - i - 1] = (R[adj[node].size() - i - 1] * R[adj[node].size() - i]) % M;
        }
        if (!known) 
            memo[node][known] += R[0];
        // le sumo conocer todos menos uno
        for (int i = 0; i < adj[node].size(); ++i) {
            lld f = 1;
            if (i > 0) f = (f * L[i-1]) % M;
            if (i+1 < adj[node].size()) f = (f * R[i+1]) % M;
            f = (f * dp(adj[node][i], 1)) % M;
            memo[node][known] += f;
            memo[node][known] %= M;
        }
    }
    return memo[node][known];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    cout << dp(1, 0) << "\n";

    return 0;
}