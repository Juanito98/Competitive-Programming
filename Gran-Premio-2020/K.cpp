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
int n, m, k;

int padre[MAXN];
int root(int nodo) {
    if (!padre[nodo]) return nodo;
    return padre[nodo] = root(padre[nodo]);
}

void join(int i, int j) {
    int ra = root(i), rb = root(j);
    if (ra == rb) return;
    padre[rb] = ra;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    vector<pii> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int usados = 0;
    
    vector<bool> used(m);
    sort(edges.begin(), edges.end());
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        tie(u, v) = edges[i];
        if (root(u) == root(v)) continue;
        used[i] = true;
        join(u, v);
        usados ++;
    }

    bool imposible = k < n-1;

    int componente = root(1);
    for (int nodo = 2; nodo <= n; ++nodo) {
        if (root(nodo) != componente) 
            imposible = true;
    }

    for (int i = 0; i < m && usados < k; ++i) {
        if (used[i]) continue;
        used[i] = true;
        usados++;
    }

    if (usados != k) imposible = true;

    vector<int> degree(n+1);
    for (int i = 0; i < m; ++i) {
        if (used[i]) {
            degree[edges[i].first]++;
            degree[edges[i].second]++;
        }
    }

    if (imposible) {
        cout << "Impossible";
    } else {
        cout << degree[1];
        for (int nodo = 2; nodo <= n; ++nodo) {
            cout << " " << degree[nodo];
        }
    }
    cout << endl;

    return 0;
}