/*
    2 SAT Problem
    https://www.urionlinejudge.com.br/judge/es/problems/view/1348
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
#define addor(a, b) (G[neg(a)].push_back(b), G[neg(b)].push_back(a))
vector<int> G[MAX * 2];

int lw[MAX * 2], idx[MAX * 2], qidx;
stack<int> q;
int qcmp, cmp[MAX * 2];

bool verdad[MAX * 2 + 1];

int n;
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

bool satisf() {
    fill(idx, idx + 2*n, 0), qidx = 0;
    fill(cmp, cmp + 2*n, -1), qcmp = 0;
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
    cin >> m >> n;
    while (m != 0 || n != 0) {
        // Clear G
        for (int i = 0; i < 2*n; ++i) 
            G[i].clear();

        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (a == 0) a = b;
            if (b == 0) b = a;
            if (a != 0 && b != 0)
                addor(a - 1, b - 1);
            cin >> a >> b;
            if (a == 0) a = b;
            if (b == 0) b = a;
            if (a != 0 && b != 0)
                addor(neg(a - 1), neg(b - 1));
        }

        bool ans = satisf();
        cout << (ans ? "yes" : "no") << "\n";

        cin >> m >> n;
    }

    return 0;
}