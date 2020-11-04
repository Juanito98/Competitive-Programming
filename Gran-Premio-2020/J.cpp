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

const int MAXN = 100002;

struct segment_tree {
    #define IZQ (nodo*2)
    #define DER (nodo*2+1)

    int lazy_transform[MAXN * 5];
    set<int> lazy_borra[MAXN * 5];

    void push_borra(int nodo, int v) {
        // Si ya están todos muertos, ignora
        if (lazy_transform[nodo] < 0) return; 
        // borra
        if (lazy_transform[nodo] == v) {
            // Se mueren todos
            lazy_borra[nodo].clear();
            lazy_transform[nodo] = -v; 
        } else {
            lazy_borra[nodo].insert(v);
        }
    }

    void push_transf(int nodo, int v) {
        // Si ya están todos muertos, ignora
        if (lazy_transform[nodo] < 0) return;

        lazy_transform[nodo] = v;
        if (v < 0) {
            lazy_borra[nodo].clear();
        }
    }

    void propagate(int nodo, int ini, int fin) {
        if (lazy_transform[nodo] < 0) {
            lazy_borra[nodo].clear();
        }
        if (ini == fin) {
            lazy_borra[nodo].clear();
        }
        for (auto v : lazy_borra[nodo]) {
            push_borra(IZQ, v);
            push_borra(DER, v);
        }
        lazy_borra[nodo].clear();
        if (lazy_transform[nodo] != 0) {
            push_transf(IZQ, lazy_transform[nodo]);
            push_transf(DER, lazy_transform[nodo]);
        }
        lazy_transform[nodo] = 0;
    }

    void update(int nodo, int ini, int fin, int i, int j, int v) {
        propagate(nodo, ini, fin);
        if (fin < i || ini > j) return;
        if (ini >= i && fin <= j) {
            if (v < 0) push_borra(nodo, -v);
            else push_transf(nodo, v);

            propagate(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, i, j, v);
            update(DER, med + 1, fin, i, j, v);
        }
    }

    int query(int nodo, int ini, int fin, int pos) {
        propagate(nodo, ini, fin);
        if (ini == fin) {
            return lazy_transform[nodo];
        } else {
            int med = (ini + fin) / 2;
            if (pos <= med)
                return query(IZQ, ini, med, pos);
            else
                return query(DER, med + 1, fin, pos);
        }
    }

} ST;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int q;
    for (cin >> q; q; --q) {
        char op;
        cin >> op;

        if (op == 'm') {
            int i, j, k;
            cin >> i >> j >> k;
            ST.update(1, 1, n, i, j, k);
        } else if (op == 'b') {
            int k;
            cin >> k;
            ST.update(1, 1, n, 1, n, -k);
        } else if (op == 'd') {
            int i;
            cin >> i;
            int v = ST.query(1, 1, n, i);
            if (v > 0) {
                cout << v << "\n";
            } else if (v < 0) {
                cout << "para que quieres saber eso\n";
            } else {
                cout << "si lo encuentro que te hago\n";
            }
        } else {
            int i, j;
            cin >> i >> j;
            int v1 = ST.query(1, 1, n, i);
            int v2 = ST.query(1, 1, n, j);
            if (v1 < 0) v1 = -1;
            if (v2 < 0) v2 = -1;
            cout << (v1 == v2 ? "si" : "no") << "\n";
        }

        /*for (int i = 1; i <= n; ++i) {
            cout << ST.query(1, 1, n, i) << " ";
        }
        cout << endl;*/
    }
    return 0;
}