#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
#include <functional>
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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    vector<int> degree(n, 0);

    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
      degree[a]++;
      degree[b]++;
    }

    int root = -1;
    for (int i = 0; i < n; ++i) {
      if (degree[i] == 2) {
        root = i;
      }
    }

    if (root == -1) {
      cout << "NO\n";
    } else {
      cout << "YES\n";

      queue<pair<pii, int>> q;
      q.push({{root, -1}, 0});
      while (!q.empty()) {
        int nodo = q.front().first.first;
        int parent = q.front().first.second;
        int parity = q.front().second;
        q.pop();
        for (auto h : adj[nodo]) {
          if (h == parent) {
            continue;
          }
          if (parity == 0) {
            cout << nodo + 1 << " " << h + 1 << endl;
          } else {
            cout << h + 1 << " " << nodo + 1 << endl;
          }
          q.push({{h, nodo}, parity ^ 1});
          if (parent == -1) {
            parity ^= 1;
          }
        }
      }
    }
  }

  return 0;
}
