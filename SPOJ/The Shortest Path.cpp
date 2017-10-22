#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 10002
#define x first
#define y second
using namespace std;

int n, m;
vector < pair < int, int >  > lista[MAXN];
map < string, int > mapeo;

priority_queue < pair < int, int > > monti; // x -> costo, y -> nodo

bool visitados[MAXN];

void genera( pair < int, int > a ) {
    for(int i=0; i < lista[a.y].size(); i++) {
        if(!visitados[lista[a.y][i].x])
            monti.push( make_pair(a.x + lista[a.y][i].y, lista[a.y][i].x) );
    }
}

int dijkstra(int a, int b) {

    while(!monti.empty())
        monti.pop();

    monti.push( make_pair(0, a) );

    fill(visitados, visitados+n+1, false);

    pair < int, int > aux;
    aux= monti.top();

    while(aux.y != b) {
        monti.pop();
        if(!visitados[aux.y]) {
            visitados[aux.y]= true;
            genera(aux);
        }
        aux= monti.top();
    }

    return aux.x;
}

int main() {
    optimizar;

	int cases;
	string name;
	string uno, dos;

	for(cin >> cases; cases >= 1; cases--) {
        cin >> n;
        for(int i=1; i<=n; i++)
            lista[i].clear();
        mapeo.clear();

        int a, b;
        for(int i=1; i<=n; i++) {
            cin >> name;
            mapeo[name]= i;
            int j;
            for(cin >> j; j >= 1; j--) {
                cin >> a >> b;
                lista[i].push_back( make_pair(a, -b) );
            }
        }

        cin >> m;
        for(int i=1; i<=m; i++) {
            cin >> uno >> dos;
            cout << -dijkstra(mapeo[uno], mapeo[dos]) << "\n";
        }

        if(cases != 1) cout << "\n";
	}

	return 0;
}