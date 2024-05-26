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

typedef vector<vector<lld>> matrix;

const lld MOD = 1e9 + 7;

void printMatrix(const matrix &m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[i].size(); ++j) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
}

matrix multiply(const matrix &a, const matrix &b) {
  int n = a.size();
  int k = a[0].size();
  int m = b[0].size();
  matrix c = vector<vector<lld>>(n, vector<lld>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int l = 0; l < k; ++l) {
        c[i][j] += a[i][l] * b[l][j];
        c[i][j] %= MOD;
      }
    }
  }
  return c;
}

matrix matExp(const matrix &A, int e) {
  if (e == 1) {
    return A;
  }
  matrix res = matExp(A, e / 2);
  res = multiply(res, res);
  if (e & 1) {
    res = multiply(A, res);
  }
  return res;
}

matrix buildInit() {
  matrix A = vector<vector<lld>>(20, vector<lld>(20, 0));
  // After 2 minutes, every 4 minutes it produces by meiosis 3 brand
  for (int j = 5; j < 20; j += 4) {
    A[0][j] = 3;
  }
  // Following rows have 1 in i-1
  for (int i = 1; i < 20; ++i) {
    A[i][i - 1] = 1;
  }
  return A;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    matrix ans = matExp(buildInit(), n);
    // Sum the first column
    lld s = 0;
    for (int i = 0; i < ans.size(); ++i) {
      s += ans[i][0];
      s %= MOD;
    }
    cout << s << "\n";
  }

  return 0;
}
