#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 150002
#define lld long long int
using namespace std;

int n, m, P;
pair < int, int > aristas[MAXN];

void une(int a, int b) {
    if(aristas[a].first) {
        if(!aristas[a].second) aristas[a].second = b;
    } else aristas[a].first = b;
}

int memo[MAXN][2][2];

/*
si f = 0 entonces NO vengo de first
si f = 1 entonces vengo de first
si quiero llegar a P viniendo de su first cual = 1
si quiero llegar a P viniendo de su second cual = 0
*/
int _auxNodo, _auxF;
int DP(int nodo, int f, const int & cual) {
    if(nodo == P && cual == f) return 0;
    if(!memo[nodo][f][cual]) {
        memo[nodo][f][cual] = (1 << 30);
        _auxNodo = f ? aristas[nodo].second : aristas[nodo].first;
        _auxF = aristas[_auxNodo].first == nodo ? 1 : 0;
        memo[nodo][f][cual] = DP(_auxNodo, _auxF, cual) + 1;
    }
    return memo[nodo][f][cual];
}

int llegada[MAXN]; // llegar del nodo a P, - es que llegue de su first
int primero[MAXN]; //viaje despues
int segundo[MAXN];

int solve(int X) {
    int r = 0;
    int x;
    
    for(int i = 1; i <= n; i++) {
        x = X;
        if(abs(llegada[i]) > x) continue;
        x-= abs(llegada[i]);
        if(!x) { r++; continue; }
        if((llegada[i] < 0 && primero[i] < 0) || (llegada[i] >= 0 && primero[i] >= 0)) {
            x%= abs(primero[i]);
            r+= x ? 0 : 1;
        } else {
            if(x < primero[i]) continue;
            if((primero[i] < 0 && segundo[i] < 0) || (primero[i] >= 0 && segundo[i] >= 0)) {
                x-= abs(primero[i]);
                x%= abs(segundo[i]);
                r+= x ? 0 : 1;
            } else {
                x%= abs(primero[i]) + abs(segundo[i]);
                if(!x) { r++; continue; }
                if(x == abs(primero[i])) r++;
            }
        }
    }
    return r;
}

int main() {
    optimizar;
    cin >> n >> m >> P;
    P++;
    int a, b;
    for(int i = 1; i <= m; i++) {
        cin >> a >> b;
        a++, b++;
        une(a, b);
        une(b, a);
    }

    for(int i = 1; i <= n; i++)
        if(!aristas[i].second) aristas[i].second = aristas[i].first;

    int k;
    cin >> k;

    int auxNodo, auxF;
    for(int i = 1; i <= n; i++) {
        llegada[i] = DP(i, 0, 1) < DP(i, 0, 0) ? -DP(i, 0, 1) : DP(i, 0, 0);
        auxNodo = llegada[i] < 0 ? aristas[P].second : aristas[P].first;
        auxF = aristas[auxNodo].first == P ? 1 : 0;
        primero[i] = DP(auxNodo, auxF, 1) < DP(auxNodo, auxF, 0) ? -(DP(auxNodo, auxF, 1) + 1) : DP(auxNodo, auxF, 0) + 1;
        auxNodo = primero[i] < 0 ? aristas[P].second : aristas[P].first;
        auxF = aristas[auxNodo].first == P ? 1 : 0;
        segundo[i] = DP(auxNodo, auxF, 1) < DP(auxNodo, auxF, 0) ? -(DP(auxNodo, auxF, 1) + 1) : DP(auxNodo, auxF, 0) + 1;
    }

    for(int i = 1; i <= k; i++) {
        cin >> a;
        cout << solve(a) << " ";
    }
    cout << "\n";

    return 0;
}