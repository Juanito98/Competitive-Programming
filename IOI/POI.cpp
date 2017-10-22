#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 2002
#define MAX_T 2002
using namespace std;

int n, T, id;

vector < int > cuales[MAXN];
int puntaje[MAX_T];


int cali[MAXN];
int cuantos[MAXN];
int arr[MAXN];

bool funcion(int a, int b) {
    if(cali[a] == cali[b]) {
        if(cuantos[a] == cuantos[b]) {
            return a < b;
        }
        return cuantos[a] > cuantos[b];
    }
    return cali[a] > cali[b];
}

int main()
{
    optimizar;

    cin >> n >> T >> id;
    int aux;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=T; j++) {
            cin >> aux;
            if(aux) {
                cuantos[i]++;
                cuales[i].push_back(j);
            } else {
                puntaje[j]++;
            }
        }
    }

    for(int i=1; i<=n; i++) {
        for(int j=0; j<cuales[i].size(); j++)
            cali[i]+= puntaje[cuales[i][j]];
        arr[i] = i;
    }

    cout << cali[id] << " ";
    sort(arr+1, arr+n+1, funcion);
    for(int i=1; i<=n; i++) {
        if(arr[i] == id)
            cout << i << "\n";
    }

    return 0;
}
