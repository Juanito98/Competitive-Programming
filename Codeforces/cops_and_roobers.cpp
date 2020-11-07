/*
Max flow
Problema E - https://codeforces.com/gym/101982/my
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

const int MAX_SZ = 32;

const int MAXV = MAX_SZ * MAX_SZ * 2;
const int MAXE = MAXV * 5;
const lld INF = 1e9;

struct edge {
    lld node, next, cap, flow;
};

edge g[MAXE * 2];
int start[MAXV], nextEdge;  // init start to 0s and nextEdge to 2

void addEdge(int a, int b, int c) {
    g[nextEdge] = {b, start[a], c, 0};
    start[a] = nextEdge++;
    g[nextEdge] = {a, start[b], 0, 0};
    start[b] = nextEdge++;
}

// s->source, t->sink, n->total no. nodes
int n, s, t;
lld maxFlow() {
    lld tot = 0;
    static lld q[MAXV], z[MAXV], d[MAXV], p[MAXV], qs, qe, curr;

    while (true) {
        fill(d, d + n, MAXV);
        d[s] = qs = qe = 0;
        q[qe++] = s;

        while (qs < qe) {
            curr = q[qs++];
            z[curr] = start[curr];
            if (d[curr] == d[t]) continue;
            for (int i = start[curr]; i; i = g[i].next)
                if (g[i].cap - g[i].flow > 0 &&
                    d[g[i].node] > d[curr] + 1) {
                    d[g[i].node] = d[curr] + 1;
                    q[qe++] = g[i].node;
                }
        }

        if (d[t] == MAXV) return tot;

        curr = s;
        while (true) {
            while (z[curr] && (g[z[curr]].cap - g[z[curr]].flow <= 0 ||
                               d[g[z[curr]].node] != d[curr] + 1))
                z[curr] = g[z[curr]].next;

            if (!z[curr]) {
                if (curr == s) break;
                curr = g[p[d[curr] - 1] ^ 1].node;
                d[g[p[d[curr]]].node] = -INF;
                continue;
            }

            p[d[curr]] = z[curr];
            curr = g[z[curr]].node;

            if (curr == t) {
                lld m = INF;
                for (int i = 0; i < d[t]; i++)
                    m = min(m, g[p[i]].cap - g[p[i]].flow);
                for (int i = 0; i < d[t]; i++) {
                    g[p[i]].flow += m;
                    g[p[i] ^ 1].flow -= m;
                }
                tot += m;
                curr = s;
            }
        }
    }
}

int R, C, k;
int getNode(int i, int j, bool esEntrada) {
    if (esEntrada) return i * C + j;
    return R * C + i * C + j;
}

int getNodeE(int i, int j) { return getNode(i, j, true); }
int getNodeS(int i, int j) { return getNode(i, j, false); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C >> k;
    swap(R, C);
    char matriz[R][C];
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            cin >> matriz[i][j];

    int costo_car[k];
    for (int i = 0; i < k; ++i)
        cin >> costo_car[i];

    nextEdge = 2;
    n = R * C * 2 + 1;
    t = R * C * 2;

    const int movs[4][2] = {
        -1, 0,
        1, 0,
        0, -1,
        0, 1};
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            char c = matriz[i][j];
            if (c == 'B')
                s = getNodeS(i, j);
            int costo = (c >= 'a' && c <= 'z' ? costo_car[c - 'a'] : INF);
            addEdge(getNodeE(i, j), getNodeS(i, j), costo);
            for (int l = 0; l < 4; ++l) {
                int new_i = i + movs[l][0], new_j = j + movs[l][1];
                if (new_i < 0 || new_j < 0 || new_i >= R || new_j >= C)
                    addEdge(getNodeS(i, j), t, INF);
                else
                    addEdge(getNodeS(i, j), getNodeE(new_i, new_j), INF);
            }
        }
    }

    lld maxF = maxFlow();
    cout << (maxF >= INF ? -1 : maxF) << "\n";

    return 0;
}