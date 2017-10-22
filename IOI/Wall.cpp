#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 2000002
#define izq (nodo * 2)
#define der (nodo * 2) + 1
using namespace std;

int n, Q;

struct segment_tree {
    int todo_es[MAXN*4];
    int corta[MAXN*4];
    int crece[MAXN*4];

    int _min(int a, int b) {
        if(a == -1) return b;
        if(b == -1) return a;
        return min(a, b);
    }

    void construye(int nodo, int ini, int fin) {
        corta[nodo] = -1;
        crece[nodo] = -1;
        todo_es[nodo] = 0;
        if(ini == fin) {
            return;
        } else {
            int med = (ini + fin) / 2;
            construye(izq, ini, med);
            construye(der, med+1, fin);
        }
    }

    void checa(int nodo, int v) {
        if(corta[nodo] <= crece[nodo]) {
            if(corta[nodo] != -1) {
                todo_es[nodo] = v;
                crece[nodo] = -1;
                corta[nodo] = -1;
            }
        }
    }

    void propagate_corta(int nodo, int ini, int fin) {
        if(corta[nodo] != -1) {
            if(todo_es[izq] != -1) {
                todo_es[izq] = min(todo_es[izq], corta[nodo]);
            } else {
                corta[izq] = _min(corta[nodo], corta[izq]);
                checa(izq, corta[izq]);
            }
            if(todo_es[der] != -1) {
                todo_es[der] = min(corta[nodo], todo_es[der]);
            } else {
                corta[der] = _min(corta[nodo], corta[der]);
                checa(der, corta[der]);
            }
            corta[nodo] = -1;
        }
    }

    void propagate_crece(int nodo, int ini, int fin) {
        if(crece[nodo] != -1) {
            if(todo_es[izq] != -1) {
                todo_es[izq] = max(todo_es[izq], crece[nodo]);
            } else {
                crece[izq] = max(crece[nodo], crece[izq]);
                checa(izq, crece[izq]);
            }
            if(todo_es[der] != -1) {
                todo_es[der] = max(crece[nodo], todo_es[der]);
            } else {
                crece[der] = max(crece[nodo], crece[der]);
                checa(der, crece[der]);
            }
            crece[nodo] = -1;
        }
    }

    void propagate(int nodo, int ini, int fin) {
        if(ini == fin) {
            if(crece[nodo] != -1)
                todo_es[nodo] = crece[nodo];
            crece[nodo] = corta[nodo] = -1;
            return;
        }
        if(todo_es[nodo] != -1) {
            todo_es[izq] = todo_es[der] = todo_es[nodo];
            crece[izq] = corta[izq] = -1;
            crece[der] = corta[der] = -1;
            todo_es[nodo] = -1;
        } else {
            propagate_crece(nodo, ini, fin);
            propagate_corta(nodo, ini, fin);
        }
    }

    void update_crece(int nodo, int ini, int fin, int i, int j, int v) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return;
        if(ini == fin) {
            todo_es[nodo] = max(todo_es[nodo], v);
            return;
        }
        if(ini >= i && fin <= j) {
            crece[nodo] = v;
        } else {
            int med = (ini + fin) / 2;
            update_crece(izq, ini, med, i, j, v);
            update_crece(der, med+1, fin, i, j, v);
        }
    }

    void update_corta(int nodo, int ini, int fin, int i, int j, int v) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return;
        if(ini == fin) {
            todo_es[nodo] = min(todo_es[nodo], v);
            return;
        }
        if(ini >= i && fin <= j) {
            corta[nodo] = v;
        } else {
            int med = (ini + fin) / 2;
            update_corta(izq, ini, med, i, j, v);
            update_corta(der, med+1, fin, i, j, v);
        }
    }

    void imprime(int nodo, int ini, int fin) {
        propagate(nodo, ini, fin);
        if(ini == fin) {
            cout << todo_es[nodo] << "\n";
        } else {
            int med = (ini + fin) / 2;
            imprime(izq, ini, med);
            imprime(der, med+1, fin);
        }
    }
};

segment_tree ST;

int main()
{
    optimizar;
    cin >> n >> Q;
    int aux, a, b, c;
    ST.construye(1, 1, n);
    for(int i=1; i<=Q; i++) {
        cin >> aux >> a >> b >> c;
        a++, b++;
        if(aux == 1) {
            ST.update_crece(1, 1, n, a, b, c);
        } else {
            ST.update_corta(1, 1, n, a, b, c);
        }
    }
    ST.imprime(1, 1, n);
    return 0;
}
