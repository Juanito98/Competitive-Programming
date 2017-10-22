#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define LOG_N 21
using namespace std;
int caso = 1;
int n;
int next_[MAXN];

int padre[MAXN];
int raiz(int nodo) {
	if(nodo == padre[nodo]) return nodo;
	return padre[nodo] = raiz(padre[nodo]);
}
void join(int a, int b) {
	if(raiz(a) == raiz(b)) return;
	padre[raiz(a)] = raiz(b);
}

int tam[MAXN]; // te da el tamano de la componente i
int indice[MAXN]; // te da el indice en el ciclo
bool vis[MAXN];

void get_ciclo(int nodo) {
	vis[nodo] = true;
	if(vis[next_[nodo]]) {
		if(indice[next_[nodo]]) return;
		int ini = next_[nodo], fin = nodo, cont = 1;
		indice[ini] = cont;
		do {
			ini = next_[ini];
			cont++;
			indice[ini] = cont;
		} while(ini != fin);
		tam[raiz(nodo)] = cont;
	} else {
		get_ciclo(next_[nodo]);
	}
}

int R[MAXN]; // cual es esa raiz
int nivel[MAXN];
int root(int nodo) {
	if(indice[nodo]) return R[nodo] = nodo; 
	if(!R[nodo]) {
		R[nodo] = root(next_[nodo]);
		nivel[nodo] = nivel[next_[nodo]] + 1;
	}
	return R[nodo];
}
int memo[MAXN];
int d(int nodo) { //distancia de un nodo al nodo mas proximo en el ciclo
	if(indice[nodo]) return 0; 
	if(!memo[nodo]) 
		memo[nodo] = d(next_[nodo]) + 1;
	return memo[nodo];
}

int color[MAXN][LOG_N];
int mem[MAXN][LOG_N];
int DP(int nodo, int k) {
	if(!k) return indice[nodo] ? 0 : next_[nodo];
	if(color[nodo][k] != caso) {
		color[nodo][k] = caso; 
		mem[nodo][k] = DP(DP(nodo, k - 1), k - 1);
	}
	return mem[nodo][k];
}

void salta(int &nodo, int s) {
	int p = 0;
	while(s) {
		if(s & 1) nodo = DP(nodo, p);
		s >>= 1;
		p++;
	}
}

int LCA(int a, int b) {
	if(nivel[a] > nivel[b]) return LCA(b, a);
	if(nivel[a] < nivel[b]) salta(b, nivel[b] - nivel[a]);
	if(a == b) return a;
	for(int i = LOG_N - 1; i >= 0; i--) {
		if(DP(a, i) != DP(b, i)) {
			a = DP(a, i);
			b = DP(b, i);
		}
	}
	return next_[a];
}

int query(int a, int b) {
	if(raiz(a) != raiz(b)) return -1;
	int r1 = root(a), r2 = root(b);
	if(indice[r1] > indice[r2]) {
		swap(r1, r2);
		swap(a, b);
	}
	if(r1 != r2) {
		return d(a) + d(b) + min(indice[r2] - indice[r1], tam[raiz(r1)] + indice[r1] - indice[r2]);
	} else {
		return d(a) + d(b) - 2 * d(LCA(a, b));
	}
}

int main() {
	optimizar;
	int q, a, b;
	while(cin >> n) {
		for(int i = 1; i <= n; i++) {
			vis[i] = false;
			padre[i] = i;
			tam[i] = indice[i] = R[i] = nivel[i] = memo[i] = 0;
		}
		for(int i = 1; i <= n; i++) { 
			cin >> next_[i];
			join(i, next_[i]);
		}
		for(int i = 1; i <= n; i++) {
			if(!tam[raiz(i)]) 
				get_ciclo(i);
		}
		cin >> q;
		for(int i = 1; i <= q; i++) {
			cin >> a >> b;
			cout << query(a, b) << "\n";
		}
		caso++;
	}
	return 0;
}