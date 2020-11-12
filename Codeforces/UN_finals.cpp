/*
    Max Flow
    https://codeforces.com/gym/101845/problem/F
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

struct edge {
    int node, next, cap, flow;
};

const int MAXV = 130;
const int MAXE = MAXV * 30;
const int INF = 1e6;

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    const int A_LENGTH = 'Z' - 'A' + 1;

    n = N + A_LENGTH + 2;
    s = 0;
    t = N + A_LENGTH + 1;
    nextEdge = 2;

    for (int i = 1; i <= N; ++i) {
        addEdge(s, i, 1);
        vector<int> b(30);
        for (int j = 0; j < 3; ++j) {
            string careers;
            cin >> careers;
            for (char c : careers) {
                b[c-'A']++;
            }
        }
        int mayor = 0;
        for (auto f : b) {
            mayor = max(f, mayor);
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            if (b[c-'A'] == mayor) {
                addEdge(i, N + c - 'A' + 1, 1);
            }
        }
    }

    int k;
    cin >> k;
    for (char c = 'A'; c <= 'Z'; c++) {
        addEdge(N + c -'A' + 1, t, k);
    }

    cout << maxFlow() << "\n";

    return 0;
}