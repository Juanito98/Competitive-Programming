#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;

int n;
int memo[2][4][4][4][4];
int arr[100002];

char c;

int f(int a, int b, int c) {
	int sum = 0;
	
	for(int i = 1; i <= 3; i++)
		if( a == i || b == i || c == i )
			sum++;

	return sum;
}

 

int main(){
	optimizar;
	cin >> n;

	for( int i = 1; i <= n; i++ ){
		cin >> c;
		if(c == 'M') arr[i] = 1;
		if(c == 'B') arr[i] = 2;
		if(c == 'F') arr[i] = 3;
	}
	
	int ant = 0, act = 1;

	for(int i = n; i >= 1; i--){
		swap( ant, act );
		for(int x = 0; x <= 3; x++)
			for(int y = 0; y <= 3; y++)
				for(int r = 0; r <= 3; r++)
					for(int s = 0; s <= 3; s++)
						memo[ant][x][y][r][s] = max( memo[act][y][arr[i]][r][s] + f(x, y, arr[i]), memo[act][x][y][s][arr[i]] + f(r, s, arr[i]));
	}

	cout << memo[ant][0][0][0][0] << "\n";

	

	return 0;

	

}
