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

const bool verbose = false;

int right_distance(int i, int j, int n) {
  int d = abs(j - i);
  if (i <= j) {
    return d;
  } else {
    return n - d;
  }
}

int left_distance(int i, int j, int n) { return n - right_distance(i, j, n); }

int component(const pii &s, int m, int n) {
  int i = s.first, j = s.second;
  if (i > j) {
    swap(i, j);
  }
  int ld = left_distance(i, j, n);
  int rd = right_distance(i, j, n);
  if ((rd & 1) == 0) {
    return -1;
  }
  int ca1 = (i + ((rd - 1) / 2)) % n;
  int ca2 = (j + ((ld - 1) / 2)) % n;
  if (verbose) {
    cout << "Component " << i << " " << j << endl;
    cout << "ca1: " << ca1 << ", ca2: " << ca2 << endl;
  }
  return min(ca1, ca2);
}

int component_inv(int i, int component, int m, int n) {
  // rotate to the left so component is 0
  int ir = (i - component + n) % n;
  int jr = (n - ir + 1);
  return (jr + component) % n;
}

int calculate_best_component(vector<pii> &strings, int m, int n) {
  vector<int> cost(m, m);
  for (auto s : strings) {
    int c = component(s, m, n);
    if (c == -1) {
      continue;
    } else {
      cost[c]--;
    }
  }

  int argmin = 0;
  for (int i = 1; i < m; ++i) {
    if (cost[i] < cost[argmin]) {
      argmin = i;
    }
  }
  if (verbose) {
    cout << "Best rotation: " << argmin << endl;
    cout << "Cost: " << cost[argmin] << endl;
  }
  return argmin;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int m;
  cin >> m;

  vector<pii> strings(m);
  for (int i = 0; i < m; ++i) {
    cin >> strings[i].first >> strings[i].second;
  }

  int n = 2 * m;
  vector<int> string_idx(n);
  for (int i = 0; i < m; ++i) {
    string_idx[strings[i].first] = i;
    string_idx[strings[i].second] = i;
  }

  int best_component = calculate_best_component(strings, m, n);

  // here we'll modify the strings
  vector<pair<int, pii>> ans;
  vector<bool> fixed(m, false);
  for (int si = 0; si < m; ++si) {
    // Will fix string si if needed
    if (fixed[si]) {
      continue;
    }
    int scurr = si;
    int a = strings[scurr].first, b = strings[scurr].second;
    int b_good = component_inv(a, best_component, m, n);
    if (b == b_good) {
      fixed[scurr] = true;
    }
    while (!fixed[scurr]) {
      ans.push_back({scurr, {b, b_good}});
      fixed[scurr] = true;
      scurr = string_idx[b_good];
      b = b_good;
      a = (strings[scurr].first == b ? strings[scurr].second
                                     : strings[scurr].first);
      b_good = component_inv(a, best_component, m, n);
    }
  }

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i].first << " " << ans[i].second.first << " "
         << ans[i].second.second << endl;
  }

  return 0;
}
