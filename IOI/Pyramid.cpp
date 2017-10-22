#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0);cin.tie(0);
#define lld long long int
#define INF (1 << 30)
#define MAXN 1002
using namespace std;

lld _min(lld a, lld b) {
    if(a == 0) return b == 0 ? INF : b;
    if(b == 0) return a;
    return a < b ? a : b;
}

int N, M;

int n, m;
lld arr[MAXN][MAXN];
lld suma[MAXN][MAXN];

lld izq[MAXN];
lld der[MAXN];
lld arriba[MAXN];
lld abajo[MAXN];
lld menor[MAXN][MAXN];

int x, y;
int a, b;

lld sum(int x1, int y1, int x2, int y2) {
    return suma[x2][y2] + suma[x1-1][y1-1] - (suma[x2][y1-1] + suma[x1-1][y2]);
}

void barrido_Nieves() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1 + M; j <= m; j+= M + 1) {
            izq[j] = der[j] = arr[i][j];
            for(int j1 = 1; j1 <= M && j + j1 <= m; j1++) {
                der[j-j1] = _min(der[j-j1+1], arr[i][j-j1]);
                izq[j+j1] = _min(izq[j+j1-1], arr[i][j+j1]);
            }
        }
        for(int j=1; j + M <= m; j++)
            menor[i][j] = _min(der[j], izq[j+M]);
    }

    for(int j=1; j<=m; j++) {
        for(int i = N + 1; i <= n; i+= N+1) {
            arriba[i] = abajo[i] = menor[i][j];
            for(int i1 = 1; i1 <= N && i1 + i <= n; i1++) {
                abajo[i-i1] = _min(menor[i-i1][j], abajo[i-i1+1]);
                arriba[i+i1] = _min(menor[i+i1][j], arriba[i+i1-1]);
            }
        }
        for(int i=1; i + N <=n; i++)
            menor[i][j] = _min(abajo[i], arriba[i+N]);
    }
}

void calcula() {
    for(int i = 1; i <= n - a + 1; i++)
        for(int j = 1; j <= m - b + 1; j++)
            arr[i][j] = sum(i, j, i + a-1, j + b-1);

}

lld mayor = -1;
int respX, respY;

void barrido(int i) {
    int j = 1;
    int cont;
    while(j + y - 1 <= m) {
        cont = sum(i, j, i+x-1, j+y-1) - menor[i+1][j+1];
        if(cont > mayor) {
            mayor = cont;
            respX = i, respY = j;
        }
        j++;
    }
}

int main() {
    optimizar;
    cin >> n >> m;
    cin >> x >> y;
    cin >> a >> b;
    swap(n, m), swap(x, y), swap(a, b);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++) {
            cin >> arr[i][j];
            suma[i][j] = sum(1, 1, i-1, j) + sum(i, 1, i, j-1) + arr[i][j];
        }

    N = x - a - 2;
    M = y - b - 2;

    calcula();
    barrido_Nieves();

    for(int i=1; i+x-1<=n; i++)
        barrido(i);

    cout << respY << " " << respX << "\n";
    int i = respX + 1, j = respY + 1;
    while(arr[i][j] != menor[respX+1][respY+1]) {
        j++;
        if(j > respY+1+M) {
            j = respY+1;
            i++;
        }
    }
    cout << j << " " << i << "\n";

    return 0;
}
