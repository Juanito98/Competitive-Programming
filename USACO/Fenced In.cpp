#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 100002
using namespace std;

lld resp;

lld n, m;
lld a, b;

lld V[MAXN];
lld H[MAXN];

int topeA, topeB;

lld vert, hori;
lld countV, countH;

int main() {
	freopen("fencedin.in", "r", stdin);
	freopen("fencedin.out", "w", stdout);
	optimizar;
	cin >> n >> m >> a >> b;
	
	for(int i = 0; i < a; i++) 
		cin >> V[i];
	V[a] = n;
	V[a + 1] = (1 << 30);

	for(int i = 0; i < b; i++) 
		cin >> H[i];
	H[b] = m;
	H[b + 1] = (1 << 30); 
	
	sort(V, V + a + 1);
	sort(H, H + b + 1);
	
	for(int i = a; i >= 1; i--) 
		V[i]-= V[i - 1];
	
	for(int i = b; i >= 1; i--) 
		H[i]-= H[i - 1];
	
	sort(V, V + a + 1);
	sort(H, H + b + 1);
	
	while(topeA <= a || topeB <= b) {
		if(V[topeA] < H[topeB]) {
			resp+= (hori + b - countH) * V[topeA];
			vert++;
			if(hori) vert = 1;
			countV++;
			if(hori > 1) hori = 1;
			topeA++;
		} else {
			resp+= (vert + a - countV) * H[topeB];
			hori++;
			if(vert) hori = 1;
			countH++;
			if(vert > 1) vert = 1;
			topeB++;
		}
	}
	
	cout << resp << "\n";
	return 0;
}