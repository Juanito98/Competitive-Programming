#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
using namespace std;

int n;

lld A, B;

lld entra(lld pos) {
	if(A <= pos && B >= pos)  return 0;
	if(A > pos)
		return pos - A;
	else
		return pos - B;
}

void update(lld x) {
	lld ini = x;
	lld fin = (1 << 30);
	fin*= fin;
	ini+= entra(ini);
	fin+= entra((2 * x) - fin);
	A = ini;
	B = fin;
	if(A < x || B < x)
        B = A - 1;
}

int main() {
	optimizar;
	cin >> n;
	int act;
	cin >> act;
	A = act;
	B = (1 << 30);
	B*= B;
	for(int i=1; i<n; i++) {
		cin >> act;
		update(act);
		if(B < A) break;
	}
	if(B < A)
		cout << "0\n";
	else
		cout << B - A + 1 << "\n";
    return 0;
}
