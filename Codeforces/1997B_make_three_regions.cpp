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
    string sup, inf;
    cin >> sup >> inf;
    int ans = 0;
    for (int i = 1; i < n - 1; ++i) {
      if (sup[i] == '.' && sup[i - 1] == '.' && sup[i + 1] == '.' &&
          inf[i] == '.' && inf[i - 1] == 'x' && inf[i + 1] == 'x') {
        ans++;
      }
      if (inf[i] == '.' && inf[i - 1] == '.' && inf[i + 1] == '.' &&
          sup[i] == '.' && sup[i - 1] == 'x' && sup[i + 1] == 'x') {
        ans++;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
