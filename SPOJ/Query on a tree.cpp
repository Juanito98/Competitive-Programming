#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10002;

struct ura {
    int a, b, c;
};
ura edges[MAXN];

struct node {
    int v;
    node *l, *r;
};
typedef node* pnode;
pnode segmentTree;

int n;
vector < int > adj[MAXN];
int padre[MAXN], depth[MAXN], subsize[MAXN];
int chainNo, chainHead[MAXN], chainInd[MAXN], num[MAXN];
int costo[MAXN]; // costo de subir al padre

void build(pnode &tree, int ini, int fin) {
    if(!tree) tree = new node();
    if(ini == fin) {
        tree -> v = costo[ini];
    } else {
        int med = (ini + fin) / 2;
        build(tree -> l, ini, med);
        build(tree -> r, med + 1, fin);
        tree -> v = max(tree -> l -> v, tree -> r -> v);
    }
}

void update(pnode &tree, int ini, int fin, const int &pos, const int &v) {
    if(ini > pos || fin < pos) return;
    if(ini == fin) {
        tree -> v = costo[pos] = v;
    } else {
        int med = (ini + fin) / 2;
        update(tree -> l, ini, med, pos, v);
        update(tree -> r, med + 1, fin, pos, v);
        tree -> v = max(tree -> l -> v, tree -> r -> v);
    }
}

int query(pnode &tree, int ini, int fin, const int &i, const int &j) {
    if(ini > j || fin < i) return 0;
    if(ini >= i && fin <= j) return tree -> v;
    int med = (ini + fin) / 2;
    return max(query(tree -> l, ini, med, i, j), query(tree -> r, med + 1, fin, i, j));
}

void dfs(int nodo) {
    subsize[nodo] = 1;
    for(int a : adj[nodo]) {
        if(a == padre[nodo]) continue;
        padre[a] = nodo;
        depth[a] = depth[nodo] + 1;
        dfs(a);
        subsize[nodo] += subsize[a];
    }
}

int tope;
void HLD(int nodo) {
    if(!chainHead[chainNo]) chainHead[chainNo] = nodo;
    chainInd[nodo] = chainNo;
    num[nodo] = ++tope;

    int heavy = 0, size = 0;
    for(int a : adj[nodo]) {
        if(a == padre[nodo]) continue;
        if(subsize[a] > size) {
            heavy = a;
            size = subsize[a];
        }
    }
    if(heavy) HLD(heavy);

    for(int a : adj[nodo]) {
        if(a == padre[nodo] || a == heavy) continue;
        chainNo++;
        HLD(a);
    }
}

int LCA(int a, int b) {
    int chainA = chainInd[a], chainB = chainInd[b];
    while(chainA != chainB) {
        if(depth[chainHead[chainA]] > depth[chainHead[chainB]])
            a = padre[chainHead[chainA]];
        else
            b = padre[chainHead[chainB]];
        chainA = chainInd[a], chainB = chainInd[b];
    }
    return depth[a] < depth[b] ? a : b;
}

int query(int a, int lca) {
    int r = 0;
    int chainA = chainInd[a];
    while(chainA != chainInd[lca]) {
        r = max(r, query(segmentTree, 1, n, num[chainHead[chainA]], num[a]));
        a = padre[chainHead[chainA]];
        chainA = chainInd[a];
    }
    if(a != lca) r = max(r, query(segmentTree, 1, n, num[lca] + 1, num[a]));
    return r;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    for(cin >> t; t; t--) {
        cin >> n;
        for(int i = 1; i <= n; i++) adj[i].clear();
        for(int i = 1; i < n; i++) {
            cin >> edges[i].a >> edges[i].b >> edges[i].c;
            adj[edges[i].a].push_back(edges[i].b);
            adj[edges[i].b].push_back(edges[i].a);
        }
        fill(padre, padre + n + 1, 0);
        dfs(1);
        chainNo = tope = 0;
        fill(chainHead, chainHead + n + 1, 0);
        HLD(1);
        for(int i = 1; i < n; i++) {
            int v = depth[edges[i].a] > depth[edges[i].b] ? edges[i].a : edges[i].b;
            costo[num[v]] = edges[i].c;
        }
        build(segmentTree, 1, n);
        string s;
        for(cin >> s; s != "DONE"; cin >> s) {
            int x, y;
            cin >> x >> y;
            if(s == "CHANGE") {
                edges[x].c = y;
                x = depth[edges[x].a] > depth[edges[x].b] ? edges[x].a : edges[x].b;
                update(segmentTree, 1, n, num[x], y);
            } else {
                int l = LCA(x, y);
                cout << max(query(x, l), query(y, l)) << "\n";
            }
        }
    }
    return 0;
}
