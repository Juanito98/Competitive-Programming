#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 1000002;

int memo[LIMIT];
int cycle_lenght(int n) {
	if(n == 1)
		return 1;
	else {
		if(n < LIMIT) {
			if(!memo[n])
				memo[n] = 1 + (n & 1 ? cycle_lenght(3*n + 1) : cycle_lenght(n >> 1));
			return memo[n];
		} else {
			return 1 + (n & 1 ? cycle_lenght(3*n + 1) : cycle_lenght(n >> 1));
		}
	}

}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b;
	while(cin >> a >> b) {
		int ans = 0;
		int ini = min(a, b), fin = max(a, b);
		for(int i = ini; i <= fin; i++) 
			ans = max(ans, cycle_lenght(i));
		cout << a << " " << b << " " << ans << "\n";
	}
	return 0;
}