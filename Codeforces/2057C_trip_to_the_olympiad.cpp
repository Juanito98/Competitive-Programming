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

int lsb(int x) { return x & (-x); }

int msb(int x) {
  if (x == 0) {
    return 0;
  }
  while (lsb(x) < x) {
    x -= lsb(x);
  }
  return x;
}

// a ^ c = x, b ^ c = y
// => (a ^ b) + (a ^ c) + (b ^ c)
//    = (x ^ y) + x + y
// Note: if x = 1111111111, then y is irrelevant
void find_answer(int l, int r, int &a, int &b, int &c) {
  if (r == 0) {
    return;
  }
  int msbr = msb(r);

  if (msbr == msb(l)) {
    // All of them are going to have the msbr
    a += msbr;
    b += msbr;
    c += msbr;
    find_answer(l - msbr, r - msbr, a, b, c);
  } else {
    // a = 1000..., c = 01111..., b irrelevant
    a += msbr;
    c += msbr - 1;

    // b irrelevant but want to be different from a, c
    b += (msbr == r ? l : r);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int l, r;
    cin >> l >> r;
    int a = 0, b = 0, c = 0;
    find_answer(l, r, a, b, c);

    cout << a << " " << b << " " << c << endl;
  }

  return 0;
}
