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

int f(vector<int> &a) {
  if (0 == a[0] && 0 == a[1] && 0 == a[2]) {
    return 0;
  }
  sort(a.begin(), a.end());
  a[2] = a[1] / 2;
  return 1 + f(a);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int x;
    cin >> x;
    vector<int> a = {x, x, x};
    cout << f(a) << endl;
  }

  return 0;
}
