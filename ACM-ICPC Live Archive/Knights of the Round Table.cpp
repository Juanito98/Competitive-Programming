//#include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <math.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 2000002
#define lld long long int
using namespace std;
const lld M = 1000000007;
int n, k;
int arr[MAXN];
int asiento[MAXN];
bool sentado[MAXN];
bool ocupado[MAXN];

int raiz(int nodo) {
    if(asiento[nodo] == nodo) return nodo;
    return asiento[nodo] = raiz(asiento[nodo]);
}
void join(int a, int b) {
    if(raiz(a) == raiz(b)) return;
    asiento[raiz(a)] = raiz(b);
}

int solve() {
    int mayor = 0;
    int ind;
    int i, j, flechas;
    for(i = 1; i <= n * 2; i = j + 1) {
        flechas = arr[i];
        for(j = i; j <= n * 2 && flechas > j - i + 1; flechas += arr[++j]);
        if(j - i + 1 > mayor) {
            ind = i;
            mayor = j - i + 1;
        }
    }
    flechas = 0;
    lld r = 1;
    for(i = 1; i <= n; i++, ind++) {
        flechas += arr[ind];
        if(!ocupado[ind]) r *= flechas;
        r %= M;
        flechas--;
    }
    return r;
}

int main()
{
    optimizar;
    int a, b;
    while(cin >> n >> k) {
        for(int i = 1; i <= n * 2; i++) {
            asiento[i] = i;
            sentado[i] = false;
            ocupado[i] = false;
            arr[i] = 0;
        }
        for(int i = 1; i <= k; i++) {
            cin >> a >> b;
            join(b, b == n ? 1 : b + 1);
            sentado[a] = sentado[a + n] = true;
            arr[b]++; arr[b + n]++;
            ocupado[b] = ocupado[b + n] = true;
        }
        for(int i = 1; i <= n; i++) 
            if(!sentado[i]) {
                arr[raiz(i)]++; arr[raiz(i) + n]++;
            }
        cout << solve() << "\n";
    }
    return 0;
}