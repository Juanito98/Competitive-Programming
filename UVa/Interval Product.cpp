#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
using namespace std;
int n, Q;

int BIT[MAXN];
int arr[MAXN];
bool iszero[MAXN];
int ceros[MAXN];

int transforma(int a) {
	if(a == 0) return 0;
	if(a < 0) return -1;
	return 1;
} 

void updateCeros(int a, int val) {
	while(a <= n) {
		ceros[a]+= val;
		a+= a & (-a);
	}
}

int sumaCeros(int a) {
	int r=0;
	while(a) {
		r+= ceros[a];
		a-= a&(-a);
	}
	return r;
}

int queryCeros(int i, int j) {
	return sumaCeros(j) - sumaCeros(i-1);
}

int lol;

void update(int a, int val) {
	if(val == 0) {
		if( !iszero[a] ) {
			iszero[a]=true;
			updateCeros(a, 1);
		}
		return;
	} else {
		if( iszero[a] ) {
			iszero[a]=false;
			updateCeros(a, -1);
		}
		lol= val;
		val*= arr[a];
		arr[a]= lol;
	}
	
	while(a <= n) {
		BIT[a]*= val;
		a+= a & (-a);
	}
}

int suma(int a) {
	int r=1;
	while(a) {
		r*= BIT[a];
		a-= a&(-a);
	}
	return r;
}

int query(int i, int j) {
	return suma(j) / suma(i-1);
}

 
int main() {
	optimizar;
	
	int aux;
	int a, b;
	char q;
	
	while( cin >> n ) {
		cin >> Q;
		
		fill(arr,arr+n+2, 1);
		fill(BIT, BIT+n+2, 1);	
		fill(ceros, ceros+n+2, 0);
		fill(iszero, iszero+n+2, false);	
		
		for(int i=1; i<=n; i++) {
			cin >> aux;
			update(i, transforma(aux));
		}
		
		for(int i=1; i<=Q; i++) {
			cin >> q;
			cin >> a >> b;
			if(q == 'C') {
				update(a, transforma(b));
			} else {
				if( queryCeros(a, b) ) {
					cout << "0";
				} else {
					a= query(a, b);
					if(a > 0) cout << "+";
					if(a < 0) cout << "-";
				}
			}
		}
		
		cout << "\n";
	}
	return 0;
}