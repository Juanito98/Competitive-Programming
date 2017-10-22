#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define izq (nodo * 2)
#define der (nodo * 2) + 1
#define INF (1 << 30)
using namespace std;

int n;

int arr[MAXN] = {(1 << 30)};
int higherLeft[MAXN];
int higherRight[MAXN];

int pila[MAXN];
int tope;

void f(int a) {
    while(arr[a] >= arr[pila[tope]])
        tope--;

    higherLeft[a] = pila[tope];
    pila[++tope] = a;
}

void f2(int a) {
    while(arr[a] >= arr[pila[tope]])
        tope--;

    higherRight[a] = pila[tope];
    pila[++tope] = a;
}

int ST[MAXN*5];

void creaST(int nodo, int ini, int fin) {
    if(ini == fin) {
        ST[nodo] = arr[ini];
    } else {
        int med = (ini + fin) / 2;
        creaST(izq, ini, med);
        creaST(der, med+1, fin);

        ST[nodo] = min(ST[izq], ST[der]);
    }
}

int ini;
int fin;

int query(int nodo, int i, int j) {
    if(i > fin || j < ini)
        return INF;
    if(i >= ini && j <= fin)
        return ST[nodo];

    int med = (i + j) / 2;
    return min(query(izq, i, med), query(der, med+1, j));
}

int checkLeft(int j) {
    int i = higherLeft[j];
    if(!i) return arr[j];
    ini = i + 1;
    fin = j - 1;
    return arr[j] - query(1, 1, n);
}

int checkRight(int i) {
    int j = higherRight[i];
    if(!j) return arr[i];
    ini = i + 1;
    fin = j - 1;
    return arr[i] - query(1, 1, n);
}

bool imprimi;

void checkPeak(int i) {
    int L = checkLeft(i);
    int R = checkRight(i);

    if(L >= 150000 && R >= 150000) {
        if(imprimi) cout << " ";
        imprimi = true;
        cout << i;
    }
}

void getPeaks() {
    for(int i=1; i<=n; i++)
        if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            checkPeak(i);
}

int main()
{
    optimizar;

    while( cin >> n ) {
        imprimi = false;
        tope = 0;
        for(int i=1; i<=n; i++) {
            cin >> arr[i];
            f(i);
        }
        tope = 0;
        for(int i=n; i>=1; i--) f2(i);

        creaST(1, 1, n);
        getPeaks();
        cout << "\n";
    }

    return 0;
}
