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

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  int curr = 0;
  int turn = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] == curr) {
      continue;
    }
    turn ^= 1;
    if (a[i] == curr + 1) {
      curr++;
    } else {
      break;
    }
  }

  cout << (turn ? "Bobius" : "Alicius") << endl;

  return 0;
}
