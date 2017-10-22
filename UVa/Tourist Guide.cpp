#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
using namespace std;
int n, m;
int counth;

map < string, int > mapeo;
bool pto[MAXN];
vector < int > lista[MAXN];
int aux;

int raiz;

int nivel[MAXN];
int articulacion(int nodo, int level) {
	nivel[nodo]=level;
	int x;
	int maxLevel=level-1;

	for(int i=0; i < lista[nodo].size(); i++) {
		if(!nivel[lista[nodo][i]]) {
			x=articulacion(lista[nodo][i], level+1);

            if(x == level && level != 1) {
                if(!pto[nodo])
                    counth++;
                pto[nodo]=true;
            }

			maxLevel= min(maxLevel, x);

			if(nodo == raiz)
				aux++;
		} else {
			maxLevel= min(maxLevel, nivel[lista[nodo][i]]);
		}
	}

	return maxLevel;
}

int main() {
	optimizar;

	cin >> n;
	string palabra;

	map < string, int > :: iterator a;
	map < string, int > :: iterator b;

    int caso=1;

    int x, y;

	while(n != 0) {
		counth=0;
		for(int i=1; i<=n; i++) {
			cin >> palabra;
			mapeo[palabra]=i;
		}

		cin >> m;

		for(int i=1; i<=m; i++) {
			cin >> palabra;
			a = mapeo.find(palabra);
			cin >> palabra;
			b= mapeo.find(palabra);

			x= a -> second;
			y= b -> second;

			lista[x].push_back(y);
			lista[y].push_back(x);
		}

        for(int i=1; i<=n; i++) {
            if(!nivel[i]) {
                aux=0;
                raiz=i;
                articulacion(i, 1);

                if(aux > 1) {
                    pto[i]=true;
                    counth++;
                }
            }
        }

        cout << "City map #" << caso << ": ";
        cout << counth << " camera(s) found\n";

        for(a= mapeo.begin(); a != mapeo.end(); a++) {
            if(pto[a -> second])
                cout << a -> first << '\n';
        }

		aux=0;
		mapeo.clear();

		for(int i=1; i <= n; i++)
            lista[i].clear();

		for(int i=1; i<=n; i++) {
			nivel[i]=0;
			pto[i]=false;
		}

	    cin >> n;
            if(n!=0)
            cout << '\n';

        caso++;
	}
	return 0;
}
