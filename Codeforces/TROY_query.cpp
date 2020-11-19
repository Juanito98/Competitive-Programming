/*
    2SAT Problem
    https://codeforces.com/gym/100570/problem/D
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

map<lld, int> rowMap;
map<lld, int> columnMap;
int nextId;
int getRowNode(lld r) {
    if (rowMap.count(r) == 0) 
        rowMap[r] = nextId++;
    return rowMap[r];
}
int getColumnNode(lld r) {
    if (columnMap.count(r) == 0)
        columnMap[r] = nextId++;
    return columnMap[r];
}

const int MAX = 200002;
int n;
//We have a vertex representing a var and other for his negation.
//Every edge stored in G represents an implication. To add an equation of the form a||b, use addor(a, b)
//MAX=max cant var, n=cant var
#define addor(a, b) (G[neg(a)].push_back(b), G[neg(b)].push_back(a))
vector<int> G[MAX * 2];
//idx[i]=index assigned in the dfs
//lw[i]=lowest index(closer from the root) reachable from i
int lw[MAX * 2], idx[MAX * 2], qidx;
stack<int> q;
int qcmp, cmp[MAX * 2];
//verdad[cmp[i]]=valor de la variable i
bool verdad[MAX * 2 + 1];

int neg(int x) { return x >= n ? x - n : x + n; }
void tjn(int v) {
    lw[v] = idx[v] = ++qidx;
    q.push(v), cmp[v] = -2;
    for (int u : G[v]) {
        if (!idx[u] || cmp[u] == -2) {
            if (!idx[u]) tjn(u);
            lw[v] = min(lw[v], lw[u]);
        }
    }
    if (lw[v] == idx[v]) {
        int x;
        do {
            x = q.top();
            q.pop();
            cmp[x] = qcmp;
        } while (x != v);
        verdad[qcmp] = (cmp[neg(v)] < 0);
        qcmp++;
    }
}

bool satisf() {  //O(n)
    fill(idx, idx + 2 * n, 0), qidx = 0;
    fill(cmp, cmp + 2 * n, -1), qcmp = 0;
    for (int i = 0; i < n; ++i) {
        if (!idx[i]) tjn(i);
        if (!idx[neg(i)]) tjn(neg(i));
    }
    for(int i = 0; i < n; ++i) 
        if (cmp[i] == cmp[neg(i)]) return false;
    return true;
}

bool possible(int m, vector<pair<pii,bool>>& e) {
    // Clear G
    for (int i = 0; i < 2*n; ++i) 
        G[i].clear();
    for (int i = 0; i <= m; ++i) {
        int u, v;
        tie(u, v) = e[i].first;
        if (e[i].second) {
            // Son iguales, debo mantenerlo iguales
            addor(u, neg(v));
            addor(neg(u), v);
        } else {
            // Son distintos, debo cambiar
            addor(u, v);
            addor(neg(u), neg(v));
        }
    }
    return satisf();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;
    n = 2 * q;

    vector<pair<pii, bool>> query(q);
    for (int i = 0; i < q; ++i) {
        lld r, c;
        int a, b;
        cin >> r >> c >> a >> b;
        int u = getRowNode(r);
        int v = getColumnNode(c);
        query[i] = {{u, v}, a == b};
    }

    // Busquemos la primera que no se cumpla
    int l = 0, r = q;
    while (l < r) {
        int med = (l + r) / 2;
        if (possible(med, query)) {
            l = med + 1;
        } else {
            r = med;
        }
    }

    for (int i = 0; i < l; ++i) {
        cout << "Yes\n";
    }
    for (int i = l; i < q; ++i) {
        cout << "No\n";
    }

    return 0;
}