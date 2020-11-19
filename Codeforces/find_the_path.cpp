/*
    BFS
    https://codeforces.com/gym/101992/problem/H
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

const int MAX = 100002;

int n, m, u, L, K; 
vector<pii> adj[MAX];

int maxW[MAX];
queue<int> q;
bool vis[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("path.in", "r")) freopen("path.in", "r", stdin);
    int T;
    for (cin >> T; T; --T) {
        cin >> n >> m >> u >> L >> K;
        for (int i = 1; i <= n; ++i)
            adj[i].clear();
        while (!q.empty()) q.pop();
        fill(vis + 1, vis + n + 1, false);
        fill(maxW, maxW + K + 1, 0);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
        }
        int nodo = u;
        q.push(nodo);
        for (int i = 1; i <= K; ++i) {
            maxW[i] = maxW[i-1];
            for (int sz = q.size(); sz; --sz) {
                nodo = q.front();
                q.pop();
                if (vis[nodo]) continue;
                vis[nodo] = true;
                for (auto p : adj[nodo]) {
                    maxW[i] = max(maxW[i], p.second);
                    q.push(p.first);
                }
            }
        }
        cout << maxW[K] << "\n";
    }

    return 0;
}