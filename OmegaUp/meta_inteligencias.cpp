// PES 2021 Mayo Dia 1
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

const int MAXN = 100002;

int n, L;
pii arr[MAXN];
vector<int> adj[MAXN];

map<int, int>* cmp[MAXN];      // El arbol que forma sus idiomas
vector<pii>* lenguajes[MAXN];  // Conjunto de idiomas que domina
int ans[MAXN];

int raiz(int nodo, map<int, int>* cmp) {
    if ((*cmp)[nodo] == 0) return nodo;
    return (*cmp)[nodo] = raiz((*cmp)[nodo], cmp);
}

void merge(int nodo, int hijo) {
    if (lenguajes[hijo]->size() > lenguajes[nodo]->size()) {
        swap(lenguajes[hijo], lenguajes[nodo]);
        swap(cmp[nodo], cmp[hijo]);
    }

    // Small to large
    for (pii p : *lenguajes[hijo]) {
        // Union find en nodo
        int ra = raiz(p.first, cmp[nodo]);
        int rb = raiz(p.second, cmp[nodo]);
        if (ra == rb) continue;
        lenguajes[nodo]->push_back(p);
        (*cmp[nodo])[ra] = rb;
    }
}

void dfs(int nodo, int p = -1) {
    lenguajes[nodo] = new vector<pii>(1, arr[nodo]);
    cmp[nodo] = new map<int, int>();
    (*cmp[nodo])[arr[nodo].first] = arr[nodo].second;

    for (int h : adj[nodo]) {
        if (p == h) continue;
        dfs(h, nodo);
        merge(nodo, h);
    }

    ans[nodo] = L - 1 - lenguajes[nodo]->size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> L;

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        if (i != 1) adj[p].push_back(i);
    }

    for (int i = 1; i <= n; ++i)
        cin >> arr[i].first >> arr[i].second;

    dfs(1);

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";

    cout << "\n";

    return 0;
}