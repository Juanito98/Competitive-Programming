#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1000005
#define INF (1 << 30)
#define lld long long int
#define x first
#define y second
using namespace std;

int n;

lld resp[MAXN];
int cycle;

vector < int > lista[MAXN];
int vis[MAXN];
int color;
int padre[MAXN];

struct ura {
    int hijo;
    lld c;
};
ura child[MAXN];

vector < int > ciclos[MAXN];
int cont;

lld costo(int a, int b) {
    if(a == b)
        return 0;
    if(child[a].hijo == b)
        return child[a].c;
    return child[b].c;
}

bool anyCycle;
void buscaCiclo(int nodo) {
    stack < pair < int, int > > pila; // x -> nodo, y -> padre
    int papa = 0;
    pila.push( make_pair(nodo, papa) );

    while(!pila.empty()) {
        nodo = pila.top().x;
        papa = pila.top().y;
        pila.pop();
        if(vis[nodo] != color) {
            vis[nodo] = color;
            padre[nodo] = papa;
            for(int i=0; i < lista[nodo].size(); i++)
                pila.push( make_pair(lista[nodo][i], nodo) );
        } else {
            if(!anyCycle) {
                if(padre[papa] != nodo || (child[papa].hijo == nodo && child[nodo].hijo == papa)) {
                    anyCycle = true;
                    cont++;
                    int ini = papa;
                    int fin = nodo;
                    while(ini != fin) {
                        ciclos[cont].push_back(ini);
                        ini = padre[ini];
                    }
                    ciclos[cont].push_back(ini);
                }
            }
        }
    }
}

bool esRaiz[MAXN];
lld profundidad[MAXN];

void checa_lejano(int nodo) {
    stack < pair < int, lld > > pila; // x -> nodo, y -> costo
    lld c = 0;
    lld mayor = 0;
    int lejano = nodo;
    pila.push( make_pair(nodo, c) );
    while(!pila.empty()) {
        nodo = pila.top().x;
        c = pila.top().y;
        pila.pop();
        vis[nodo] = color;
        if(mayor < c) {
            mayor = c;
            lejano = nodo;
        }
        for(int i = 0; i < lista[nodo].size(); i++)
            if(vis[lista[nodo][i]] != color && !esRaiz[lista[nodo][i]])
                pila.push( make_pair(lista[nodo][i], c + costo(nodo, lista[nodo][i])) );
    }

    resp[cycle] = max(resp[cycle], mayor);
}

void get_profundidad(int raiz) {
    stack < pair < int, lld > > pila; // x -> nodo, y -> costo
    int nodo = raiz;
    lld c = 0;
    int lejano = raiz;
    pila.push( make_pair(nodo, c) );
    while(!pila.empty()) {
        nodo = pila.top().x;
        c = pila.top().y;
        pila.pop();
        vis[nodo] = color;
        if(profundidad[raiz] < c) {
            profundidad[raiz] = c;
            lejano = nodo;
        }
        for(int i = 0; i < lista[nodo].size(); i++)
            if(vis[lista[nodo][i]] != color && !esRaiz[lista[nodo][i]])
                pila.push( make_pair(lista[nodo][i], c + costo(nodo, lista[nodo][i])) );
    }

    color--;
    esRaiz[raiz] = false;
    checa_lejano(lejano);
    esRaiz[raiz] = true;
    color++;
}

lld memo[MAXN];
lld f1[MAXN];
lld f2[MAXN];

lld aux;
void check_cycle(int ind) {
    lld c = 0;
    memo[0] = 0;
    for(int i=1; i < ciclos[ind].size(); i++) {
        c+= costo(ciclos[ind][i-1], ciclos[ind][i]);
        memo[i] = c;
    }
    c+= costo(ciclos[ind][ciclos[ind].size()-1] , ciclos[ind][0]);

    f1[ciclos[ind].size()] = -(INF * (lld) ciclos[ind].size());
    f2[ciclos[ind].size()] = -(INF * (lld) ciclos[ind].size());

    for(int i = ciclos[ind].size() - 1; i>=0; i--) {
        f1[i] = max(f1[i+1], profundidad[ciclos[ind][i]] + memo[i]);
        f2[i] = max(f2[i+1], profundidad[ciclos[ind][i]] - memo[i]);
    }

    for(int i=0; i < ciclos[ind].size() - 1; i++) {
        aux = profundidad[ciclos[ind][i]] - memo[i] + f1[i+1];
        aux = max(aux, c + profundidad[ciclos[ind][i]] + memo[i] + f2[i+1]);
        if(resp[ind] < aux)
            resp[ind] = max(resp[ind], aux);
    }
}

int main()
{
    optimizar;

    cin >> n;
    int a, b;
    for(int i=1; i<=n; i++) {
        cin >> a >> b;
        lista[i].push_back(a);
        lista[a].push_back(i);
        child[i].hijo = a;
        child[i].c = b;
    }

    color++;

    for(int i=1; i<=n; i++) {
        if(!vis[i]) {
            anyCycle = false;
            buscaCiclo(i);
        }
    }

    for(int i=1; i<= cont; i++)
        for(int j =0; j < ciclos[i].size(); j++)
            esRaiz[ciclos[i][j]] = true;

    color++;
    for(int i=1; i<= cont; i++) {
        cycle= i;
        for(int j =0; j < ciclos[i].size(); j++)
            get_profundidad(ciclos[i][j]);
    }

    for(int i=1; i<= cont; i++)
        check_cycle(i);

    lld mayor = 0;
    for(int i=1; i <= cont; i++)
        mayor+= resp[i];

    cout << mayor << "\n";
    return 0;
}
