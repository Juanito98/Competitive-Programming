#include <bits/stdc++.h>
using namespace std;

int mov[8][2] = {
-1, -1, 
-1, 0, 
-1, 1, 
0, -1, 
0, 1,
1, -1,
1, 0, 
1, 1
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	int cnt = 0;
	do {
		cin >> n >> m;
		cnt++;
		if(!n || !m) continue;
		int arr[n][m];
		for(int i = 0; i < n; i++) fill(arr[i], arr[i] + m, 0);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				char c;
				cin >> c;
				if(c == '*') {
					arr[i][j] = 10;
					for(int k = 0; k < 8; k++) {
						int x = i + mov[k][0], y = j + mov[k][1];
						if(x >= 0 && x < n && y >= 0 && y < m)
							arr[x][y]++;
					}
				}
			}
		}
		if(cnt > 1) cout << "\n";
		cout << "Field #" << cnt << ":\n";
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++)
				if(arr[i][j] < 10) 
					cout << arr[i][j];
				else cout << "*";
			cout << "\n";
		}

	} while(n > 0 || m > 0);
	return 0;
}