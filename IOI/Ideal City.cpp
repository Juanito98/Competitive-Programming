#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 100002
using namespace std;
const int MOD = 1e9;

int n;

int v[MAXN]; // cuantas celdas tiene el nodo i
vector < int > lista[MAXN];
int degree[MAXN];
int sigNodo;

pair < int, int > puntos[MAXN];

void construye() {
    queue < pair < pair < int, int >, int > > ant[2]; // Pto, #nodo
    int act = 0, sig = 1;
    int j, k;
    int ini, fin;
    for(int i = 0; i < n; i = j + 1) {
        swap(act, sig);
        while(!ant[sig].empty()) ant[sig].pop();
        for(j = i; puntos[j + 1].first == puntos[i].first; j++);
        ini = i, fin = i;
        for(k = i; k <= j; k++) {
            ini = k;
            while(puntos[k].second + 1 == puntos[k + 1].second) k++;
            fin = k;
            v[++sigNodo] = fin - ini + 1;
            ant[sig].push(make_pair(make_pair(puntos[ini].second, puntos[fin].second), sigNodo));
            while(!ant[act].empty()) {
                if(ant[act].front().first.second < puntos[ini].second) {
                    ant[act].pop();
                } else {
                    if(ant[act].front().first.first <= puntos[fin].second) {
                        lista[sigNodo].push_back(ant[act].front().second);
                        lista[ant[act].front().second].push_back(sigNodo);
                        degree[sigNodo]++;
                        degree[ant[act].front().second]++;
                    }
                    if(puntos[fin].second < ant[act].front().first.second) break;
                    ant[act].pop();
                }
            }
        }
    }
}

int solve() {
    queue < int > cola;
    for(int i = 0; i < n; i++)
        if(degree[i] == 1) cola.push(i);

    lld S = 0;
    int nodo;
    while(!cola.empty()) {
        nodo = cola.front();
        cola.pop();
        if(degree[nodo] != 1) continue;
        S += (lld) (v[nodo] * 1ll * (n - v[nodo]) * 1ll);
        S %= (MOD * 1ll);
        for(int i = 0; i < lista[nodo].size(); i++) {
            if(--degree[lista[nodo][i]] == 1)
                cola.push(lista[nodo][i]);
            v[lista[nodo][i]] += v[nodo];
        }
    }
    return S;
}

int DistanceSum(int N, int *X, int *Y) {
    n = N;
    sigNodo = 0;
    for(int i = 0; i < n; i++) {
        lista[i].clear();
        puntos[i] = make_pair(X[i], Y[i]);
    }
    sort(puntos, puntos + n);
    construye();
    int Sol = solve();

    sigNodo = 0;
    for(int i = 0; i < n; i++) {
        lista[i].clear();
        puntos[i] = make_pair(Y[i], X[i]);
        degree[i] = 0;
    }
    sort(puntos, puntos + n);
    construye();
    Sol += solve();
    Sol %= MOD;
    return Sol;
}

int main()
{
    optimizar;
    int n;
    cin >> n;
    int *coor_x, *coor_y;
    coor_x = new int[n];
    coor_y = new int[n];
    for(int i = 0; i < n; i++)
        cin >> coor_x[i] >> coor_y[i];
    cout << DistanceSum(n, coor_x, coor_y) << "\n";
    return 0;
}
