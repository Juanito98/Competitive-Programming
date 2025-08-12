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
typedef unsigned long long int ulld;
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    ulld a, b, k;
    cin >> a >> b >> k;
    if (a > b) {
      swap(a, b);
    }
    ulld g = __gcd(a, b);
    int ans = (b / g <= k) ? 1 : 2;
    cout << ans << endl;
  }

  return 0;
}
