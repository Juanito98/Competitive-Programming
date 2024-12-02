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

const int MAXN = 1e7 + 2;

int divisor[MAXN]; // Divisor primo
bool esPrimo[MAXN];

void makeCriba(int n) {
  for (lld i = 2; i <= n; ++i) {
    if (divisor[i]) {
      continue;
    }
    divisor[i] = i;
    esPrimo[i] = true;
    for (lld j = i * i; j <= n; j += i) {
      divisor[j] = i;
    }
  }
}

int n;
int arr[MAXN];

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  int m = 0;

  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  bool ans = true;

  int g = gcd(arr[0], arr[n - 1]);
  for (int i = 0; i < n; ++i) {
    if ((arr[i] % g) != 0) {
      ans = false;
    }
    arr[i] /= g;
    m = max(m, arr[i]);
  }

  makeCriba(m);

  unordered_set<int> primosUsados;
  for (int i = 0; i < n; ++i) {
    // Apartemos los primos
    int x = arr[i];
    while (x > 1) {
      int p = divisor[x];
      while ((x % p) == 0) {
        x /= p;
      }
      if (primosUsados.count(p) > 0) {
        ans = false;
      } else {
        primosUsados.insert(p);
      }
    }
  }

  cout << (ans ? "YES" : "NO") << endl;

  return 0;
}
