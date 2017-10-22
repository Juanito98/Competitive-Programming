#include <bits/stdc++.h>
#define lld long long int
#define IZQ (nodo * 2)
#define DER (nodo * 2 + 1)
using namespace std;
const int MAXN = 100002;
const int INF = (1 << 30);

int n;
bool bucket[MAXN];
int A[MAXN], B[MAXN];

struct segment_tree {
    int mini[MAXN *  5];
    int lazy[MAXN * 5];

    void propagate(int nodo, int ini, int fin) {
        if(lazy[nodo] != INF) {
            mini[nodo] = mini[nodo] + lazy[nodo];
            if(ini != fin) {
                if(lazy[IZQ] != INF) lazy[IZQ] += lazy[nodo];
                else lazy[IZQ] = lazy[nodo];
                if(lazy[DER] != INF) lazy[DER] += lazy[nodo];
                else lazy[DER] = lazy[nodo];
            }
            lazy[nodo] = INF;
        }
    }

    int menor() {
        propagate(1, 1, 2 * n);
        return mini[1];
    }

    void update(int nodo, int ini, int fin, int i, int j, int v) {
        propagate(nodo, ini, fin);
        if(ini > j || fin < i) return;
        if(ini >= i && fin <= j) {
            lazy[nodo] = v;
            propagate(nodo, ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, i, j, v);
            update(DER, med + 1, fin, i, j, v);
            mini[nodo] = min(mini[IZQ], mini[DER]);
        }
    }
    void update(int i, int j, int v) { update(1, 1, 2 * n, i, j, v); }

    int query(int nodo, int ini, int fin, int pos) {
        propagate(nodo, ini, fin);
        if(ini == fin) return mini[nodo];
        int med = (ini + fin) / 2;
        if(pos <= med) return query(IZQ, ini, med, pos);
        else return query(DER, med + 1, fin, pos);
    }
    int query(int pos) { 
        if(pos > 2 * n) return 0;
        return query(1, 1, 2 * n, pos); 
    }
};
segment_tree gananMayores, gananMenores;

void quita(int p) {
    int x = gananMayores.query(p) - gananMayores.query(p + 1);
    gananMayores.update(1, p, -x);
}

void pon(segment_tree &ST, int p, int v) {
    ST.update(1, p, v);
}

int res;

void solve() {
    for(int i = 2 * n; i > 0; i--) 
        pon(gananMayores, i, bucket[i] ? -1 : 1);

    for(int i = n; i >= 0; i--) {
        int enfA = i, enfB = n - enfA;
        enfA -= max(0, -gananMayores.menor());
        enfB -= max(0, -gananMenores.menor());
        res = max(res, enfA + enfB);

        if(i == 0) break;
        quita(A[i]);
        pon(gananMenores, A[i], 1);
        pon(gananMenores, B[i], -1);
    }
}

int main()
{
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
        bucket[A[i]] = true;
    }
    int aux = 0;
    for(int i = 1; i <= 2 * n; i++) 
        if(!bucket[i]) B[++aux] = i;
    reverse(B + 1, B + n + 1);
    solve();
    cout << res << "\n";
    return 0;
}