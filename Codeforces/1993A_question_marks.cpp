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
    int n;
    string s;
    cin >> n;
    cin >> s;
    map<char, int> freq;
    for (char c : s) {
      if (c == '?')
        continue;
      if (freq.count(c) == 0) {
        freq[c] = 0;
      }
      freq[c] += 1;
    }
    int ans = 0;
    for (auto it : freq) {
      ans += min(n, it.second);
    }
    cout << ans << endl;
  }

  return 0;
}
