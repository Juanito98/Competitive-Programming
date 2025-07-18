// https://open.kattis.com/problem-sources/European%20Girls%27%20Olympiad%20in%20Informatics%202025
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

vector<int> calculate_path_from(const int start,
                                const vector<vector<int>> &adj) {
  int n = adj.size();
  vector<int> path_from_start(n, -1);
  queue<int> q;
  q.push(start);
  for (int t = 0; !q.empty(); ++t) {
    for (int i = q.size(); i > 0; --i) {
      int node = q.front();
      q.pop();
      if (path_from_start[node] != -1) {
        continue;
      }
      path_from_start[node] = t;
      for (int h : adj[node]) {
        q.push(h);
      }
    }
  }
  return path_from_start;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> radj(n, vector<int>());

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    radj[b].push_back(a);
  }

  vector<int> path_to_start = calculate_path_from(0, adj);

  // Fill the dp with a dijkstra order
  vector<int> dp(n, -1);
  priority_queue<pii> q;
  q.push({0, n - 1});
  while (!q.empty()) {
    int cost = -q.top().first;
    int node = q.top().second;
    q.pop();
    if (dp[node] != -1) {
      continue;
    }
    dp[node] = cost;
    for (int h : radj[node]) {
      int h_cost = max(path_to_start[h], 1 + cost);
      q.push({-h_cost, h});
    }
  }

  for (int node = 0; node < n - 1; ++node) {
    cout << dp[node] << " \n"[node == (n - 2)];
  }

  return 0;
}
