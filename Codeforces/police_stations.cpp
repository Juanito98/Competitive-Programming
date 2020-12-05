/*
    BFS Problem
    Idea buena. Demostración por contradicción
    https://codeforces.com/contest/796/problem/D
*/
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

const int MAX = 300002;

int n, k, d;
vector<pii> adj[MAX];
bool used[MAX];

queue<int> q;
bool vis[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> d;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        if (vis[x]) continue;
        q.push(x);
        vis[x] = true;
    }
    k = q.size();
    
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    //bfs
    while (!q.empty()) {
        int nodo = q.front();
        q.pop();
        for (auto p : adj[nodo]) {
            if (vis[p.first]) continue;
            vis[p.first] = true;
            used[p.second] = true;
            q.push(p.first);
        }
    }

    cout << k - 1 << "\n";
    for (int i = 1; i < n; ++i) 
        if (!used[i])
            cout << i << " ";
    cout << "\n";
    return 0;
}