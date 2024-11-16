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

// Returns the size of the subtree
int dfs(int nodo, int p, vector<lld> &freq, const int n,
        const vector<vector<int>> &adj) {
  int sz = 1;
  for (int h : adj[nodo]) {
    if (h == p) {
      continue;
    }
    int childSz = dfs(h, nodo, freq, n, adj);
    freq[h] = ((lld)(childSz)) * ((lld)(n - childSz));
    sz += childSz;
  }
  return sz;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<vector<int>> adj(n, vector<int>());
  // Read
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // freq[i] will be the number of times
  // we pass the vertex i <-> parent i
  vector<lld> freq(n, 0);
  dfs(0, -1, freq, n, adj);
  lld ans = 0;
  int cnt = 0;
  for (int nodo = 0; nodo < n; ++nodo) {
    if (freq[nodo] > ans) {
      ans = freq[nodo];
      cnt = 1;
    } else if (freq[nodo] == ans) {
      cnt++;
    }
  }
  cout << ans << " " << cnt << endl;
  return 0;
}
