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
typedef pair<int, int> pii;

const int MAXN = 200002;

int n, m, Q;
vector<pair<int, pii> > e;
vector<pair<pii, pii> > q; // {{A, id}, {u, v}}
int ans[MAXN];

int cmp[MAXN];

int raiz(int nodo) {
    if (!cmp[nodo]) return nodo;
    return cmp[nodo] = raiz(cmp[nodo]);
}

void join(int a, int b) {
    if (raiz(a) == raiz(b)) return;
    cmp[raiz(a)] = raiz(b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> Q;

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        e.push_back({c, {a, b}});
    }

    for (int i = 0; i < Q; ++i) {
        int u, v, A;
        cin >> u >> v >> A;
        q.push_back({{A, i}, {u, v}});
    }

    sort(e.begin(), e.end());
    sort(q.begin(), q.end());

    int j = 0;
    for (int i = 0; i < Q; ++i) {
        int u, v, A, idx;
        tie(A, idx) = q[i].first;
        tie(u, v) = q[i].second;

        while (j < e.size() && e[j].first <= A) {
            // Agregamos la arista j
            join(e[j].second.first, e[j].second.second);
            j++;
        }
        ans[idx] = raiz(u) == raiz(v);
    }

    for (int i = 0; i < Q; ++i)
        cout << ans[i] << "\n";

    return 0;
}