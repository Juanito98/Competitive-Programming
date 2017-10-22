#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1002
using namespace std;
int caso = 1;
int n;
int arr[MAXN][MAXN];
int suma[MAXN][MAXN];

int vis[MAXN][MAXN];
int memo[MAXN][MAXN];
int DP(int i, int j) {
	if(i < 1 || j > n) return 0;
	if(vis[i][j] != caso) {
		vis[i][j] = caso;
		memo[i][j] = max(DP(i - 1, j), DP(i, j + 1) + suma[i][j]);
	}
	return memo[i][j];
}

int main() {
	optimizar;
	while(cin >> n) {
		if(!n) break;
		
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= i; j++) 
				cin >> arr[i - j + 1][j];
		
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++) 
				suma[i][j] = arr[i][j] + suma[i-1][j];
		
		cout << DP(n, 1) << "\n";
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				arr[i][j] = suma[i][j] = 0;
			}
		caso++;
	}
	return 0;
}