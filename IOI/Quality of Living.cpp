#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 3002
using namespace std;
int n, m;
int r, c;
int arr[MAXN][MAXN];
int pre[MAXN][MAXN];

int query(int x1, int y1, int x2, int y2) {
    if(x1 > x2 || y1 > y2) return 0;
    return pre[x2][y2] + pre[x1 - 1][y1 - 1] - pre[x2][y1 - 1] - pre[x1 - 1][y2];
}
void genera(int x) {
	int aux;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			aux = 0;
			if(arr[i][j] < x) aux = -1;
			if(arr[i][j] > x) aux = 1;
			pre[i][j] = aux + pre[i-1][j] + query(i, 1, i, j-1);
		}
	}
}

bool median_is_smaller() {
	for(int i = r; i <= n; i++) {
		for(int j = c; j <= m; j++) {
			if(query(i - r + 1, j - c + 1, i, j) < 0) return true;
		}
	}
	return false;
}

int binSearch(int ini, int fin) {
	int med;
	while(ini < fin) {
		med = (ini + fin + 1) / 2;
		genera(med);
		if(median_is_smaller()) {
			fin = med - 1;
		} else {
			ini = med;
		}
	}
	return ini;
}

int main() {
	optimizar;
	cin >> n >> m;
	cin >> r >> c;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> arr[i][j];
	cout << binSearch(1, n * m) << "\n";
	return 0;
}
