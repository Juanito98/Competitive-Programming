#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define llf long double
using namespace std;
const int MAXN = 100002;

int n;
int padre[MAXN];
int color[MAXN];
bool vis[MAXN];
vector < int > lista[MAXN];
map < pair < int, int >, int > puntos;

llf dist(pair < llf, llf > P, pair < llf, llf > Q) {
    return sqrt((P.first - Q.first) * (P.first - Q.first) + (P.second - Q.second) * (P.second - Q.second));
}

void join(int a, int b) {
    lista[a].push_back(b);
    lista[b].push_back(a);
}

int t = 0;
int unos = 0;
void colorea(int nodo, int c) {
    t++;
    if(c) { unos++; color[nodo] = 1; }
    vis[nodo] = true;
    for(int i = 0; i < lista[nodo].size(); i++)
        if(!vis[lista[nodo][i]]) colorea(lista[nodo][i], c^1);
}

int main()
{
    optimizar;
    int x, y;
    map < pair < int, int >, int > :: iterator it;
    while(cin >> n) {
        for(int i = 1; i <= n; i++) {
            padre[i] = i;
            lista[i].clear();
            color[i] = 0;
            vis[i] = false;
        }
        for(int i = 1; i <= n; i++) {
            cin >> x >> y;
            for(int k = -5; k <= 5; k++) {
                for(int l = -5; l <= 5; l++) {
                    it = puntos.find(make_pair(x + k, y + l));
                    if(it == puntos.end()) continue;
                    if(dist(make_pair(x, y), it -> first) <= 5.0) join(i, it -> second);
                }
            }
            puntos[make_pair(x, y)] = i;
        }
        puntos.clear();
        int r = 0;
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                t = unos = 0;
                colorea(i, 1);
                if(unos > t - unos) unos = t - unos;
                r += unos;
            }
        }
        cout << r << "\n";
    }
    return 0;
}
