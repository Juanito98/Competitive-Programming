#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define IZQ (nodo * 2)
#define DER (nodo * 2) + 1
#define lld long long int
#define MAXN 100002
using namespace std;

int n, start, d;
int arr[MAXN];

bool f(int a, int b) { return arr[a] > arr[b]; }

struct segment_tree {
    int ordenados[MAXN];
    int pos[MAXN];
    bool active[MAXN];

    struct ura {
        lld S;
        int cuantos;
    } tree[MAXN * 5];

    void construye() {
        for(int i = 1; i <= n; i++) ordenados[i] = i;
        sort(ordenados + 1, ordenados + n + 1, f);
        for(int i = 1; i <= n; i++) pos[ordenados[i]] = i;
        for(int i = 1; i <= n; i++) ordenados[i] = arr[ordenados[i]];
    }

    void update(int nodo, int ini, int fin, const int & p, const bool &v) {
        if(ini > p || fin < p) return;
        if(ini == fin) {
            active[p] = v;
            tree[nodo].cuantos = v ? 1 : 0;
            tree[nodo].S = v ? ordenados[p] : 0;
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, p, v);
            update(DER, med + 1, fin, p, v);
            tree[nodo].S = tree[IZQ].S + tree[DER].S;
            tree[nodo].cuantos = tree[IZQ].cuantos + tree[DER].cuantos;
        }
    }

    void activa(int p) { update(1, 1, n, pos[p], true); }
    void desactiva(int p) { update(1, 1, n, pos[p], false); }

    lld query(int nodo, int ini, int fin, int k) {
        if(k <= 0) return 0;
        if(tree[nodo].cuantos <= k) return tree[nodo].S;
        int med = (ini + fin) / 2;
        return query(IZQ, ini, med, min(tree[IZQ].cuantos, k))
            + query(DER, med + 1, fin, k - min(tree[IZQ].cuantos, k));
    }

    lld query(int k) { return query(1, 1, n, k); }
};
segment_tree ST;

void quita(int ini, int fin) {
    for(int i = ini; i <= fin; i++) ST.desactiva(i);
}

pair < lld, int > recorre(int ini, int fin, int dias, int mov) {
    pair < lld, int > r;
    r.first = 0, r.second = ini;
    lld aux;
    for(int i = ini; i <= fin; i++) {
        ST.activa(i);
        aux = ST.query(dias - (i - start) * mov);
        if(aux > r.first)
            r = make_pair(aux, i);
    }
    quita(r.second + 1, fin);
    return r;
}

void llena(int ini, int fin, int e1, int corte, lld A[ ], const int mov) {
    if(ini > fin) return;
    int dia = (ini + fin) / 2;
    pair < lld, int > r = recorre(e1, corte, dia, mov);
    A[dia] = r.first;
    llena(dia + 1, fin, r.second, corte, A, mov);
    quita(e1, r.second);
    llena(ini, dia - 1, e1, r.second, A, mov);
}

void solve(lld A1[ ], lld A2[ ]) {
    if(start > n) return;
    llena(0, d, start, n, A1, 1);
    llena(0, d, start, n, A2, 2);
}

lld I1[MAXN * 3];
lld I2[MAXN * 3];
lld D1[MAXN * 3];
lld D2[MAXN * 3];

int main()
{
    optimizar;
    cin >> n >> start >> d;
    start++;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];

    ST.construye();
    solve(D1, D2);

    reverse(arr + 1, arr + n + 1);
    start = n - start + 2;
    ST.construye();
    solve(I1, I2);

    lld mayor = D1[d];

    for(int i = 0; i <= d; i++) {
        int j = d - i;
        if(j < 1) continue;
        mayor = max(mayor, D2[i] + I1[j - 1]);
        if(j < 2) continue;
        mayor = max(mayor, D1[i] + I2[j - 2]);
    }
    cout << mayor << "\n";
    return 0;
}
