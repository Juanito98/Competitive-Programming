/*
    2 SAT Problem
    Idea: Representar aristas como nodos
    https://codeforces.com/problemset/problem/27/D
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

const int MAX = 10002;
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
//remember to CLEAR G!!!
bool satisf() {  //O(n)
    fill(idx, idx + 2 * n, 0), qidx = 0;
    fill(cmp, cmp + 2 * n, -1), qcmp = 0;
    for(int i = 0; i < n; ++i) {
        if (!idx[i]) tjn(i);
        if (!idx[neg(i)]) tjn(neg(i));
    }
    for(int i = 0; i < n; ++i) if (cmp[i] == cmp[neg(i)]) return false;
    return true;
}

int getNodeDentro(int i, int j, int N) {
    if (i > j) swap(i, j);
    return i * N + j;
}

int getNodeFuera(int i, int j, int N) {
    if (i < j) swap(i, j);
    return i * N + j;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    n = N*N;

    vector<pii> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
        int u = edges[i].first, v = edges[i].second;
        int dUV = getNodeDentro(u, v, N);
        int fUV = getNodeFuera(u, v, N);
        addor(dUV, fUV); // Alguna arista tiene que estar
        for (int l = (u + 1) % N; l != v; l = (l + 1) % N) {
            for (int k = (v + 1) % N; k != u; k = (k + 1) % N) {
                int dLK = getNodeDentro(l, k, N);
                int fLK = getNodeFuera(l, k, N);
                addor(neg(dUV), neg(dLK)); // No pueden estar ambas
                addor(neg(fUV), neg(fLK));
            }
        } 
    }

    bool ans = satisf();
    if (!ans) {
        cout << "Impossible\n";
    } else {
        for (auto p : edges) {
            int nodo = getNodeDentro(p.first, p.second, N);
            cout << (verdad[cmp[nodo]] ? "i" : "o");
        }
        cout << endl;
    }

    return 0;
}