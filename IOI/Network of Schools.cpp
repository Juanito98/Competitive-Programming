#include <bits/stdc++.h>
#define MAXN 1000002
using namespace std;
int n;
stack < int > pila;
vector < int > invertido[MAXN];
vector < int > lista[MAXN];

int componentes;
int inDegree[MAXN];
int outDegree[MAXN];
int nodoSupremo[MAXN];

int nAux;

bool visitado[MAXN];

void desmarca() {
    for(int i=1; i<=nAux; i++)
        visitado[i]=false;
}

void marca(int nodo) {
    if(!nodoSupremo[nodo]) {
        nodoSupremo[nodo]=n;
        for(int i=0; i < lista[nodo].size(); i++)
            marca(lista[nodo][i]);
    }
}

void rellena(int nodo) {
    if(!visitado[nodo]) {
        visitado[nodo]=true;

        int aux;
        for(int i=0; i < lista[nodo].size(); i++) {
            aux=lista[nodo][i];
            if(nodoSupremo[nodo] != nodoSupremo[aux]) {
                inDegree[nodoSupremo[aux]]++;
                outDegree[nodoSupremo[nodo]]++;
            }
            rellena(aux);
        }
    }
}

void dfs(int nodo) {
    if(!visitado[nodo]) {
        visitado[nodo]=true;

        for(int i=0; i< invertido[nodo].size(); i++)
            dfs(invertido[nodo][i]);

        pila.push(nodo);
    }
}

void newNodos() {
    for(int i=1; i<=nAux; i++)
        dfs(i);

    int nodo;
    while(!pila.empty()) {
        nodo= pila.top();

        if(!nodoSupremo[nodo]) {
            n++;
            marca(nodo);
        }

        pila.pop();
    }

    desmarca();

    for(int i=1; i <= nAux; i++)
        rellena(i);

}

int main()
{
    scanf("%d", &nAux);

    int aux;
    int j;
    for(int i=1; i<=nAux; i++) {
        scanf("%d", &j);
        while(j != 0) {
            lista[i].push_back(j);
            invertido[j].push_back(i);
            scanf("%d", &j);
        }
    }

    newNodos();

    int in=0, out=0;
    for(int i=1; i<=n; i++) {
        if(inDegree[i] == 0)
            in++;
    }

    printf("%d\n", in);

    for(int i=1; i<=n; i++) {
        if(outDegree[i] == 0)
            out++;
    }

    if(n == 1) {
        printf("0\n");
    } else {
        printf("%d\n", max(in, out));
    }
    return 0;
}
