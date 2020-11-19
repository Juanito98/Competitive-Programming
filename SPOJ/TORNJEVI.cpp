/*
    2SAT Problem
    Idea: cada casilla tiene 4 nodos, un rayo hacia alguna dirección
    https://www.spoj.com/status/ns=26948464
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

const int U = 0;
const int D = 1;
const int R = 2;
const int L = 3;

int n;
const int MAX = 40002;

//We have a vertex representing a var and other for his negation.
//Every edge stored in G represents an implication. To add an equation of the form a||b, use addor(a, b)
//MAX=max cant var, n=cant var
#define addor(a, b) (G[neg(a)].push_back(b), G[neg(b)].push_back(a))
vector<int> G[MAX * 2];
//idx[i]=index assigned in the dfs
//lw[i]=lowest index(closer from the root) reachable from i
int lw[MAX * 2], idx[MAX * 2], qidx;
stack<int> q;
int qcmp, cmp[MAX * 2];
//verdad[cmp[i]]=valor de la variable i
bool verdad[MAX * 2 + 1];

int neg(int x) { return x >= n ? x - n : x + n; }
void tjn(int v) {
    lw[v] = idx[v] = ++qidx;
    q.push(v), cmp[v] = -2;
    for (int u : G[v]) {
        if (!idx[u] || cmp[u] == -2) {
            if (!idx[u]) tjn(u);
            lw[v] = min(lw[v], lw[u]);
        }
    }
    if (lw[v] == idx[v]) {
        int x;
        do {
            x = q.top();
            q.pop();
            cmp[x] = qcmp;
        } while (x != v);
        verdad[qcmp] = (cmp[neg(v)] < 0);
        qcmp++;
    }
}
//remember to CLEAR G!!!
bool satisf() {  //O(n)
    fill(idx, idx + 2 * n, 0), qidx = 0;
    fill(cmp, cmp + 2 * n, -1), qcmp = 0;
    for (int i = 0; i < n; ++i) {
        if (!idx[i]) tjn(i);
        if (!idx[neg(i)]) tjn(neg(i));
    }
    for (int i = 0; i < n; ++i)
        if (cmp[i] == cmp[neg(i)]) return false;
    return true;
}

int r, c;
char arr[102][102];

int getNodo(int i, int j, int orientacion) {
    return (i*c + j) + r*c*orientacion;
}

int orientacionContraria(int orientacion) {
    if (orientacion == U) return D;
    if (orientacion == D) return U;
    if (orientacion == L) return R;
    return L;
}

pii getTower(int i, int j, int orientacion) {
    // Returns {-1,-1} si no
    int di = 0, dj = 0;
    if (orientacion == U) di = -1;
    else if (orientacion == D) di = 1;
    else if (orientacion == L) dj = -1;
    else if (orientacion == R) dj = 1;

    do {
        i += di;
        j += dj;
    } while (i >= 0 && j >= 0 && i < r && j < c && arr[i][j] != 'T' && arr[i][j] != '#');
    if (i < 0 || j < 0 || i >= r || j >= c || arr[i][j] == '#')
        return {-1, -1};
    return {i, j};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;
    n = r * c * 4;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j)
            cin >> arr[i][j];
    } // Cada nodo va a tener 4 variables

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (arr[i][j] == 'T') {
                // Arriba o abajo
                addor(getNodo(i, j, U), getNodo(i, j, D));
                addor(neg(getNodo(i, j, U)), neg(getNodo(i, j, D)));
                // Izquierda o derecha
                addor(getNodo(i, j, L), getNodo(i, j, R));
                addor(neg(getNodo(i, j, L)), neg(getNodo(i, j, R)));
                // Ver que torres no se apunten entre sí
                for (int orientacion = 0; orientacion < 4; ++orientacion) {
                    pii tower = getTower(i, j, orientacion);
                    if (tower.first == -1) continue;
                    int oc = orientacionContraria(orientacion);
                    addor(neg(getNodo(i, j, orientacion)), neg(getNodo(i, j, orientacion)));
                    addor(neg(getNodo(tower.first, tower.second, oc)), neg(getNodo(tower.first, tower.second, oc)));
                }
            } else if (arr[i][j] == 'n') {
                vector<pii> tower(4, {-1, -1});
                for (int o = 0; o < 4; ++o) {
                    tower[o] = getTower(i, j, o);
                }
                int a = -1, b = -1;
                if (tower[U].first != -1) {
                    a = getNodo(tower[U].first, tower[U].second, D);
                } else if (tower[D].first != -1) {
                    a = getNodo(tower[D].first, tower[D].second, U);
                }
                if (tower[L].first != -1) {
                    b = getNodo(tower[L].first, tower[L].second, R);
                } else if (tower[R].first != -1) {
                    b = getNodo(tower[R].first, tower[R].second, L);
                }
                if (a == -1) a = b;
                if (b == -1) b = a;
                addor(a, b);
            }
        }
    }

    satisf();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char c = arr[i][j];
            if (arr[i][j] == 'T') {
                int msc = 0;
                for (int o = 0; o < 4; ++o) 
                    if (verdad[cmp[getNodo(i, j, o)]])
                        msc |= (1 << o);
                if ((msc & (1 << L)) && (msc & (1 << D)))
                    c = '1';
                else if ((msc & (1 << D)) && (msc & (1 << R)))
                    c = '2';
                else if ((msc & (1 << R)) && (msc & (1 << U)))
                    c = '3';
                else if ((msc & (1 << U)) && (msc & (1 << L)))
                    c = '4';
            }
            cout << c;
        }
        cout << "\n";
    }

    return 0;
}