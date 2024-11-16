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

  int n, p;
  cin >> n >> p;

  vector<int> v(n);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    if (v[i] <= p) {
      ans = max(ans, v[i]);
    }
  }

  cout << ans << endl;

  return 0;
}
