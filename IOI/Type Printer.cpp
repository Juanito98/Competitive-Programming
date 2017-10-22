#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#define MAXN 25002
#define MAX_TAM 22
using namespace std;
int mayor;

int max(int a, int b) {
    return a > b ? a : b;
}

struct ura {
    bool masLarga;
    char letra;
    bool finPalabra;
    vector < int > hijos;
};
ura arbol[MAXN*MAX_TAM];
int sigNodo;

vector < char > resp;

int buscaLetra(int nodo, char a) {
    for(int i=0; i<arbol[nodo].hijos.size(); i++) {
        if(arbol[arbol[nodo].hijos[i]].letra == a)
            return arbol[nodo].hijos[i];
    }
    ++sigNodo;
    arbol[nodo].hijos.push_back(sigNodo);
    arbol[sigNodo].letra=a;
    return sigNodo;
}

void inserta(string palabra) {
    int nodo=0;
    for(int i=0; i < palabra.size(); i++)
        nodo=buscaLetra(nodo, palabra[i]);
    arbol[nodo].finPalabra=true;
}

bool recorre(int x, int nodo) {
    if(!x) {
        arbol[nodo].masLarga=true;
        return true;
    }

    for(int i=0; i<arbol[nodo].hijos.size(); i++)
        if(recorre(x-1, arbol[nodo].hijos[i])) {
            arbol[nodo].masLarga=true;
            return true;
        }

    return false;
}

void imprime(int nodo) {
    int c=-1;
    for(int i=0; i<arbol[nodo].hijos.size(); i++) {
        if(!arbol[arbol[nodo].hijos[i]].masLarga) {
            resp.push_back(arbol[arbol[nodo].hijos[i]].letra);
            imprime(arbol[nodo].hijos[i]);
            resp.push_back('-');
        } else {
            c=i;
        }
    }
    if(arbol[nodo].finPalabra) {
        resp.push_back('P');
    }
    if(c >= 0) {
        resp.push_back(arbol[arbol[nodo].hijos[c]].letra);
        imprime(arbol[nodo].hijos[c]);
    }
}

void buscaProfundo(int x, int nodo) {
    if(!arbol[nodo].hijos.size()) {
        mayor=max(mayor, x);
    } else {
        for(int i=0; i<arbol[nodo].hijos.size(); i++)
            buscaProfundo(x+1, arbol[nodo].hijos[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    string aux;
    for(int i=1; i<=n; i++) {
        cin >> aux;
        inserta(aux);
    }
    buscaProfundo(0,0);
    recorre(mayor, 0);
    imprime(0);

    printf("%d\n", resp.size());
    for(int i=0; i<resp.size(); i++)
        printf("%c\n", resp[i]);
    return 0;
}
