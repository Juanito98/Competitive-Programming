#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 62
using namespace std;
int caso;
int n, m;
int C[MAXN][MAXN];
vector < int > lista[MAXN];

int costo[MAXN]; // costo al padre
int hijo[MAXN]; // el hijo mas a la izquierda
int hermano[MAXN]; // siguiente hermano a la derecha

int vis[MAXN];
void recorre(int nodo) {
	vis[nodo] = caso;
	for(int i = 0; i < lista[nodo].size(); i++) {
		if(vis[lista[nodo][i]] == caso) continue;
		if(!hijo[nodo]) hijo[nodo] = lista[nodo][i];
		else {
			hermano[lista[nodo][i]] = hijo[nodo];
			hijo[nodo] = lista[nodo][i];
		}
		costo[lista[nodo][i]] = C[nodo][lista[nodo][i]];
		recorre(lista[nodo][i]);
	}
}

int color[MAXN][MAXN][3];
int memo[MAXN][MAXN][3];
int DP(int nodo, int k, int suben) {
	if(k < 0 || suben < 0) return -60000;
	if(!nodo) return 0;
	if(color[nodo][k][suben] != caso) {
		color[nodo][k][suben] = caso;
		int mayor = -60000;
		for(int _k = 0; _k <= k; _k++) {
			// no subo
			mayor = max(mayor, DP(hijo[nodo], _k, 0) + DP(hermano[nodo], k - _k, suben));
			mayor = max(mayor, DP(hijo[nodo], _k - 1, 1) + DP(hermano[nodo], k - _k, suben));
			mayor = max(mayor, DP(hijo[nodo], _k - 1, 2) + DP(hermano[nodo], k - _k, suben));
			
			if(!suben) continue; 
			// subo
			mayor = max(mayor, DP(hijo[nodo], _k, 0) + DP(hermano[nodo], k - _k, suben - 1) + costo[nodo]);
			mayor = max(mayor, DP(hijo[nodo], _k, 1) + DP(hermano[nodo], k - _k, suben - 1) + costo[nodo]);
		}
		memo[nodo][k][suben] = mayor;
	}
	return memo[nodo][k][suben];
}

int main() {
	optimizar;
	int a, b, c;
	for(cin >> caso; caso; caso--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			lista[i].clear();
			costo[i] = hijo[i] = hermano[i] = 0;
		}
		for(int i = 1; i < n; i++) {
			cin >> a >> b >> c;
			lista[a].push_back(b);
			lista[b].push_back(a);
			C[a][b] = C[b][a] = c;
		}
		recorre(1);
		cout << DP(1, m, 0) << "\n";
	}
	return 0;
}