#include <iostream>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define lld long long int
using namespace std;

int n;
int arr[MAXN];
int sum[MAXN];

struct BIT {
	int tree[MAXN * 3];
	int tam = MAXN * 3;

	void update(int a, int v) {
		a+= MAXN;
		while(a < tam) {
			tree[a]+= v;
			a+= a&(-a);
		}
	}

	int query(int a) {
		a+= MAXN;
		a = min(a, tam - 1);
		int c = 0;
		if(a < 0) return 0;
		while(a) {
			c+= tree[a];
			a-= a&(-a);
		}
		return c;
	}

	int query(int i, int j) {
		return query(j) - query(i - 1);
	}
};
BIT bit;

int main() {
	optimizar;
	int k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
		arr[i] = arr[i] < k ? -1 : 1; 
		sum[i] = arr[i] + sum[i - 1];
	}
	lld resp = 0;
	for(int i = n; i >= 1; i--) {
		bit.update(sum[i], 1);
		resp+= bit.query(sum[i-1], MAXN);
	}
	cout << resp << "\n";
	return 0;
}