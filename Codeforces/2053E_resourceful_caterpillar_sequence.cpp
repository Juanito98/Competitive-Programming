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

vector<int> calculate_min_distance_to_leaf(const vector<vector<int>> &adj) {
  int n = adj.size();
  queue<int> q;
  for (int nodo = 0; nodo < n; ++nodo) {
    if (adj[nodo].size() == 1) {
      q.push(nodo);
    }
  }
  vector<int> d(n);
  vector<bool> vis(n, false);
  int t = 0;
  while (!q.empty()) {
    for (int sz = q.size(); sz > 0; --sz) {
      int nodo = q.front();
      q.pop();
      if (vis[nodo]) {
        continue;
      }
      vis[nodo] = true;
      d[nodo] = t;
      for (int child : adj[nodo]) {
        q.push(child);
      }
    }
    t++;
  }
  return d;
}

int count_leafs(const vector<int> &d) {
  int ans = 0;
  for (int x : d) {
    if (x == 0) {
      ans++;
    }
  }
  return ans;
}

void dfs(const vector<vector<int>> &adj, const vector<int> &d, int nodo,
         vector<int> &parent,
         vector<int> &nodes_with_d_greater_than_1_in_subtree,
         vector<bool> &vis) {
  vis[nodo] = true;
  for (int child : adj[nodo]) {
    if (vis[child]) {
      continue;
    }
    parent[child] = nodo;
    dfs(adj, d, child, parent, nodes_with_d_greater_than_1_in_subtree, vis);
    nodes_with_d_greater_than_1_in_subtree[nodo] +=
        nodes_with_d_greater_than_1_in_subtree[child];
  }
  if (d[nodo] > 1) {
    nodes_with_d_greater_than_1_in_subtree[nodo]++;
  }
}
void dfs(const vector<vector<int>> &adj, const vector<int> &d,
         vector<int> &parent,
         vector<int> &nodes_with_d_greater_than_1_in_subtree) {
  int n = adj.size();
  vector<bool> vis(n, false);
  dfs(adj, d, 1, parent, nodes_with_d_greater_than_1_in_subtree, vis);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      adj[a - 1].push_back(b - 1);
      adj[b - 1].push_back(a - 1);
    }
    vector<int> d = calculate_min_distance_to_leaf(adj);
    int leafs = count_leafs(d);
    vector<int> parent(n, -1);
    vector<int> nodes_with_d_greater_than_1_in_subtree(n, 0);
    dfs(adj, d, parent, nodes_with_d_greater_than_1_in_subtree);
    // Deciding q
    lld ans = 0;
    for (int q = 0; q < n; ++q) {
      if (d[q] == 0) {
        // Just make sure p is not a leaf
        ans += n - leafs;
      } else {
        // Deciding direction
        for (auto q1 : adj[q]) {
          // After nora's turn we will be in q1
          if (d[q1] != 1) {
            // if q1 is leaf (d[q1] = 0) nora wins
            // or if q1 > 1, nora can tie
            continue;
          }
          // d[q1] = 1 we could win if we decide on dany
          // p such that d[p] > 1 and p is in the subtree of q1 with
          // root on q
          if (parent[q] != q1) {
            // q1 is in the subtree of q rooted in 1
            ans += nodes_with_d_greater_than_1_in_subtree[q1];
          } else {
            ans += nodes_with_d_greater_than_1_in_subtree[1] -
                   nodes_with_d_greater_than_1_in_subtree[q];
          }
        }
      }
    }
    cout << ans << endl;
  }

  return 0;
}
