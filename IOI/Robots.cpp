#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;

int n;
pair < int, int > arr[1000002];

vector < int > r_w;
vector < int > r_v;

bool valido(int t) {
	priority_queue < int > monti; // guarda s
	int ind = 0;
	for(int i = 1; i <= n; i++) {
		while(ind < r_w.size() && arr[i].first >= r_w[ind]) {
			for(int j = 1; j <= t; j++) {
				if(monti.empty()) break;
				monti.pop();
			}
			ind++;
		}
		monti.push(arr[i].second);
	}
	
	while(ind < r_w.size()) {
		for(int j = 1; j <= t; j++) {
			if(monti.empty()) break;
			monti.pop();
		}
		ind++;
	}
	
	if(monti.empty()) return true;
	
	for(int i = r_v.size() - 1; i >= 0; i--) {
		if(monti.top() >= r_v[i]) return false;
		for(int j = 1; j <= t; j++) {
			monti.pop();
			if(monti.empty()) return true;
		}
	}
	return monti.empty();
}

int binSearch(int ini, int fin) {
	int med;
	while(ini < fin) {
		med = (ini + fin) / 2;
		if(valido(med)) {
			fin = med;
		} else {
			ini = med + 1;
		}
	}
	return ini;
}

int main() {
	optimizar;
	int A, B;
	int aux;
	cin >> A >> B >> n;
	for(int i = 1; i <= A; i++) { cin >> aux; r_w.push_back(aux); }
	for(int i = 1; i <= B; i++) { cin >> aux; r_v.push_back(aux); }
	for(int i = 1; i <= n; i++) cin >> arr[i].first >> arr[i].second;
	
	sort(r_w.begin(), r_w.end());
	sort(r_v.begin(), r_v.end());
	sort(arr + 1, arr + n + 1);
	
	int x = binSearch(1, n + 1);
	if(x > n) {
		cout << "-1\n";
	} else {
		cout << x << "\n";
	}
	return 0;
}
