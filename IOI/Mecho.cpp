#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 802
#define lld long long int
#define x first
#define y second
using namespace std;

int n;
lld S;
char arr[MAXN][MAXN];
int corto[MAXN][MAXN];

queue < pair < int, int > > cola;
pair < int, int > edoFinal;
pair < int, int > edoInicial;

int vis[MAXN][MAXN];
int color;

void expand(int x, int y) {
    if(x > n || y > n || x < 1 || y < 1)
        return;
    if(arr[x][y] == 'T' || arr[x][y] == 'D')
        return;
    if(vis[x][y] == color)
        return;

    vis[x][y] = color;
    cola.push( make_pair(x, y) );
}

void expand_bees() {
    color++;
    pair < int, int > edo;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            corto[i][j] = -1;
            if(arr[i][j] == 'H') {
                cola.push(make_pair(i, j));
                vis[i][j] = color;
            }
        }
    }

    int t = 0;
    int tam;
    while(!cola.empty()) {
        for(tam = cola.size(); tam >= 1; tam--) {
            edo = cola.front();
            corto[edo.x][edo.y] = t;

            expand(edo.x + 1, edo.y);
            expand(edo.x - 1, edo.y);
            expand(edo.x, edo.y + 1);
            expand(edo.x, edo.y - 1);

            cola.pop();
        }
        t++;
    }
}

void genera(int x, int y, lld t) {
    if(x > n || y > n || x < 1 || y < 1)
        return;
    if(arr[x][y] == 'T')
        return;
    if(vis[x][y] == color)
        return;

    if(x != edoFinal.x || y != edoFinal.y)
        if( (t / S) >= corto[x][y] )
            return;

    vis[x][y] = color;
    cola.push( make_pair(x, y) );
}

bool can_arrive(lld t) {
    t*=S;
    while(!cola.empty())
        cola.pop();

    color++;
    pair < int, int > edo;
    genera(edoInicial.x, edoInicial.y, t);
    int tam;
    while(!cola.empty()) {
        for(tam = cola.size(); tam >= 1; tam--) {
            edo = cola.front();
            cola.pop();
            if(edo == edoFinal) return true;

            genera(edo.x + 1, edo.y, t+1);
            genera(edo.x - 1, edo.y, t+1);
            genera(edo.x, edo.y + 1, t+1);
            genera(edo.x, edo.y - 1, t+1);
        }
        t++;
    }
    return false;
}

int binSearch(int ini, int fin) {
    expand_bees();
    int med;

    if(!can_arrive(0))
        return -1;

    while(ini < fin) {
        med = (ini + fin + 1) / 2;
        if(can_arrive(med)) {
            ini = med;
        } else {
            fin = med - 1;
        }
    }
    return ini;
}

int main()
{
    optimizar;

    cin >> n >> S;
    char aux;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> aux;

            if(aux == 'M')
                edoInicial = make_pair(i, j);

            if(aux == 'D')
                edoFinal = make_pair(i, j);

            arr[i][j] = aux;
        }
    }

    cout << binSearch(0, n * n) << "\n";

    return 0;
}
