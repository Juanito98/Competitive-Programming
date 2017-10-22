#include <bits/stdc++.h>
#define lld long long int
#define IZQ (nodo * 2)
#define DER (nodo * 2 + 1)
using namespace std;
const int MAXN = 200002;
const lld INF = (1ll << 60);

int n;
int arr[MAXN];

struct segment_tree {
    lld mini[MAXN * 5];
    lld suma[MAXN * 5];
    lld lazy[MAXN * 5];

    void propagate(int nodo, int ini, int fin) {
        if(lazy[nodo]) {
            suma[nodo] += lazy[nodo] * (lld) (fin - ini + 1);
            mini[nodo] += lazy[nodo];
            if(ini != fin) {
                lazy[IZQ] += lazy[nodo];
                lazy[DER] += lazy[nodo];
            }
            lazy[nodo] = 0;
        }
    }

    void construye(int nodo = 1, int ini = 1, int fin = n) {
        if(ini == fin) {
            suma[nodo] = mini[nodo] = arr[ini];
        } else {
            int med = (ini + fin) / 2;
            construye(IZQ, ini, med);
            construye(DER, med + 1, fin);
            suma[nodo] = suma[IZQ] + suma[DER];
            mini[nodo] = min(mini[IZQ], mini[DER]);
        }
    }

    void update(int nodo, int ini, int fin, int i, int j, int v) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return;
        if(ini >= i && fin <= j) {
            lazy[nodo] += v;
            propagate(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, i, j, v);
            update(DER, med + 1, fin, i, j, v);
            suma[nodo] = suma[IZQ] + suma[DER];
            mini[nodo] = min(mini[IZQ], mini[DER]);
        }
    }
    void update(int i, int j, int c) { update(1, 1, n, i, j, c); }

    lld menor(int nodo, int ini, int fin, int i, int j) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return INF;
        if(ini >= i && fin <= j) return mini[nodo];
        int med = (ini + fin) / 2;
        return min(menor(IZQ, ini, med, i, j), menor(DER, med + 1, fin, i, j));
    }
    lld menor(int i, int j) { return menor(1, 1, n, i, j); }

    lld sumQuery(int nodo, int ini, int fin, int i, int j) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return 0;
        if(ini >= i && fin <= j) return suma[nodo];
        int med = (ini + fin) / 2;
        return sumQuery(IZQ, ini, med, i, j) + sumQuery(DER, med + 1, fin, i, j);
    }
    lld sumQuery(int i, int j) { return sumQuery(1, 1, n, i, j); }

};
segment_tree ST;

int main()
{
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) 
        cin >> arr[i];
    ST.construye();
    for(int i = 1; i <= q; i++) {
        char car;
        int a, b, c;
        cin >> car;
        cin >> a >> b;
        if(car == 'M') {
            cout << ST.menor(a, b) << "\n";
        } else if(car == 'S') {
            cout << ST.sumQuery(a, b) << "\n";
        } else {
            cin >> c;
            ST.update(a, b, c);
        }
    }
    return 0;
}