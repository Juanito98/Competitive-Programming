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

int f(const string &s, const string &t) {
  // find the starting match in s (substring)
  int ans = 0;
  for (int i = 0; i < s.size(); ++i) {
    for (int j = 0; j < t.size(); ++j) {
      if (s[i] != t[j])
        continue;
      // Two pointers to iterate left and right of t
      int l = j;
      for (int k = i; l >= 0 && k >= 0; k--) {
        if (s[k] == t[l]) {
          l--;
        }
      }
      l++;
      int r = j;
      for (int k = i; r < t.size() && k < s.size(); k++) {
        if (s[k] == t[r]) {
          r++;
        }
      }
      r--;
      ans = max(ans, r - l + 1);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    string s, t;
    cin >> s >> t;
    cout << s.size() + t.size() - f(s, t) << endl;
  }

  return 0;
}
