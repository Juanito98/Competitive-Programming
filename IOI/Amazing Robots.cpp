#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 25
#define mcm 12
#define x first
#define y second
using namespace std;

int n1, m1;
char maze1[MAXN][MAXN];
bool police1[mcm] [MAXN][MAXN] [mcm + 5];
int g1;

int n2, m2;
char maze2[MAXN][MAXN];
bool police2[mcm] [MAXN][MAXN] [mcm + 5];
int g2;

bool vis[MAXN][MAXN] [MAXN][MAXN] [mcm];

struct ura {
    char x, y;
    char a, b;
    int padre;
    char t;
    char facing;
};
ura cola[MAXN*MAXN*MAXN*MAXN*mcm];
int ini, fin;

bool both_gOut(ura a) {
    return (a.x < 1 || a.x > n1 || a.y < 1 || a.y > m1) && (a.a < 1 || a.a > n2 || a.b < 1 || a.b > m2);
}

bool pegaPoli(ura a) {
    for(int i=1; i<=max(g1, g2); i++) {
        if(police1[i][a.x][a.y][a.t] || police2[i][a.a][a.b][a.t])
            return true;
    }
    return false;
}

void mete(ura a) {
    if(pegaPoli(a))
        return;
    if(vis[a.x][a.y][a.a][a.b][a.t])
        return;
    vis[a.x][a.y][a.a][a.b][a.t] = true;
    cola[++fin] = a;
}

void north(ura a) {
    a.facing = 'N';

    if(a.x >= 1 && a.x <= n1 && a.y >= 1 && a.y <= m1)
        a.x--;
    if(a.a >= 1 && a.a <= n2 && a.b >= 1 && a.b <= m2)
        a.a--;

    if(maze1[a.x][a.y] == '#')
        a.x++;
    if(maze2[a.a][a.b] == '#')
        a.a++;

    for(int i=1; i<=max(g1, g2); i++) {
        if(police1[i][a.x][a.y][(a.t + mcm- 1) % mcm] && police1[i][a.x+1][a.y][a.t])
            return;

        if(police2[i][a.a][a.b][(a.t + mcm- 1) % mcm] && police2[i][a.a+1][a.b][a.t])
            return;
    }

    mete(a);
}
void south(ura a) {
    a.facing = 'S';
    if(a.x >= 1 && a.x <= n1 && a.y >= 1 && a.y <= m1)
        a.x++;
    if(a.a >= 1 && a.a <= n2 && a.b >= 1 && a.b <= m2)
        a.a++;

    if(maze1[a.x][a.y] == '#')
        a.x--;
    if(maze2[a.a][a.b] == '#')
        a.a--;

    for(int i=1; i<=max(g1, g2); i++) {
        if(police1[i][a.x][a.y][(a.t + mcm- 1) % mcm] && police1[i][a.x-1][a.y][a.t])
            return;

        if(police2[i][a.a][a.b][(a.t + mcm- 1) % mcm] && police2[i][a.a-1][a.b][a.t])
            return;
    }

    mete(a);
}
void east(ura a) {
    a.facing = 'E';
    if(a.x >= 1 && a.x <= n1 && a.y >= 1 && a.y <= m1)
        a.y++;

    if(a.a >= 1 && a.a <= n2 && a.b >= 1 && a.b <= m2)
        a.b++;

    if(maze1[a.x][a.y] == '#')
        a.y--;
    if(maze2[a.a][a.b] == '#')
        a.b--;

    for(int i=1; i<=max(g1, g2); i++) {
        if(police1[i][a.x][a.y][(a.t + mcm- 1) % mcm] && police1[i][a.x][a.y-1][a.t])
            return;

        if(police2[i][a.a][a.b][(a.t + mcm- 1) % mcm] && police2[i][a.a][a.b-1][a.t])
            return;
    }

    mete(a);
}
void west(ura a) {
    a.facing = 'W';
    if(a.x >= 1 && a.x <= n1 && a.y >= 1 && a.y <= m1)
        a.y--;

    if(a.a >= 1 && a.a <= n2 && a.b >= 1 && a.b <= m2)
        a.b--;

    if(maze1[a.x][a.y] == '#')
        a.y++;
    if(maze2[a.a][a.b] == '#')
        a.b++;

    for(int i=1; i<=max(g1, g2); i++) {
        if(police1[i][a.x][a.y][(a.t + mcm- 1) % mcm] && police1[i][a.x][a.y+1][a.t])
            return;

        if(police2[i][a.a][a.b][(a.t + mcm- 1) % mcm] && police2[i][a.a][a.b+1][a.t])
            return;
    }

    mete(a);
}


int busca() {
    bool yaLlegue = false;
    ura edo;
    int t = 0;
    int tam;
    while(ini < fin && !yaLlegue && t <= 10000) {
        for(tam = fin - ini; tam >= 1; tam--) {
            edo = cola[++ini];
            if(both_gOut(edo)) {
                yaLlegue = true;
                break;
            }
            edo.t ++;
            edo.t%= mcm;
            edo.padre = ini;
            north(edo);
            south(edo);
            east(edo);
            west(edo);
        }
        if(!yaLlegue) t++;
    }

    if(yaLlegue) return t;
    return -1;
}

void simula(int lab, int a, int b, int c, char orientacion) {
    int i = 0;
    int pasos = 0;
    while(i < mcm) {

        if(lab == 1) {
            police1[g1][a][b][i] = true;
        } else {
            police2[g2][a][b][i] = true;
        }
        i++;
        pasos++;

        if(orientacion == 'N') a--;
        if(orientacion == 'S') a++;
        if(orientacion == 'E') b++;
        if(orientacion == 'W') b--;

        if(pasos == (c-1)) {
            if(orientacion == 'N') {
                orientacion = 'S';
            } else {
                if(orientacion == 'S')
                    orientacion = 'N';
            }
            if(orientacion == 'E') {
                orientacion = 'W';
            } else {
                if(orientacion == 'W')
                    orientacion = 'E';
            }
            pasos = 0;
        }
    }
}

void lee() {
    pair < char, char > robot;
    int g;
    int a, b, c;
    char orientacion;

    cin >> n1 >> m1;
    for(int i=1; i<=n1; i++)
        for(int j=1; j<=m1; j++) {
            cin >> maze1[i][j];
            if(maze1[i][j] == 'X')
                robot = make_pair(i, j);
        }
    cin >> g;
    for(g1=1; g1<=g; g1++) {
        cin >> a >> b >> c >> orientacion;
        simula(1, a, b, c, orientacion);
    }
    cola[++fin].x = robot.x;
    cola[fin].y = robot.y;


    cin >> n2 >> m2;
    for(int i=1; i<=n2; i++)
        for(int j=1; j<=m2; j++) {
            cin >> maze2[i][j];
            if(maze2[i][j] == 'X')
                robot = make_pair(i, j);
        }
    cin >> g;
    for(g2=1; g2<=g; g2++) {
        cin >> a >> b >> c >> orientacion;
        simula(2, a, b, c, orientacion);
    }
    cola[fin].a = robot.x;
    cola[fin].b = robot.y;

    cola[fin].padre = -1;
    g1--, g2--;
}

void imprime(int nodo) {
    if(cola[nodo].padre != -1) {
        imprime(cola[nodo].padre);
        cout << cola[nodo].facing << "\n";
    }
}

int main()
{
    optimizar;

    lee();

    int resp = busca();
    cout << resp << "\n";
    if(resp != -1)
        imprime(ini);

    return 0;
}
