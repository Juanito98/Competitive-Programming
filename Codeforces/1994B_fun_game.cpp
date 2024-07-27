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
    string s, t;
    cin >> n;
    cin >> s >> t;
    bool possible = true;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '1') {
        break;
      }
      possible &= (s[i] == t[i]);
    }
    cout << (possible ? "YES" : "NO") << endl;
  }

  return 0;
}
