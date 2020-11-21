/*
    Regional Latinoamerica 2019
    Segment tree + sparse table
    La idea de ST esta cool. Necesitas hacer query(l, r, x, y)
    regresar el menor indice j tal que s[j] este fuera del rango [x, y]
    https://www.urionlinejudge.com.br/judge/es/problems/view/3014
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

const int MAX = 100002;
const int LOG_N = 20;

int n, L, U;
int arr[MAX];
lld sum[MAX];

pii sigL[MAX], sigU[MAX];
pii sig[LOG_N][2][MAX];

struct segment_tree {
    #define IZQ (nodo << 1)
    #define DER ((nodo << 1) + 1) 
    pair<lld, lld> tree[MAX * 5]; // Guarda el minimo y el maximo indice

    void build(int nodo = 1, int ini = 1, int fin = n) {
        if (ini == fin) {
            tree[nodo] = {sum[ini], sum[ini]};
        } else {
            int med = (ini + fin) / 2;
            build(IZQ, ini, med);
            build(DER, med+1, fin);
            tree[nodo] = {
                min(tree[IZQ].first, tree[DER].first),
                max(tree[IZQ].second, tree[DER].second)
            };
        }
    }

    // Regresa el indice
    int query(int nodo, int ini, int fin, int i, int j, lld x, lld y) {
        if (ini > j || fin < i) return -1;
        if (tree[nodo].first >= x && tree[nodo].second <= y) return -1;
        if (ini == fin) {
            return ini;
        } else {
            int med = (ini + fin) / 2;
            int l = query(IZQ, ini, med, i, j, x, y);
            if (l != -1) return l;
            return query(DER, med+1, fin, i, j, x, y);
        }
    }
    pii query(int i, int j, lld x, lld y) {
        int idx = query(1, 1, n, i, j, x, y);
        if (idx == -1) return {0, n+1};
        if (sum[idx] < x) return {0, idx};
        return {1, idx};
    }

} ST;

void init() {
    ST.build();
    sig[0][0][n+1] = sig[0][1][n+1] = {0, n+1};
    for (int i = 1; i <= n; ++i) {
        // Si empezamos en L, cual es la siguiente pared que tocamos?
        sig[0][0][i] = ST.query(i+1, n, sum[i], U-L+sum[i]);
        // Si empezamos en U, cual es la siguiente pared que tocamos?
        sig[0][1][i] = ST.query(i+1, n, L-U+sum[i], sum[i]);
    }

    // sparse
    for (int k = 1; k < LOG_N; ++k) {
        sig[k][0][n + 1] = sig[k][1][n + 1] = {0, n + 1};
        for (int i = 1; i <= n; ++i) {
            pii pot = sig[k-1][0][i];
            sig[k][0][i] = sig[k-1][pot.first][pot.second];
            pot = sig[k-1][1][i];
            sig[k][1][i] = sig[k-1][pot.first][pot.second];
        }
    }
}

lld cut(lld B) {
    if (B <= L) return L;
    else if (B >= U) return U;
    return B;
}

lld f(int i, int j, lld X) {
    X = cut(X + arr[i]);
    // Busquemos el primero donde pega
    pii p = ST.query(i+1, j, L-X+sum[i], U-X+sum[i]);
    if (p.second <= j) {
        // Avancemos mientras podamos
        for (int k = LOG_N-1; k >= 0; --k)
            if (sig[k][p.first][p.second].second <= j)
                p = sig[k][p.first][p.second];
        X = (p.first == 0 ? L : U);
        i = p.second;
    }
    // Ya no tocará con pared
    return X + sum[j] - sum[i];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> L >> U;
    for (int i = 1; i <= n; ++i) {
       cin >> arr[i];
       sum[i] = sum[i-1] + arr[i];
    }

    init();

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, X;
        cin >> a >> b >> X;
        cout << f(a, b, X) << "\n";
    }

    return 0;
}