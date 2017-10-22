#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50002;
const int LOG_N = 18;

int n, m;
vector < int > adj[MAXN];
int padre[MAXN][LOG_N], depth[MAXN];
int sol[MAXN];

void dfs(int v = 1) {
    depth[v] = depth[padre[v][0]] + 1;
    for(int i = 1; i < LOG_N; i++)
        padre[v][i] = padre[padre[v][i - 1]][i - 1];

    for(int u : adj[v]) {
        if(u == padre[v][0]) continue;
        padre[u][0] = v;
        dfs(u);
    }
}

void jump(int &v, int k) {
    for(int i = 0; i < LOG_N; i++)
        if(k & (1 << i)) v = padre[v][i];
}

int lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    jump(u, depth[u] - depth[v]);
    if(u == v) return u;
    for(int i = LOG_N - 1; i >= 0; i--) {
        if(padre[u][i] != padre[v][i]) {
            u = padre[u][i];
            v = padre[v][i];
        }
    }
    return padre[u][0];
}

void update(int u, int v) {
    int l = lca(u, v);
    sol[u]++;
    sol[v]++;
    sol[l]--;
    sol[padre[l][0]]--;
}

void solve(int v = 1) {
    for(int u : adj[v]) {
        if(u == padre[v][0]) continue;
        solve(u);
        sol[v] += sol[u];
    }
}

int main()
{
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs();
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        update(u, v);
    }
    solve();
    int r = 0;
    for(int i = 1; i <= n; i++) r = max(r, sol[i]);
    cout << r << "\n";
    return 0;
}
