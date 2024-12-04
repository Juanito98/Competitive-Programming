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

const int MAXN = 1e5 + 2;

const lld MOD = 1e9 + 7;

lld exp(lld x, lld e) {
  if (e == 0) {
    return 1;
  }
  lld ans = exp(x, e / 2);
  ans *= ans;
  ans %= MOD;
  if (e & 1) {
    ans *= x;
    ans %= MOD;
  }
  return ans;
}

lld invMod(lld x) { return exp(x, MOD - 2); }

lld factorial[MAXN];
lld fact(int x) {
  if (x == 0) {
    return 1;
  }
  if (!factorial[x]) {
    factorial[x] = x * fact(x - 1);
    factorial[x] %= MOD;
  }
  return factorial[x];
}

lld C(int n, int k) {
  lld ans = ((fact(n) * invMod(fact(n - k))) % MOD) * invMod(fact(k));
  ans %= MOD;
  return ans;
}

int n, m, k;
vector<pii> adj[MAXN];

// dFreq[x] is the number of nodes at x distance
map<int, int> dFreq;

bool vis[MAXN];
int d[MAXN];

void dijkstra() {
  int nodo = 0;
  int dNeg = 0;
  priority_queue<pii> monti;
  monti.push({dNeg, nodo});
  while (!monti.empty()) {
    tie(dNeg, nodo) = monti.top();
    monti.pop();
    if (vis[nodo]) {
      continue;
    }
    vis[nodo] = true;
    d[nodo] = -dNeg;
    dFreq[d[nodo]]++;
    for (auto p : adj[nodo]) {
      monti.push({dNeg - p.second, p.first});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }

  dijkstra();

  lld ans = 0;
  int nn = n;
  // E = d1 * p(d1) + d2 * p(d2) + ...
  //   = d1 * #valid|d1 / C(n, k) + d2 * #valid|d2 / C(n, k)
  for (const auto it : dFreq) {
    // we add the chunk of E given the closest friend
    // is at it.first.
    nn -= it.second;
    if (it.first == 0) {
      continue;
    }
    for (int i = 1; i <= it.second; ++i) {
      // Lets put i friends at it.first distance
      if (i > k || k - i > nn) {
        // invalid
        continue;
      }
      lld s = C(it.second, i) * C(nn, k - i);
      s %= MOD;
      s *= it.first;
      s %= MOD;
      ans += s;
      ans %= MOD;
    }
  }

  ans *= invMod(C(n - 1, k));
  ans %= MOD;

  cout << ans << endl;
  return 0;
}
