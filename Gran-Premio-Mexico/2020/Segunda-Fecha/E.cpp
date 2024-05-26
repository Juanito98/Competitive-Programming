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

const int MAXN = 100002;
const int LOG_N = 20;

struct bit {
    int tree[MAXN * 4];

    void update(int p, int v) {
        for (; p < MAXN*4; p += p & (-p))
            tree[p] += v;
    }

    int query(int p) {
        int v = 0;
        for (; p; p -= p & (-p))
            v += tree[p];
        return v;
    }
} BIT;

int n, m;
vector<int> adj[MAXN];
int edad[MAXN];

int nextCnt = 1;
pii rango[MAXN];

int padre[LOG_N][MAXN];

void dfs(int nodo) {
    rango[nodo].first = nextCnt++;
    // Visita a sus hijos
    for (auto h : adj[nodo]) {
        padre[0][h] = nodo;
        dfs(h);
    }
    rango[nodo].second = nextCnt++;
}

void do_sparse() {
    for (int k = 1; k < LOG_N; ++k) {
        for (int nodo = 1; nodo <= n; ++nodo) {
            padre[k][nodo] = padre[k-1][padre[k-1][nodo]];
        }
    }
}

void inunda(int nodo) {
    //cout << "Inundando " << nodo << endl;
    BIT.update(rango[nodo].first, 1);
    BIT.update(rango[nodo].second, -1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        edad[i] = a;
        if (i > 1) 
            adj[b].push_back(i);
    }

    dfs(1);
    do_sparse();

    vector<pii> events; // (lower, nodo)

    for (int i = 0; i < m; ++i) {
        int nodo, a, b;
        cin >> nodo >> a >> b;
        // Sube o hasta b
        for (int k = LOG_N - 1; k >= 0; --k) {
            if (padre[k][nodo] == 0) continue;
            if (edad[padre[k][nodo]] <= b)
                nodo = padre[k][nodo];
        }
        //cout << "Ev " << nodo << " " << a << endl;
        events.push_back({a, nodo});
    }

    sort(events.begin(), events.end());

    int j = 0;
    pii arr[n+1];
    for (int i = 1; i <= n; ++i) 
        arr[i] = {edad[i], i};
    sort(arr+1, arr +n + 1);

    int ans[n+1];
    for (int i = 1; i <= n; ++i) {
        int nodo = arr[i].second;
        while (j < events.size() && events[j].first <= edad[nodo]) {
            inunda(events[j].second);
            j++;
        }
        ans[nodo] = BIT.query(rango[nodo].first);
        //cout << "Answering nodo " << nodo << " " << ans[nodo] << endl;
    }

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    cout << "\n";

    return 0;
}