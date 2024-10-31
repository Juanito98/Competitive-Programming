// Source: https://oj.uz/problem/view/EGOI24_bouquet
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

const int MAXN = 200002;
struct Segment_tree {
  int n;
  vector<int> tree;

  Segment_tree(int n_arg) {
    n = n_arg;
    tree = vector<int>(n_arg * 5, 0);
  }

  int izq(int nodo) { return nodo * 2; }
  int der(int nodo) { return nodo * 2 + 1; }

  void print(int nodo, int ini, int fin) {
    if (ini > fin) {
      return;
    }
    if (ini == fin) {
      cout << "ST[" << ini << "] = " << tree[nodo] << endl;
    } else {
      int med = (ini + fin) / 2;
      print(izq(nodo), ini, med);
      print(der(nodo), med + 1, fin);
    }
  }
  void print() { print(1, 0, n - 1); }

  void update(int nodo, int ini, int fin, int pos, int v) {
    if (ini > pos || fin < pos || ini > fin) {
      return;
    }
    if (ini == fin) {
      tree[nodo] = v;
    } else {
      int med = (ini + fin) / 2;
      update(izq(nodo), ini, med, pos, v);
      update(der(nodo), med + 1, fin, pos, v);
      tree[nodo] = max(tree[izq(nodo)], tree[der(nodo)]);
    }
  }
  void update(int pos, int v) { update(1, 0, n - 1, pos, v); }

  int query(int nodo, int ini, int fin, int l, int r) {
    if (ini > r || fin < l || ini > fin) {
      return 0;
    }
    if (ini >= l && fin <= r) {
      return tree[nodo];
    } else {
      int med = (ini + fin) / 2;
      return max(query(izq(nodo), ini, med, l, r),
                 query(der(nodo), med + 1, fin, l, r));
    }
  }

  int query(int r) {
    if (r < 0) {
      return 0;
    }
    return query(1, 0, n - 1, 0, r);
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<pii> arr(n);
  Segment_tree st(n);
  vector<int> dp(n);
  priority_queue<pii> updates;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    // Leemos
    int l, r;
    cin >> l >> r;
    // Calculamos dp(i)
    // cout << i << "################\n";

    dp[i] = 1 + st.query(i - l - 1);
    // cout << "dp[i] = " << dp[i] << endl;

    // Metemos el updeteo de i
    updates.push({-(i + r), i});
    // Updeteamos los valores utiles para las sig iteraciones
    while (!updates.empty() && abs(updates.top().first) <= i) {
      int p = updates.top().second;
      int v = dp[p];
      st.update(p, v);
      updates.pop();
    }
    // st.print();
    //   Updeteamos solución
    ans = max(ans, dp[i]);
  }

  cout << ans << endl;

  return 0;
}
