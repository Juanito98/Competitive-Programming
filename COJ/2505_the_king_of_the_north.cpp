/*
https://coj.uci.cu/24h/problem.xhtml?pid=2505
OJO: NO LO PUDE ENVIAR
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

const int MAXN = 302;
const lld INF = 1e7;

struct edge {
    int node, next, cap, flow;
};

const int MAXV = MAXN*MAXN*2;
const int MAXE = MAXV*5;

edge g[MAXE * 2];
int start[MAXV], nextEdge;  // init start to 0s and nextEdge to 2

void addEdge(int a, int b, int c) {
    g[nextEdge] = {b, start[a], c, 0};
    start[a] = nextEdge++;
    g[nextEdge] = {a, start[b], 0, 0};
    start[b] = nextEdge++;
}

int n, s, t;
// s->source, t->sink, n->total no. nodes
int maxFlow() {
    int tot = 0;
    static int q[MAXV], z[MAXV], d[MAXV], p[MAXV], qs, qe, curr;

    while (true) {
        fill(d, d + n, MAXV);
        d[s] = qs = qe = 0;
        q[qe++] = s;

        static int it = 1;

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

        it ++;

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
                int m = INF;
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

int r, c;
int getNodo(int i, int j, bool entrada) {
    if (entrada) return i * c + j;
    return r * c + i * c + j;
}
int getNodoE(int i, int j) {
    return getNodo(i, j, true);
}
int getNodoS(int i, int j) {
    return getNodo(i, j, false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;

    n = r * c * 2 + 1;
    t = r * c * 2;
    nextEdge = 2;

    const int MAX_COSTO = 1000000;

    int arr[r][c];

    const int movs[4][2] = {
        -1, 0,
        1, 0,
        0, 1,
        0, -1
    };
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> arr[i][j];
            addEdge(getNodoE(i, j), getNodoS(i, j), arr[i][j]);
            for (int k = 0; k < 4; ++k) {
                int newI = i + movs[k][0], newJ = j + movs[k][1];
                if (newI < 0 || newJ < 0 || newI >= r || newJ >= c) {
                    addEdge(getNodoS(i, j), t, MAX_COSTO);
                } else {
                    addEdge(getNodoS(i, j), getNodoE(newI, newJ), MAX_COSTO);
                }
            }
        }
    }

    int x, y;
    cin >> x >> y;
    x--;
    y--;
    s = getNodoS(x, y);

    cout << maxFlow() << "\n";

    return 0;
}