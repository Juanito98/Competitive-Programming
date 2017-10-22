#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define INF (1 << 30)
#define izq (nodo * 2)
#define der (nodo * 2) + 1
using namespace std;

int n, Q;

int first[MAXN];
int expande[MAXN];

int arr[MAXN];

struct segment_tree {
    int * tree;
    int size;

    void init(int s) {
        tree = new int[s*4];
        size = s;
        construye(1, 1, size);
    }
    void clear() {
        delete[] tree;
    }

    void construye(int nodo, int ini, int fin) {
        if(ini == fin) {
            tree[nodo] = expande[ini];
        } else {
            int med = (ini + fin) / 2;
            construye(izq, ini, med);
            construye(der, med+1, fin);
            tree[nodo] = max(tree[izq], tree[der]);
        }
    }

    int query(int nodo, int ini, int fin, int i, int j) {
        if(ini > j || fin < i) return 0;
        if(ini >= i && fin <= j)
            return tree[nodo];
        int med = (ini + fin) / 2;
        return max(query(izq, ini, med, i, j), query(der, med+1, fin, i, j));
    }

};

segment_tree ST;

int query(int a, int b) {
    if(arr[a] == arr[b])
        return b - a + 1;
    return max(ST.query(1, 1, ST.size, a, first[b]-1), b - first[b] + 1);
}

int main()
{
    optimizar;
    cin >> n;
    int a, b;
    while(n != 0) {
        cin >> Q;
        arr[0] = -INF;
        arr[n] = INF;
        for(int i=1; i<=n; i++)
            cin >> arr[i];

        for(int i = n; i >= 1; i--) {
            if(arr[i] == arr[i+1]) {
                expande[i] = expande[i+1] + 1;
            } else {
                expande[i] = 1;
            }
        }
        for(int i=1; i<=n; i++) {
            if(arr[i] == arr[i-1]) {
                first[i] = first[i-1];
            } else {
                first[i] = i;
            }
        }

        ST.init(n);

        for(int i=1; i<= Q; i++) {
            cin >> a >> b;
            cout << query(a, b) << "\n";
        }

        ST.clear();

        cin >> n;
    }

    return 0;
}
