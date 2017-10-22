#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define INF (1 << 30)
#define MAXN 10
using namespace std;

int corto[MAXN][MAXN] [MAXN][MAXN];
int suma[MAXN][MAXN];

int menor = INF;

struct ura {
    int x, y;
};
ura caballo[MAXN*MAXN];
int tope;
ura rey;

ura coordenada(char a, char b) {
    ura pto;
    pto.x = a - 'A' + 1;
    pto.y = b - '0';
    return pto;
}

queue < ura > cola;
int vis[MAXN][MAXN];
int color;

void checa(int i, int j) {
    if(i > 8 || i < 1 || j > 8 || j < 1)
        return;
    if(vis[i][j] == color)
        return;

    vis[i][j] = color;
    ura a;
    a.x = i;
    a.y = j;
    cola.push(a);
}

void genera(ura a) {
    checa(a.x + 2, a.y + 1);
    checa(a.x + 2, a.y - 1);
    checa(a.x - 2, a.y + 1);
    checa(a.x - 2, a.y - 1);

    checa(a.x + 1, a.y + 2);
    checa(a.x + 1, a.y - 2);
    checa(a.x - 1, a.y + 2);
    checa(a.x - 1, a.y - 2);
}

void rellena(int i, int j) {
    color++;
    int t = 0;
    int tam;
    ura edo;
    checa(i, j);
    while(!cola.empty()) {
        for(tam = cola.size(); tam >= 1; tam--) {
            edo = cola.front();
            corto[i][j] [edo.x][edo.y] = t;
            corto[edo.x][edo.y] [i][j] = t;
            genera(edo);
            cola.pop();
        }
        t++;
    }
}

int camino(int k, int i, int j) {
    return corto[caballo[k].x][caballo[k].y] [i][j] + max(abs(rey.x - i), abs(rey.y - j));
}

void solve() {
    int aux;

    for(int i=1; i<=8; i++)
        for(int j=1; j<=8; j++) {
            aux = 0;
            rellena(i, j);
            for(int k=1; k<=tope; k++)
                aux+= corto[caballo[k].x][caballo[k].y] [i][j];

            suma[i][j] = aux;
        }

    for(int i=1; i<=8; i++) {
        for(int j=1; j<=8; j++) {
            aux = suma[i][j];
            for(int k=1; k<=tope; k++) {
                aux-= corto[caballo[k].x][caballo[k].y] [i][j];
                for(int a=1; a<=8; a++) {
                    for(int b=1; b<=8; b++)
                        menor = min(menor,  aux + camino(k, a, b) + corto[i][j] [a][b]);
                }
                aux+= corto[caballo[k].x][caballo[k].y] [i][j];
            }
        }
    }
}

int main()
{
    optimizar;

    string ent;
    cin >> ent;

    if(ent.size()) {
        rey = coordenada(ent[0], ent[1]);
        for(int i = 2; i<ent.size(); i+=2)
            caballo[++tope] = coordenada(ent[i], ent[i+1]);

        solve();
        cout << menor << "\n";
    }

    return 0;
}
