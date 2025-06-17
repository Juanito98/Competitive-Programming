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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n, m;
    cin >> n >> m;
    int fn_prev = 1, fn = 1;
    for (int i = 1; i < n; ++i) {
      swap(fn_prev, fn);
      fn += fn_prev;
    }
    for (int i = 0; i < m; ++i) {
      vector<int> a(3);
      cin >> a[0] >> a[1] >> a[2];
      sort(a.begin(), a.end());
      bool possible = a[0] >= fn && a[2] >= (fn + fn_prev);
      cout << (possible ? 1 : 0);
    }
    cout << endl;
  }

  return 0;
}
