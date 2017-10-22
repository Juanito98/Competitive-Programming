#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define INF (1 << 30)
#define x first
#define y second
using namespace std;

int n, m, k;

vector < pair < int, int > > lista[MAXN];
bool visitados[MAXN];

int resp;

void lee() {
    int a, b, c;
    for(int i=1; i<=m; i++) {
        cin >> a >> b >> c;
        a++, b++;
        lista[a].push_back( make_pair(b, c) );
        lista[b].push_back( make_pair(a, c) );
    }
}

vector < int > d;

int raiz;
int mayor;
bool vis[MAXN];
int padre[MAXN];
int t[MAXN];

void lejano(int nodo, int costo) {
    visitados[nodo] = true;
    if(costo > mayor) {
        mayor = costo;
        raiz = nodo;
    }

    for(int i = 0; i < lista[nodo].size(); i++)
        if(!visitados[lista[nodo][i].x])
            lejano(lista[nodo][i].x, costo + lista[nodo][i].y);
}

void get_D(int nodo, int costo) {
    vis[nodo] = true;
    t[nodo] = costo;
    if(costo > mayor) {
        mayor = costo;
        raiz = nodo;
    }

    for(int i = 0; i < lista[nodo].size(); i++)
        if(!vis[lista[nodo][i].x]) {
            get_D(lista[nodo][i].x, costo + lista[nodo][i].y);
            padre[lista[nodo][i].x] = nodo;
        }
}

int sacaDiametro(int nodo) {
    mayor = -1;
    lejano(nodo, 0);
    mayor = -1;
    get_D(raiz, 0);
    int D = INF;
    int costo = 0;
    for(int i = raiz; padre[i]; i = padre[i]) {
        D = min(D, max(t[i], costo));
        costo+= (t[i] - t[padre[i]]);
    }
    if(D == INF)
        D = 0;
    resp = max(resp, t[raiz]);
    return D;
}

int main()
{
    optimizar;
    cin >> n >> m >> k;
    lee();

    for(int i=1; i<=n; i++) {
        if(!visitados[i])
            d.push_back(sacaDiametro(i));
    }

    sort(d.begin(), d.end());
    reverse(d.begin(), d.end());

    if(d.size() > 1)
        resp = max(resp, d[0] + d[1] + k);

    if(d.size() > 2)
        resp = max(resp, d[1] + d[2] + (2 * k));

    cout << resp << "\n";

    return 0;
}
