#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1002
using namespace std;
int n;
bool camino[MAXN][MAXN];

bool vis[MAXN][MAXN][6];
bool memo[MAXN][MAXN][6];

int pred(int a) {
    if(a == 1) return n;
    return a - 1;
}

int next(int a) {
    return (a % n) + 1;
}

bool any_path(int x, int i, int j) {
    return camino[x][i] || camino[x][j];
}

bool useI(int a) {
    return a & 1;
}
bool useJ(int a) {
    return a & 2;
}


bool yaLlegue(int i, int j, bool ImIzq) {
    if(next(i) == j)
        return true;

    if(!vis[i][j][ImIzq]) {
        if(ImIzq) {
            if(camino[i][next(i)]) {
                if(yaLlegue(next(i), j, 1)) {
                    cout << next(i) << "\n";
                    return true;
                }
            }
            if(camino[i][pred(j)]) {
                if(yaLlegue(i, pred(j), 0)) {
                    cout << pred(j) << "\n";
                    return true;
                }
            }
        } else {
            if(camino[j][next(i)]) {
                if(yaLlegue(next(i), j, 1)) {
                    cout << next(i) << "\n";
                    return true;
                }
            }
            if(camino[j][pred(j)]) {
                if(yaLlegue(i, pred(j), 0)) {
                    cout << pred(j) << "\n";
                    return true;
                }
            }
        }
        vis[i][j][ImIzq] = true;
    }

    return false;
}

int main()
{
    optimizar;
    cin >> n;
    int a, b;
    int c;
    for(cin >> c; c >= 1; c--) {
        cin >> a >> b;
        camino[a][b] = true;
        camino[b][a] = true;
    }
    bool impreso = false;
    for(int i=1; i<=n; i++) {
        if(yaLlegue(i, i, 0)) {
            cout << i << "\n";
            impreso = true;
            break;
        }
    }

    if(!impreso)
        cout << "-1\n";

    return 0;
}