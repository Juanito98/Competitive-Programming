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
const int MOD = 998244353;

struct SortedArray {
  int n;
  vector<lld> a;
  vector<int> sorted; // sorted[i] is the index of the ith greatest element
  vector<int> p;      // p[sorted[i]] = i,

  SortedArray(vector<lld> &arr) {
    cout.flush();
    a = arr;
    n = a.size();
    sorted = vector<int>(n);
    p = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      sorted[i] = i;
    }
    sort(sorted.begin(), sorted.end(),
         [&](int i, int j) { return a[i] < a[j]; });
    for (int i = 0; i < n; ++i) {
      p[sorted[i]] = i;
    }
  }

  lld get(int i) { return a[i]; }
  lld getSorted(int i) { return a[sorted[i]]; }

  int upper_bound_sorted_idx(int v) {
    if (getSorted(n - 1) <= v) {
      return n;
    }
    int l = 0, r = n - 1;
    while (l < r) {
      int m = (l + r) / 2;
      if (getSorted(m) <= v) {
        l = m + 1;
      } else {
        r = m;
      }
    }
    return l;
  }

  int getSortedIdx(int i) { return p[i]; }

  // increases a[i] by 1.
  void incr(int i) {
    int sorted_i = getSortedIdx(i);
    int sorted_j = upper_bound_sorted_idx(a[i]);
    sorted_j--;
    swap(sorted[sorted_i], sorted[sorted_j]);
    p[sorted[sorted_i]] = sorted_i;
    p[sorted[sorted_j]] = sorted_j;
    a[i]++;
  }
};

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

SortedArray *fromRead(int n) {
  vector<lld> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  return (new SortedArray(a));
}

// a and b are sorted, we want to increase a[i] by 1
// and keep it sorted and update the response
void update(SortedArray *a, SortedArray *b, int i, lld &ans) {
  lld old_v = a->get(i);
  a->incr(i);
  int new_sorted_idx = a->getSortedIdx(i);
  ans *= invMod(min(old_v, b->getSorted(new_sorted_idx)));
  ans %= MOD;
  ans *= (min(a->getSorted(new_sorted_idx), b->getSorted(new_sorted_idx)));
  ans %= MOD;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n, q;
    cin >> n >> q;
    SortedArray *a = fromRead(n);
    SortedArray *b = fromRead(n);
    lld ans = 1;
    {
      // Calculate the initial ans
      for (int i = 0; i < n; ++i) {
        ans *= min(a->getSorted(i), b->getSorted(i));
        ans %= MOD;
      }
    }

    cout << ans;

    for (int i = 0; i < q; ++i) {
      int op, x;
      cin >> op >> x;

      if (op == 1) {
        update(a, b, x - 1, ans);
      } else {
        update(b, a, x - 1, ans);
      }

      cout << " " << ans;
    }
    cout << endl;
  }

  return 0;
}
