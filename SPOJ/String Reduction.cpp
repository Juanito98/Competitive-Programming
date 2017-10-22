#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 302
#define INF (1 << 30)
using namespace std;

char cad[MAXN];

bool reduceA[MAXN][MAXN];
bool visA[MAXN][MAXN];

bool reduceB[MAXN][MAXN];
bool visB[MAXN][MAXN];

int memo[MAXN][MAXN];
bool visitados[MAXN][MAXN];

bool checaA(int, int);
bool checaB(int, int);

int f(int i, int j) {
    if(i > j)
        return 0;

    if(i == j)
        return memo[i][j] = 1;

    if(checaA(i, j) || checaB(i, j))
        return memo[i][j] = 1;

    if(!visitados[i][j]) {
        visitados[i][j] = true;
        int menor = INF;
        for(int k = i; k < j; k++)
            menor = min(menor, f(i, k) + f(k+1, j));
        memo[i][j] = menor;
    }
    return memo[i][j];
}

int main()
{
    optimizar;

    cin >> cad;
    int a;
    for(a = 0; cad[a]; a++);
    cout << f(0, a-1) << "\n";

    return 0;
}


bool checaA(int i, int j) {
    if(visA[i][j])
        return reduceA[i][j];

    visA[i][j] = true;

    if(i > j)
        return reduceA[i][j] = false;

    if(i == j) {
        if(cad[i] == 'a')
            return reduceA[i][j] = true;
        else
            return reduceA[i][j] = false;
    }

    if(cad[i] == cad[j])
        if(checaA(i+1, j-1))
            return reduceA[i][j] = true;

    for(int k=i+1; k < j; k++) {
        if(cad[k] == 'a') {
            if( (checaB(i, k-1) && checaB(k+1, j)) || (checaA(i, k-1) && checaA(k+1, j)) )
                return reduceA[i][j] = true;
        }
    }
    return reduceA[i][j];
}

bool checaB(int i, int j) {

    if(visB[i][j])
        return reduceB[i][j];

    visB[i][j] = true;

    if(i > j)
        return reduceB[i][j] = false;

    if(i == j) {
        if(cad[i] == 'b')
            return reduceB[i][j] = true;
        else
            return reduceB[i][j] = false;
    }

    if(cad[i] == cad[j])
        if(checaB(i+1, j-1))
            return reduceB[i][j] = true;

    for(int k=i+1; k < j; k++) {
        if(cad[k] == 'b') {
            if( (checaB(i, k-1) && checaB(k+1, j)) || (checaA(i, k-1) && checaA(k+1, j)) )
                return reduceB[i][j] = true;
        }
    }
    return reduceB[i][j];
}
