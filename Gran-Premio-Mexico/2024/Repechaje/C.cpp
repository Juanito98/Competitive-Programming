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

const int BOOK_TIME = 480;
const int CLOSE_TIME = BOOK_TIME + 300;

const int MAXN = 1002;
const int MAXT = BOOK_TIME + 2;

int n;
pii arr[MAXN];

void read(vector<int> &a) {
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
}

void zip(const vector<int> &a, const vector<int> &b) {
  for (int i = 0; i < n; ++i) {
    arr[i] = {a[i], b[i]};
  }
}

int color;
int vis[MAXN][MAXT];
int memo[MAXN][MAXT];

// Dado que son las t minutos, maximiza arr.second
// sabiendo que te tomará arr.first * 3 minutos terminar
// uno
int dp(int i, int t) {
  if (i >= n || t > BOOK_TIME) {
    // Ya no podemos rentar otro libro
    return 0;
  }

  if (vis[i][t] != color) {
    vis[i][t] = color;
    memo[i][t] = dp(i + 1, t);
    // Checamos si lo podemos rentar
    if (arr[i].first * 3 + t <= CLOSE_TIME) {
      memo[i][t] =
          max(memo[i][t], arr[i].second + dp(i + 1, t + arr[i].first * 3));
    }
  }
  return memo[i][t];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  vector<int> pages(n), a(n), b(n);

  read(pages);
  read(a);
  read(b);

  auto solve = [&](const vector<int> &v) {
    zip(pages, v);
    sort(arr, arr + n);
    color++;
    return dp(0, 0);
  };

  int p = solve(a);
  int f = solve(b);

  if (p == f) {
    cout << "EITHER\n";
  } else if (p < f) {
    cout << "FAME\n";
  } else {
    cout << "PLEASURE\n";
  }

  return 0;
}
