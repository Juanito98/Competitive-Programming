#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
using namespace std;
const int MAXN = 100002;
const int LOG_N = 20;

int n, Q, root;
vector < int > adj[MAXN];
int depth[MAXN], padre[MAXN][LOG_N];
set < int > libre;
int id[MAXN], realNum[MAXN];

int cont;
void dfs(int v) {
    depth[v] = depth[padre[v][0]] + 1;
    for(int i = 1; i < LOG_N; i++) 
        padre[v][i] = padre[padre[v][i - 1]][i - 1];

    for(int i = 0; i < adj[v].size(); i++) dfs(adj[v][i]);
    id[v] = ++cont;
    realNum[cont] = v;
}

int erase(int v) {
    int u = v;
    for(int i = LOG_N - 1; i >= 0; i--) {
        if(!libre.count(id[padre[u][i]]) && padre[u][i])
            u = padre[u][i];
    }
    libre.insert(id[u]);
    return depth[v] - depth[u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> Q;
    for(int i = 1; i <= n; i++) {
        libre.insert(i);
        int p;
        cin >> p;
        if(!p) root = i;
        else {
            padre[i][0] = p;
            adj[p].push_back(i);
        }
    }
    for(int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());
    dfs(root);

    int last = 0;
    for(int i = 1; i <= Q; i++) {
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            for(int j = 1; j <= b; j++) {
                set < int > :: iterator it = libre.begin();
                last = realNum[*it];
                cout << "add to " << last << "\n";
                libre.erase(*it);
            }
            cout << last << "\n";
        } else {
            cout << erase(b) << "\n";
        }
    }
    return 0;
}