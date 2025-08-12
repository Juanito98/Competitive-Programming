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
typedef pair<lld, lld> pll;

const lld M = 998244353;

lld expBin(lld n, lld e) {
  if (e == 0) {
    return 1;
  }
  lld x = expBin(n, e / 2);
  x *= x;
  x %= M;
  if (e & 1) {
    x *= n;
    x %= M;
  }
  return x;
}

lld inv(lld x) { return expBin(x, M - 2); }

lld notP(lld p) { return (1 - p + M) % M; }

lld pmod(lld a, lld b) { return (a * b) % M; }

vector<lld> dontTakeAnyProbDp;

lld dontTakeAnyProb(const vector<pair<pii, lld>> &range, int i, int j) {
  if (dontTakeAnyProbDp.empty()) {
    int n = range.size();
    for (int i = 0; i < n; ++i) {
      lld p = notP(range[i].second);
      if (i > 0) {
        p *= dontTakeAnyProbDp[i - 1];
        p %= M;
      }
      dontTakeAnyProbDp.push_back(p);
    }
  }
  if (i > j) {
    return 1;
  }
  return pmod(dontTakeAnyProbDp[j], inv(dontTakeAnyProbDp[i - 1]));
}

int nextRangeIdx(const vector<pair<pii, lld>> &range, int j) {
  int l = 0, r = range.size() - 1;
  while (l < r) {
    int m = (l + r) / 2;
    if (range[m].first.first < j) {
      l = (m + 1);
    } else {
      r = m;
    }
  }
  if (range[l].first.first == j)
    return l;
  else
    return -1;
}

lld ans(int m, const vector<pair<pii, lld>> &range) {
  int n = range.size();
  vector<lld> dp(n, 0);
  for (int i = n - 1; i >= 0; --i) {
    // take it
    int j = range[i].first.second == m
                ? (n)
                : nextRangeIdx(range, range[i].first.second + 1);

    if (j != -1) {
      dp[i] += pmod(range[i].second, pmod(dontTakeAnyProb(range, i + 1, j - 1),
                                          (j < n ? dp[j] : 1)));
      dp[i] %= M;
    }
    // don't take it
    if (i < n - 1 && range[i].first.first == range[i + 1].first.first) {
      dp[i] += pmod(notP(range[i].second), dp[i + 1]);
      dp[i] %= M;
    }
  }
  return range[0].first.first == 1 ? dp[0] : 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<pair<pii, lld>> range(n);

  for (int i = 0; i < n; ++i) {
    cin >> range[i].first.first >> range[i].first.second;
    lld p, q;
    cin >> p >> q;
    range[i].second = pmod(p, inv(q));
  }

  sort(range.begin(), range.end());

  cout << (ans(m, range)) << endl;

  return 0;
}
