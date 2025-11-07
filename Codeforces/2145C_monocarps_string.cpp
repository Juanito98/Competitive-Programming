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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> sum(n);
    for (int i = 0; i < n; ++i) {
      sum[i] = (s[i] == 'a' ? 1 : -1);
      if (i > 0) {
        sum[i] += sum[i - 1];
      }
    }
    // We are looking for the min j-i such that sum[j] - sum[i-1] = goal
    int goal = sum[n - 1];
    unordered_map<int, int> um;
    um[0] = -1;
    int best = (goal == 0 ? 0 : n);
    for (int j = 0; j < n; ++j) {
      int x = sum[j] - goal;
      if (um.count(x) > 0) {
        int i = um[x];
        best = min(best, j - i);
      }
      um[sum[j]] = j;
    }
    cout << (best == n ? -1 : best) << endl;
  }

  return 0;
}
