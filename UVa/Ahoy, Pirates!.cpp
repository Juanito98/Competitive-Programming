#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1300002
#define INF (1 << 30)
#define izq (nodo * 2)
#define der (nodo * 2) + 1
using namespace std;

string arr;

struct segment_tree {
    int tree[MAXN*4];
    int lazy[MAXN*4];
    int invierte[MAXN*4];
    int size;

    void init(int s) {
        size = s;
        construye(1, 0, size-1);
    }

    void propagate_cambia(int nodo, int ini, int fin) {
        if(ini != fin) {
            lazy[izq] = lazy[der] = lazy[nodo];
            invierte[izq] = invierte[der] = 0;
        }
        lazy[nodo] = -1;
    }

    void propagate_swap(int nodo, int ini, int fin) {
        if(ini != fin) {
            if(lazy[izq] != -1) {
                lazy[izq]^=1;
            } else {
                invierte[izq]^= 1;
            }
            if(lazy[der] != -1) {
                lazy[der]^=1;
            } else {
                invierte[der]^= 1;
            }
        }
        invierte[nodo] = 0;
    }

    void construye(int nodo, int ini, int fin) {
        lazy[nodo] = -1;
        invierte[nodo] = 0;
        if(ini == fin) {
            tree[nodo] = arr[ini] - '0';
        } else {
            int med = (ini + fin) / 2;
            construye(izq, ini, med);
            construye(der, med+1, fin);
            tree[nodo] = tree[izq] + tree[der];
        }
    }

    void propaga(int nodo, int ini, int fin) {
        if(lazy[nodo] != -1) {
            tree[nodo] = (fin - ini + 1) * lazy[nodo];
            propagate_cambia(nodo, ini, fin);
        }
        if(invierte[nodo]) {
            tree[nodo] = (fin - ini + 1) - tree[nodo];
            propagate_swap(nodo, ini, fin);
        }
    }

    void update_cambio(int nodo, int ini, int fin, int i, int j, int v) {
        propaga(nodo, ini, fin);
        if(ini > j || fin < i) return;

        if(ini >= i && fin <= j) {
            lazy[nodo] = v;
            tree[nodo] = (fin - ini + 1) * v;
            propagate_cambia(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update_cambio(izq, ini, med, i, j, v);
            update_cambio(der, med+1, fin, i, j, v);
            tree[nodo] = tree[izq] + tree[der];
        }
    }

    void update_swap(int nodo, int ini, int fin, int i, int j) {
        propaga(nodo, ini, fin);
        if(ini > j || fin < i) return;

        if(ini >= i && fin <= j) {
            invierte[nodo]^= 1;
            tree[nodo] = (fin - ini + 1) - tree[nodo];
            propagate_swap(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update_swap(izq, ini, med, i, j);
            update_swap(der, med+1, fin, i, j);
            tree[nodo] = tree[izq] + tree[der];
        }
    }

    int query(int nodo, int ini, int fin, int i, int j) {
        if(ini > j || fin < i) return 0;
        propaga(nodo, ini, fin);
        if(ini >= i && fin <= j)
            return tree[nodo];
        int med = (ini + fin) / 2;
        return query(izq, ini, med, i, j) + query(der, med+1, fin, i, j);
    }

};

segment_tree ST;

int main()
{
    optimizar;
    int T;
    cin >> T;
    int m, cuantas;
    string p;
    int Q;
    char aux;
    int a, b;
    int cont;
    for(int cases = 1; cases <= T; cases++) {
        cout << "Case " << cases << ":\n";
        cin >> m;
        for(int i=1; i <= m; i++) {
            cin >> cuantas;
            cin >> p;
            for(int j=1; j<=cuantas; j++)
                arr+= p;
        }
        ST.init(arr.size());

        cin >> Q;
        cont = 0;
        for(int i=1; i<=Q; i++) {
            cin >> aux >> a >> b;
            if(aux == 'F')
                ST.update_cambio(1, 0, ST.size-1, a, b, 1);
            if(aux == 'E')
                ST.update_cambio(1, 0, ST.size-1, a, b, 0);
            if(aux == 'I')
                ST.update_swap(1, 0, ST.size-1, a, b);
            if(aux == 'S')
                cout << "Q" << ++cont << ": " << ST.query(1, 0, ST.size-1, a, b) << "\n";
        }

        arr.clear();
    }
    return 0;
}
