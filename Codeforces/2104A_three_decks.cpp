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
    int a, b, c;
    cin >> a >> b >> c;
    int d = (a + b + c) / 3;
    bool ans = ((a + b + c) % 3 == 0) && d <= c && d >= b;
    cout << (ans ? "YES" : "NO") << endl;
  }

  return 0;
}
