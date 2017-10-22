#include <iostream>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN
using namespace std;

int N;
int raiz = 1;
int newNodo = 1;
struct segment_tree {
    struct ura {
        int S;
        int mayor;
        int IZQ, DER;
    };
    ura tree[6000002];
    int lazy[6000002];

    bool tengoHijos(int nodo) { return tree[nodo].IZQ; }

    void propagate(int nodo, int ini, int fin) {
        if(lazy[nodo] != -1) {
            if(!tengoHijos(nodo)) {
                tree[nodo].IZQ = ++newNodo;
                tree[nodo].DER = ++newNodo;
            }
            tree[nodo].S = lazy[nodo] * (fin - ini + 1);
            tree[nodo].mayor = max(0, tree[nodo].S);
            lazy[tree[nodo].IZQ] = lazy[tree[nodo].DER] = lazy[nodo];
        }
        lazy[nodo] = -1;
    }

    void update(int &nodo, int ini, int fin, const int &i, const int &j, const int &v) {
        if(ini > j || fin < i) return;
        if(!nodo) nodo = ++newNodo;
        propagate(nodo, ini, fin);
        if(ini >= i && fin <= j) {
            lazy[nodo] = v;
            propagate(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update(tree[nodo].IZQ, ini, med, i, j, v);
            update(tree[nodo].DER, med + 1, fin, i, j, v);
            tree[nodo].mayor = max(tree[tree[nodo].IZQ].mayor, tree[tree[nodo].IZQ].S + tree[tree[nodo].DER].mayor);
            tree[nodo].S = tree[tree[nodo].IZQ].S + tree[tree[nodo].DER].S;
        }
    }
    void update(int i, int j, int v) { update(raiz, 0, N, i, j, v); }

    int query(const int nodo, int ini, int fin, int h) {
        propagate(nodo, ini, fin);
        if(tree[nodo].mayor <= h) return fin - ini + 1;
        if(ini == fin) return 0;
        int med = (ini + fin) / 2;
        if(tree[tree[nodo].IZQ].mayor > h) return query(tree[nodo].IZQ, ini, med, h);
        return med - ini + 1 + query(tree[nodo].DER, med + 1, fin, h - tree[tree[nodo].IZQ].S);
    }
    int query(int h) { return query(raiz, 0, N, h) - 1; }
};
segment_tree ST;

int main() {
    optimizar;
    cin >> N;
    char car = ' ';
    int a, b, c;
    for(cin >> car; car != 'E'; cin >> car) {
        if(car == 'Q') {
            cin >> a;
            cout << ST.query(a) << "\n";
        } else {
            cin >> a >> b >> c;
            ST.update(a, b, c);
        }
    }
    return 0;
}