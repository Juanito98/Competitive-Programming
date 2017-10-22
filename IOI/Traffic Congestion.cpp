#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1000002
#define lld long long int
#define INF (1 << 30)
using namespace std;

int n;

lld traffic[MAXN];

lld people[MAXN]; //personas de cada nodo
lld sumaTotal; // la suma de personas

vector < int > lista[MAXN];
bool vis[MAXN];

lld recorre(int nodo) {
    if(vis[nodo]) return 0;
    vis[nodo] = true;
    lld suma = people[nodo];
    lld mayor = 0;
    lld aux;
    for(int i=0; i < lista[nodo].size(); i++) {
        aux = recorre(lista[nodo][i]);
        suma+= aux;
        mayor = max(mayor, aux);
    }
    traffic[nodo] = max(mayor, sumaTotal - suma);
    return suma;
}

int main()
{
    optimizar;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> people[i];
        sumaTotal+= people[i];
    }
    int a, b;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        lista[a].push_back(b);
        lista[b].push_back(a);
    }

    recorre(0);

    lld menor = INF;
    int ind = 0;
    for(int i = 0; i < n; i++) {
        if(traffic[i] < menor) {
            menor = traffic[i];
            ind = i;
        }
    }

    cout << ind << "\n";
    return 0;
}
