/* Solution idea.
The groundy number of a single token in (i, j) (zero indexed) is:
G({(i, j)}) = 2^j if j > 0 else 0

This means that the final nim number will be != 0 if there is at least
one column such that j > 0 and there is an odd number of tokens in the
column.

-------
Note: Special case
n=1 is an special case where the groundy number is:
G({(i, j)}) = 0 if j is even else 1.

Thus, the final nim num will be the xor of all groundy num.
*/
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

  int t;
  for (cin >> t; t; --t) {
    int n, m, k;
    cin >> n >> m >> k;
    // Counts how many tokens are in column j
    unordered_map<int, int> freq;
    for (int i = 0; i < k; ++i) {
      int a, b;
      cin >> a >> b;
      int col = b - 1;
      if (col > 0) {
        freq[col]++;
      }
    }
    bool first_wins;
    if (n == 1) {
      first_wins = (freq[1] & 1);
    } else {
      first_wins = false;
      for (auto it : freq) {
        first_wins |= (it.second & 1);
      }
    }

    if (first_wins) {
      cout << "Mimo\n";
    } else {
      cout << "Yuyu\n";
    }
  }

  return 0;
}
