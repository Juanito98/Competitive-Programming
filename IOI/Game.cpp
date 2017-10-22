#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define IZQ tree[nodo].izq
#define DER tree[nodo].der
#define IZQ_ arbol[nodo].first
#define DER_ arbol[nodo].second
using namespace std;

int n, m;
int raiz = 1;

lld gcd2(lld X, lld Y) {
    lld tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

struct ura {
    lld GCD;
    int der, izq;
};

ura tree[10000000];
int sigNodo = 700000;

void update(int &nodo, int ini, int fin, const int &pos, const lld &v) {
    if(ini > pos || fin < pos) return;
    if(!nodo) nodo = ++sigNodo;
    if(ini == fin) {
        tree[nodo].GCD = v;
    } else {
        int med = (ini + fin) / 2;
        update(IZQ, ini, med, pos, v);
        update(DER, med + 1, fin, pos, v);
        tree[nodo].GCD = gcd2(tree[IZQ].GCD, tree[DER].GCD);
    }
}

lld query(int &nodo, int ini, int fin, const int &i, const int &j) {
    if(ini > j || fin < i) return 0;
    if(!nodo) return 0;
    if(ini >= i && fin <= j) {
        return tree[nodo].GCD;
    } else {
        int med = (ini + fin) / 2;
        return gcd2(query(IZQ, ini, med, i, j), query(DER, med + 1, fin, i, j));
    }
}

void merge(int &nodo, int &nodo_I, int &nodo_D, int ini, int fin, const int &pos) {
    if(ini > pos || fin < pos) return;
    if(!nodo) nodo = ++sigNodo;
    if(ini != fin) {
        int med = (ini + fin) / 2;
        merge(IZQ, tree[nodo_I].izq, tree[nodo_D].izq, ini, med, pos);
        merge(DER, tree[nodo_I].der, tree[nodo_D].der, med + 1, fin, pos);
    }
    tree[nodo].GCD = gcd2(tree[nodo_I].GCD, tree[nodo_D].GCD);
}

void construye(int &nodo, int &nodo_I, int &nodo_D, int ini, int fin) {
    if(!nodo_I && !nodo_D) return;
    if(!nodo) nodo = ++sigNodo;
    tree[nodo].GCD = gcd2(tree[nodo_I].GCD, tree[nodo_D].GCD);
    if(ini != fin) {
        int med = (ini + fin) / 2;
        construye(IZQ, tree[nodo_I].izq, tree[nodo_D].izq, ini, med);
        construye(DER, tree[nodo_I].der, tree[nodo_D].der, med + 1, fin);
    }
}

pair < int, int > arbol[700000];
pair < int, int > coor[700000];
int sig_desicion[700000];
int nuevoNodo = 1;

void update(int &nodo, int ini, int fin, const int &x, const int &y, const lld &v) {
    if(ini > x || fin < x) return;
    if(!nodo) nodo = ++nuevoNodo;
    coor[nodo].first = ini, coor[nodo].second = fin;
    if(ini == fin) {
        sig_desicion[nodo] = nodo;
        update(nodo, 1, m, y, v);
    } else {
        int med = (ini + fin) / 2;
        update(IZQ_, ini, med, x, y, v);
        update(DER_, med + 1, fin, x, y, v);
        if(sig_desicion[nodo] == nodo) {
            merge(nodo, sig_desicion[IZQ_], sig_desicion[DER_], 1, m, y);
        } else {
            if(!IZQ_) sig_desicion[nodo] = sig_desicion[DER_];
            if(!DER_) sig_desicion[nodo] = sig_desicion[IZQ_];
            if(IZQ_ && DER_) {
                sig_desicion[nodo] = nodo;
                construye(nodo, sig_desicion[IZQ_], sig_desicion[DER_], 1, m);
            }
        }
    }
}

lld query(int &nodo, int ini, int fin, const int &x1, const int &y1, const int &x2, const int &y2) {
    if(ini > x2 || fin < x1) return 0;
    if(!nodo) return 0;
    if(sig_desicion[nodo] != nodo)
        return query(sig_desicion[nodo], coor[sig_desicion[nodo]].first, coor[sig_desicion[nodo]].second, x1, y1, x2, y2);

    if(ini >= x1 && fin <= x2) {
        return query(nodo, 1, m, y1, y2);
    } else {
        int med = (ini + fin) / 2;
        return gcd2(query(IZQ_, ini, med, x1, y1, x2, y2),
                    query(DER_, med + 1, fin, x1, y1, x2, y2));
    }
}

int main()
{
    optimizar;
    int Q;
    cin >> n >> m >> Q;
    int aux;
    int x1, y1, x2, y2;
    lld v;
    for(int i = 1; i <= Q; i++) {
        cin >> aux;
        if(aux == 1) {
            cin >> x1 >> y1 >> v;
            x1++, y1++;
            update(raiz, 1, n, x1, y1, v);
        } else {
            cin >> x1 >> y1 >> x2 >> y2;
            x1++, x2++, y1++, y2++;
            cout << query(raiz, 1, n, x1, y1, x2, y2) << "\n";
        }
    }
    return 0;
}
