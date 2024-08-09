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

int lsb(int x) {
  // least significant bit
  return x & (-x);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      for (int j = 0; j < arr[i] - 1; j++) {
        int x; // useless
        cin >> x;
      }
    }
    sort(arr.begin(), arr.end());
    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
      // Find the first common bit
      int common = ans & arr[i];
      int subtree = -1; // Unset
      if (common > 0) {
        // Found the MSB of common and take all sufix 1s
        int msb;
        for (msb = common; msb - lsb(msb) > 0; msb -= lsb(msb))
          ;
        subtree = (arr[i] - msb) | (msb - 1);
      } else {
        subtree = arr[i]; // take all
      }
      ans |= subtree;
    }
    cout << ans << endl;
  }

  return 0;
}
