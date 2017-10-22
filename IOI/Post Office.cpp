#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define INF (1 <<30)
#define MAXN 302
#define MAX_P 32
using namespace std;

int n, m;

bool visitados[MAXN][MAXN][MAX_P];
int suma[MAXN];
int arr[MAXN];

int memo[MAXN][MAXN][MAX_P];

int f(int i, int j, int med) {
    return (suma[med] - suma[i]) - ((med - i) * arr[i])
            + ((j - med - 1) * arr[j]) - (suma[j-1] - suma[med]);
}

int aux;
int binSearch(int a, int b) {

    if(b - a < 1)
        return 0;

    int ini = a;
    int fin = b;
    int med;

    while(ini < fin) {
        med= (ini + fin + 1) / 2;
        if(arr[med] - arr[a] > arr[b] - arr[med])
            fin = med - 1;
        else
            ini = med;

    }

    return f(a, b, ini);
}

int DP(int ant, int i, int k) {
    if(k == 0 || i == n) {
        memo[ant][i][k] = binSearch(ant, n);
        return memo[ant][i][k];
    }

    if(k == 0 || i > n)
        return n;

    if(!visitados[ant][i][k]) {
        visitados[ant][i][k] = true;

        int nToma = DP(ant, i+1, k);
        int toma = binSearch(ant, i);
        toma+= DP(i, i+1, k-1);

        memo[ant][i][k] = min(toma, nToma);
    }
    return memo[ant][i][k];
}

int main() {
	optimizar;

    cin >> n >> m;
    arr[0] = -10000;
    suma[0] = arr[0];
    for(int i=1; i<=n; i++) {
        cin >> arr[i];
        suma[i]= arr[i] + suma[i-1];
    }

    arr[++n]= 20000;
    suma[n]= arr[n] + suma[n-1];

    cout << DP(0, 1, m) << "\n";

    int ant = 0, i = 1, k = m;

    while(i < n || k > 0) {
        if(memo[ant][i][k] == memo[ant][i+1][k]) {
            i++;
        } else {
            cout << arr[i] << " ";
            ant = i;
            i++;
            k--;

        }
    }

    cout << "\n";

	return 0;
}
