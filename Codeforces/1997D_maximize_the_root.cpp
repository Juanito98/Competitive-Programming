#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

int f(int nodo, const vector<int> &arr, const vector<vector<int>> &adj);

int fhMin(int nodo, const vector<int> &arr, const vector<vector<int>> &adj) {
  int menor = -1;
  for (int h : adj[nodo]) {
    int fh = f(h, arr, adj);
    if (menor == -1 || fh < menor) {
      menor = fh;
    }
  }
  return menor;
}

// Regresa el mayor numero al que podemos hacer igual a todos
// los nodos en el subarbol
int f(int nodo, const vector<int> &arr, const vector<vector<int>> &adj) {
  if (adj[nodo].size() == 0) {
    // Si es hoja, es sí mismo
    return arr[nodo];
  }
  // Sino es tomar el menor de f de sus hijos
  int fh = fhMin(nodo, arr, adj);
  return min(fh, (arr[nodo] + fh) / 2);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<int> arr(n + 2);
    vector<vector<int>> adj(n + 2, vector<int>());
    for (int i = 1; i <= n; ++i) {
      cin >> arr[i];
    }
    for (int i = 2; i <= n; ++i) {
      int x;
      cin >> x;
      adj[x].push_back(i);
    }
    lld ans = arr[1] + fhMin(1, arr, adj);
    cout << ans << endl;
  }

  return 0;
}
