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

const int MAXN = 1e7;

bool isComposite[MAXN];
vector<int> primes;

void sieve() {
  for (int i = 3; i * i < MAXN; i += 2) {
    if (!isComposite[i]) {
      for (int j = i * i; j < MAXN; j += i) {
        isComposite[j] = true;
      }
    }
  }
  primes.push_back(2);
  for (int i = 3; i < MAXN; i += 2) {
    if (!isComposite[i])
      primes.push_back(i);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  sieve();
  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    lld carry = 0;
    int ans = 0;
    for (ans = 0; carry + arr[ans] >= primes[ans] && ans < n; ans++) {
      carry = carry + arr[ans] - primes[ans];
    }
    cout << n - ans << endl;
  }

  return 0;
}
