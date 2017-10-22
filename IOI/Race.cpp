#include <bits/stdc++.h>
#include "race.h"
#define MAXN 200002
using namespace std;

int n, k;

int hijos[MAXN];
int vis[MAXN];
bool eliminado[MAXN];
int color;
vector < pair < int, int > > lista[MAXN];

int _min(int a, int b) {
    if(a == -1) return b;
    if(b == -1) return a;
    return min(a, b);
}

stack < int > P;
stack < int > pila;

void get_hijos(int nodo) {
    pila.push(nodo);
    P.push(nodo);
    vis[nodo] = color;
    while(!pila.empty()) {
        nodo = pila.top();
        pila.pop();
        hijos[nodo] = 1;
        for(int i = 0; i < lista[nodo].size(); i++) {
            if(vis[lista[nodo][i].first] != color && !eliminado[lista[nodo][i].first]) {
                pila.push(lista[nodo][i].first);
                P.push(lista[nodo][i].first);
                vis[lista[nodo][i].first] = color;
            }
        }
    }

    color++;
    while(!P.empty()) {
        nodo = P.top();
        P.pop();
        if(vis[nodo] != color) {
            for(int i = 0; i < lista[nodo].size(); i++) {
                if(vis[lista[nodo][i].first] != color)
                    hijos[lista[nodo][i].first]+= hijos[nodo];
            }
            vis[nodo] = color;
        }
    }
}

int get_u(int med, int nodo) {
    bool mePase = true;
    int ant = -1;
    while(mePase) {
        mePase = false;
        for(int i = 0; i < lista[nodo].size(); i++) {
            if(hijos[lista[nodo][i].first] > med && !eliminado[lista[nodo][i].first]) {
                if(ant != lista[nodo][i].first) {
                    ant = nodo;
                    nodo = lista[nodo][i].first;
                    mePase = true;
                    break;
                }
            }
        }
    }
    return nodo;
}

int cuantos[1000002]; // el menor numero de nodos que hacen k
bool existe_k[1000002];

vector < int > valores;

struct ura {
    int nodo;
    int c;
    int t;
};

ura make_ura(int nodo, int c, int t) {
    ura S;
    S.nodo = nodo;
    S.c = c;
    S.t = t;
    return S;
}

struct _queue {
    ura cola[MAXN + 10];
    int ini, fin;

    void init() {
        ini = 0, fin = 0;
    }
    ura front() {
        return cola[ini];
    }
    void pop() {
        ini++;
    }
    void push(ura a) {
        cola[fin++] = a;
    }
    bool empty() {
        return ini == fin;
    }
    ura operator[](int pos) {
        return cola[pos];
    }
};

_queue cola;

int bfs(int nodo, int c) {
    int menor = -1;
    vis[nodo] = color;
    cola.init();
    cola.push(make_ura(nodo, c, 1));
    int t;
    while(!cola.empty()) {
        nodo = cola.front().nodo;
        c = cola.front().c;
        t = cola.front().t;
        cola.pop();
        if(c > k) continue;
        for(int i = 0; i < lista[nodo].size(); i++) {
            if(vis[lista[nodo][i].first] != color && !eliminado[lista[nodo][i].first]) {
                vis[lista[nodo][i].first] = color;
                cola.push(make_ura(lista[nodo][i].first, c + lista[nodo][i].second, t + 1));
            }
        }
    }

    for(int i = 0; i < cola.fin; i++) {
        if(cola[i].c > k) continue;
        if(cola[i].c == k) {
            menor = _min(cola[i].t, menor);
        } else {
            if(existe_k[k - cola[i].c]) {
                menor = _min(menor, cuantos[k - cola[i].c] + cola[i].t);
            }
        }
    }

    for(int i = 0; i < cola.fin; i++) {
        if(cola[i].c > k) continue;
        valores.push_back(cola[i].c);
        existe_k[cola[i].c] = true;
        if(cuantos[cola[i].c] > cola[i].t || !cuantos[cola[i].c])
            cuantos[cola[i].c] = cola[i].t;
    }

    return menor;
}

int solve(int u) {
    int menor = -1;
    color++;
    vis[u] = color;
    for(int i = 0; i < lista[u].size(); i++) {
        if(!eliminado[lista[u][i].first]) {
            menor = _min(menor, bfs(lista[u][i].first, lista[u][i].second));
        }
    }
    for(int i = 0; i < valores.size(); i++) {
        existe_k[valores[i]] = false;
        cuantos[valores[i]] = 0;
    }
    valores.clear();
    return menor;
}

int sol(int raiz) {
    color++;
    get_hijos(raiz);
    int mid = hijos[raiz] / 2;
    color++;
    int u = get_u(mid, raiz);
    int x = solve(u);
    eliminado[u] = true;
    for(int i = 0; i < lista[u].size(); i++) {
        if(!eliminado[lista[u][i].first])
            x = _min(x, sol(lista[u][i].first));
    }
    return x;
}

int best_path(int N, int K, int H[][2], int L[]) {
    n = N;
    k = K;
    for(int i = 0; i < (n - 1); i++) {
        lista[H[i][0]].push_back(make_pair(H[i][1], L[i]));
        lista[H[i][1]].push_back(make_pair(H[i][0], L[i]));
    }
    return sol(0);
}

