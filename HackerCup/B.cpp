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

const int MAXN = 800002;
const int LOGN = 20;

int n;
vector<int> adj[MAXN];
int peso[MAXN];

int superLCA[MAXN]; // Por frecuencias
int level[MAXN];
int padre[MAXN][LOGN];

void bfs() {
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int nodo = q.front();
        q.pop();
        for (int h : adj[nodo]) {
            if (h == padre[nodo][0]) continue;
            padre[h][0] = nodo;
            level[h] = level[nodo] + 1;
            q.push(h);
        }
    }
}

void sparse() {
    for (int l = 1; l < LOGN; ++l) {
        for (int nodo = 1; nodo <= n; ++nodo) {
            padre[nodo][l] = padre[padre[nodo][l-1]][l-1];
        }
    }
}

int lca(int a, int b) {
    if (level[a] < level[b]) {
        swap(a, b);
    }
    // brincamos a
    {
        int w = level[a] - level[b];
        int k = 0;
        while (w) {
            if (w & 1) {
                a = padre[a][k];
            }
            w >>= 1;
            k ++;
        }
    }
    if (a == b) return a;
    // Brincamos a ambos
    for (int i = LOGN - 1; i >= 0; --i) {
        if (padre[a][i] != padre[b][i]) {
            a = padre[a][i];
            b = padre[b][i];
        }
    }
    return padre[a][0];
}

void closePath(int nodo, int f) {
    if (superLCA[f] == -1) {
        superLCA[f] = nodo;
        return;
    }
    int l = lca(nodo, superLCA[f]);
    peso[nodo] ++;
    peso[superLCA[f]]++;
    peso[l] -= 2;
    superLCA[f] = l;
}

int suma[MAXN];
void dfs() {
    stack<int> p;
    p.push(1);
    while (!p.empty()) {
        int nodo = p.top();
        p.pop();
        if (nodo > 0) {
            // Calcular suma de sus hijos
            p.push(-nodo);
            for (int h : adj[nodo]) {
                if (h == padre[nodo][0]) continue;
                p.push(h);
            }
        } else {
            // Calcular su suma
            nodo = -nodo;
            suma[nodo] = peso[nodo];
            for (int h : adj[nodo]) {
                if (h == padre[nodo][0]) continue;
                suma[nodo] += suma[h];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            superLCA[i] = -1;
            peso[i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        bfs();
        sparse();
        for (int i = 1; i <= n; ++i) {
            int f;
            cin >> f;
            closePath(i, f);
        }
        dfs();
        int ans = 0;
        for (int nodo = 2; nodo <= n; ++nodo) {
            if (suma[nodo] == 0) ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}