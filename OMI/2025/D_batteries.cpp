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

bool query(int a, int b) {
  if (a == -1 || b == -1 || a == b) {
    return 0;
  }
  cout << a << " " << b << endl;
  cout.flush();
  int ans;
  cin >> ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  for (cin >> t; t; --t) {
    int n;
    cin >> n;
    bool found = false;
    for (int d = 1; d < n && !found; ++d) {
      for (int i = 0; i < n && !found; ++i) {
        found |= query(i + 1, ((i + d) % n) + 1);
      }
    }
  }

  return 0;
}
