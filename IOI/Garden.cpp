#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define INF (1 << 30)
#define MAXN 252
using namespace std;
int n, m;
int k;

int rosas[MAXN][MAXN];

int arriba[MAXN];
int izq[MAXN];

int query(int x1, int x2, int y1, int y2) {
    return (rosas[x2][y2] + rosas[x1-1][y1-1]) - (rosas[x2][y1-1] + rosas[x1-1][y2]);
}

void precalcula() {
    int suma = 0;
    for(int i=1; i<=n; i++) {
        suma = 0;
        for(int j=1; j<=m; j++) {
            suma+= rosas[i][j];
            rosas[i][j] = suma + rosas[i-1][j];
        }
    }
}

int p(int x1, int x2, int y1, int y2) {
    return (2*(x2-x1 + 1)) + (2*(y2-y1 + 1));
}

int resp = INF;

void barrido(int i1, int i2, bool make_rectangles) {
    int j1 = 1;
    int j2 = 1;
    int suma = query(i1, i2, j1, j2);
    int perimetro;
    while(j2 <= m) {
        if(suma == k) {
            perimetro = p(i1, i2, j1, j2);
            if(make_rectangles) {
                arriba[i2] = min(arriba[i2], perimetro);
                izq[j2] = min(izq[j2], perimetro);
            } else {
                resp = min(resp, perimetro + min(arriba[i1-1], izq[j1-1]));
            }
            j1++;
        } else {
            if(suma > k) {
                j1++;
            } else {
                j2++;
            }
        }
        suma = query(i1, i2, j1, j2);
    }
}

void genera(bool make_rectangles) {
    for(int i=1; i<=n; i++) {
        for(int j=i; j<=n; j++) {
            barrido(i, j, make_rectangles);
        }
    }
}

int main()
{
    optimizar;
    cin >> n >> m;
    int nRosas;
    cin >> nRosas >> k;
    int a, b;
    for(int i = 1; i <= nRosas; i++) {
        cin >> a >> b;
        rosas[a][b]++;
    }

    precalcula();
    for(int i=0; i<= max(n, m); i++) {
        arriba[i] = INF;
        izq[i] = INF;
    }
    genera(true);
    for(int i=1; i<= max(n, m); i++) {
        arriba[i] = min(arriba[i], arriba[i-1]);
        izq[i] = min(izq[i], izq[i-1]);
    }
    genera(false);

    if(resp < INF)
        cout << resp << "\n";
    else
        cout << "NO\n";
    return 0;
}
