/*
    2SAT Problem
    https://codeforces.com/problemset/problem/228/E
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

const int MAX = 102;
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
    for (int i = 0; i < n; ++i) {
        if (!idx[i]) tjn(i);
        if (!idx[neg(i)]) tjn(neg(i));
    }
    for (int i = 0; i < n; ++i)
        if (cmp[i] == cmp[neg(i)]) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, state;
        cin >> u >> v >> state;
        u--;
        v--;
        if (state == 0) {
            addor(u, v);
            addor(neg(u), neg(v));
        } else {
            addor(neg(u), v);
            addor(u, neg(v));
        }
    }

    bool ans = satisf();

    if (ans) {
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            if (verdad[cmp[i]])
                arr.push_back(i+1);
        }
        cout << arr.size() << "\n";
        for (int nodo : arr) {
            cout << nodo << " ";
        }
        cout << "\n";
    } else {
        cout << "Impossible\n";
    }

    return 0;
}