#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 500002
#define IZQ (nodo * 2)
#define DER (nodo * 2 + 1)
using namespace std;

const lld MOD = 1000000007;

struct segment_tree {
    lld tree[MAXN * 5];
    int N;
    lld X[MAXN];

    void construye(int nodo, int ini, int fin) {
        if(ini == fin) {
            tree[nodo] = X[ini];
        } else {
            int med = (ini + fin) / 2;
            construye(IZQ, ini, med);
            construye(DER, med + 1, fin);
            tree[nodo] = abs(tree[IZQ]) * abs(tree[DER]);
            if(tree[nodo] >= MOD || tree[IZQ] < 0 || tree[DER] < 0)
                tree[nodo] = -(tree[nodo] % MOD);
        }
    }


    lld query(int nodo, int ini, int fin, const int &i, const int &j) {
        if(ini > j || fin < i) return 1;
        if(ini >= i && fin <= j) return tree[nodo];
        int med = (ini + fin) / 2;
        lld I = query(IZQ, ini, med, i, j);
        lld D = query(DER, med + 1, fin, i, j);
        lld r = abs(I) * abs(D);
        if(r >= MOD || I < 0 || D < 0)
            r = -(r % MOD);
        return r;
    }
    lld query(int i, int j) { return query(1, 0, N - 1, i, j); }

    void update(int nodo, int ini, int fin, const int &pos, const int &v) {
        if(ini > pos || fin < pos) return;
        if(ini == fin) {
            tree[nodo] = X[pos] = v;
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, pos, v);
            update(DER, med + 1, fin, pos, v);
            tree[nodo] = abs(tree[IZQ]) * abs(tree[DER]);
            if(tree[nodo] >= MOD || tree[IZQ] < 0 || tree[DER] < 0)
                tree[nodo] = -(tree[nodo] % MOD);
        }
    }
    void update(int pos, int v) { update(1, 0, N - 1, pos, v);}
};
segment_tree ST;

int n;
lld Y[MAXN];
int tree[MAXN * 5];
lld costo(int i) { return (abs(ST.query(0, i)) * Y[i]) % MOD; }

int compare(int i, int j) {
    if(i > j) return compare(j, i);
    if(i == j) return i;
    lld x = ST.query(i + 1, j);
    if(x < 0) return j;
    lld a = Y[i];
    lld b = x * Y[j];
    return a > b ? i : j;
}

void construye(int nodo, int ini, int fin) {
    if(ini == fin) {
        tree[nodo] = ini;
    } else {
        int med = (ini + fin) / 2;
        construye(IZQ, ini, med);
        construye(DER, med + 1, fin);
        tree[nodo] = compare(tree[IZQ], tree[DER]);
    }
}

void update(int nodo, int ini, int fin, const int &pos, const int &v) {
    if(ini > pos || fin < pos) return;
    if(ini == fin) {
        Y[pos] = v;
    } else {
        int med = (ini + fin) / 2;
        update(IZQ, ini, med, pos, v);
        update(DER, med + 1, fin, pos, v);
        tree[nodo] = compare(tree[IZQ], tree[DER]);
    }
}

int init(int N, int X_[ ], int Y_[ ]) {
    n = N;
    ST.N = N;
    for(int i = 0; i < N; i++) ST.X[i] = X_[i], Y[i] = Y_[i];
    ST.construye(1, 0, N - 1);
    construye(1, 0, N - 1);
    return costo(tree[1]);
}

int updateX(int pos, int v) {
    ST.update(pos, v);
    update(1, 0, n - 1, pos, Y[pos]);
    return costo(tree[1]);
}

int updateY(int pos, int v) {
    update(1, 0, n - 1, pos, v);
    return costo(tree[1]);
}

int main()
{
    optimizar;
    cin >> n;
    int *_X = new int[n];
    int *_Y = new int[n];
    for(int i = 0; i < n; i++) cin >> _X[i];
    for(int i = 0; i < n; i++) cin >> _Y[i];
    cout << init(n, _X, _Y) << "\n";
    int Q, type;
    int pos, val, r;
    for(cin >> Q; Q; Q--) {
        cin >> type;
        cin >> pos >> val;
        r = type == 1 ? updateX(pos, val) : updateY(pos, val);
        cout << r << "\n";
    }
    return 0;
}
