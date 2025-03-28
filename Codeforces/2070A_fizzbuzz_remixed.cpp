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
    cin >> n;
    int ans = 0;
    for (int i = 0; i < min(n + 1, 15); ++i) {
      if ((i % 3) == (i % 5)) {
        // i, i + 15, i + 30, + .. will share modulo
        ans += ((n - i) / 15) + 1;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
