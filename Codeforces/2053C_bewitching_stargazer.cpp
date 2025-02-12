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

// Calculates the lucky value of looking [1, n]
// and how many did you count
pair<lld, int> luckyValue(int n, int k) {
  if (n < k) {
    return {0, 0};
  }
  int m = (n + 1) / 2;
  int r = (n & 1) ? m - 1 : m;
  pair<lld, int> ans = luckyValue(r, k);
  // we count the same from [1, r] than [l, n]
  ans.first += ans.first + (lld)(ans.second) * (lld)(m);
  ans.second *= 2;
  if (n & 1) {
    ans.first += m;
    ans.second++;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n, k;
    cin >> n >> k;
    lld ans = (luckyValue(n, k)).first;
    cout << ans << endl;
  }

  return 0;
}
