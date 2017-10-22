#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
using namespace std;
const int MAXN = 100002;

struct bit {
    lld tree[MAXN * 2];

    void update(int pos, int v) {
        for(; pos < MAXN * 2; pos += pos & (-pos))
            tree[pos] += v;
    }

    lld query(int pos) {
        if(pos < 0) return 0;
        lld c = 0;
        for(; pos; pos -= pos & (-pos))
            c += tree[pos];
        return c;
    }
    lld query(int a, int b) { return  query(b) - query(a - 1); }
};

int n, m;
lld D;
lld d[MAXN];
bit BIT, S;
vector < int > lista[MAXN];

int vis[MAXN];
int color;
int masLejano(int nodo) {
    queue < int > cola;
    color++;
    lld t = 0;
    cola.push(nodo);
    vis[nodo] = color;
    while(!cola.empty()) {
        for(int i = cola.size(); i; i--) {
            nodo = cola.front();
            cola.pop();
            d[nodo] = max(d[nodo], t);
            for(int j = 0; j < lista[nodo].size(); j++) {
                if(vis[lista[nodo][j]] == color) continue;
                cola.push(lista[nodo][j]);
                vis[lista[nodo][j]] = color;
            }
        }
        t++;
    }
    return nodo;
}

void procesa() {
    int a, b;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        lista[a].push_back(b);
        lista[b].push_back(a);
    }
    a = masLejano(1);
    b = masLejano(a);
    a = masLejano(b);
    D = max(D, d[a]);
    for(int i = 1; i <= n; i++) lista[i].clear();
}

int main()
{
    optimizar;
    while(cin >> n >> m) {
        D = 0;
        procesa();
        for(int i = 1; i <= n; i++) {
            BIT.update(d[i] + 1, 1);
            S.update(d[i] + 1, d[i] + 1);
            d[i] = 0;
        }
        swap(n, m);
        procesa();
        long double r = 0.0;
        for(int i = 1; i <= n; i++) {
            r += D * BIT.query(D - d[i]);
            r += d[i] * BIT.query(D - d[i] + 1, MAXN * 2 - 1) + S.query(D - d[i] + 1, MAXN * 2 - 1);
            d[i] = 0;
        }
        cout << setprecision(3) << fixed << r / (long double) (n * m) << "\n";
        for(int i = 0; i < 2 * MAXN; i++)
            BIT.tree[i] = S.tree[i] = 0;
    }
    return 0;
}
