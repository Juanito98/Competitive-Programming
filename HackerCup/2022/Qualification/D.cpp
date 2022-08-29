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
typedef pair<int, lld> pii;

const int MAXN = 200002;
const int SQRT_N = 450;

int n, m, Q;
int sigIndex;
int degree[MAXN];
unordered_map<int, int> indexMap;
lld precalculo[2 * SQRT_N][MAXN];
unordered_map<int, lld> edges[MAXN];
vector<pii> adj[MAXN];

void clean() {
    sigIndex = 0;
    indexMap.clear();
    fill(degree, degree + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        edges[i].clear();
    }
}

int getIndex(int nodo) {
    if (indexMap.count(nodo)) {
        return indexMap[nodo];
    }
    // Precalculate response of this new index
    int idx = indexMap[nodo] = sigIndex++;
    fill(precalculo[idx], precalculo[idx] + n + 1, 0);
    for (auto e1 : adj[nodo]) {
        for (auto e2 : adj[e1.first]) {
            precalculo[idx][e2.first] += min(e1.second, e2.second);
        }
    }
    return idx;
}

lld calculateDistance1(int a, int b) {
    if (edges[a].count(b) == 0) return 0;
    return edges[a][b];
}

lld calculateDistance2(int A, int B) {
    if (degree[A] > degree[B]) {
        swap(A, B);
    }
    if (degree[A] > SQRT_N) {
        int idx = getIndex(A);
        return precalculo[idx][B];
    }
    // Calculate response manually
    lld ans = 0;
    for (auto e : adj[A]) {
        ans += min(e.second, calculateDistance1(e.first, B));
    }
    return ans;
}

lld F(int a, int b) {
    return 2ll * calculateDistance1(a, b) + calculateDistance2(a, b);
}

void join(int a, int b, lld c) {
    adj[a].push_back({b, c});
    degree[a]++;
    edges[a][b] = c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ":";
        cin >> n >> m >> Q;
        clean();
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            join(a, b, c);
            join(b, a, c);
        }
        for (int i = 0; i < Q; ++i) {
            int a, b;
            cin >> a >> b;
            cout << " " << F(a, b);
        }
        cout << "\n";
    }

    return 0;
}
