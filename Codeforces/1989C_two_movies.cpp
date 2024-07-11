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

    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) {
      cin >> A[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> B[i];
    }

    int rankM1 = 0, rankM2 = 0, p1s = 0, pNeg1s = 0;
    for (int i = 0; i < n; ++i) {
      if (A[i] == 1 && B[i] == 1) {
        p1s++;
      } else if (A[i] == -1 && B[i] == -1) {
        pNeg1s++;
      } else if (A[i] > B[i]) {
        // (1,0), (1,-1), (0,-1)
        rankM1 += A[i];
      } else {
        // (0,1), (-1,1), (0,0), (-1,0)
        rankM2 += B[i];
      }
    }
    for (; p1s > 0; --p1s) {
      if (rankM1 < rankM2) {
        rankM1++;
      } else {
        rankM2++;
      }
    }
    for (; pNeg1s > 0; --pNeg1s) {
      if (rankM1 < rankM2) {
        rankM2--;
      } else {
        rankM1--;
      }
    }
    cout << min(rankM1, rankM2) << endl;
  }

  return 0;
}
