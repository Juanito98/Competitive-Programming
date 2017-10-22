#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
#define lld long long int
using namespace std;

int n;

int trees[MAXN];
int hijo[MAXN];
int hermano[MAXN];
lld costo[MAXN][MAXN];
lld cost_root[MAXN];

lld memo[MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN];

int padre[MAXN];

lld suma(int nodo) {
    if(!nodo) return 0;
    if(cost_root[nodo]) return cost_root[nodo];
    return cost_root[nodo] = suma(padre[nodo]) + costo[nodo][padre[nodo]];
}

lld cost(int a, int P) {
    return trees[a] * (suma(a) - suma(P));
}

lld DP(int act, int P, int k) {
    if(!vis[act][P][k]) {
        vis[act][P][k] = true;
        lld c = 0;
        if(!k) {
            c = cost(act, P);
            if(hijo[act]) c+= DP(hijo[act], P, k);
            if(hermano[act]) c+= DP(hermano[act], P, k);
            return memo[act][P][k] = c;
        }

        c = INFINITY;
        if(hermano[act] && hijo[act]) {
            for(int i=0; i <= k; i++)
                c = min(c, DP(hijo[act], P, i) + DP(hermano[act], P, k - i) + cost(act, P));
            for(int i=0; i < k; i++)
                c = min(c, DP(hijo[act], act, i) + DP(hermano[act], P, k - i - 1));
        } else {
            if(hermano[act]) {
                c = min(c, DP(hermano[act], P, k)) + cost(act, P);
                c = min(c, DP(hermano[act], P, k - 1));
            } else {
                if(hijo[act]) {
                    c = min(c, DP(hijo[act], P, k)) + cost(act, P);
                    c = min(c, DP(hijo[act], act, k - 1));
                } else {
                    c = 0;
                }
            }
        }
        memo[act][P][k] = c;

    }
    return memo[act][P][k];
}

int main()
{
    optimizar;
    int k;
    cin >> n >> k;
    int p;
    for(int i=1; i<=n; i++) {
        cin >> trees[i];
        cin >> p;
        cin >> costo[i][p];
        padre[i] = p;
        costo[p][i] = costo[i][p];
        if(hijo[p])
            hermano[i] = hijo[p];
        hijo[p] = i;
    }
    cout << DP(hijo[0], 0, k);
    return 0;
}
