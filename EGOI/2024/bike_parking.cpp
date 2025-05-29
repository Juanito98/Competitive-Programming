// https://open.kattis.com/problem-sources/European%20Girls%27%20Olympiad%20in%20Informatics%202024
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
  vector<int> A(n), B(n);

  int asum = 0;
  int ai = 0, aj = n - 1;
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
    asum += A[i];
  }
  int sum = 0;
  int bi = 0, bj = n - 1;
  for (int i = 0; i < n; ++i) {
    cin >> B[i];
    sum += B[i];
  }

  int score = 0;

  auto assign = [&](int ai, int bi) {
    // Assing all possible people from bi into ai
    int cnt = min(A[ai], B[bi]);
    sum -= cnt;
    A[ai] -= cnt;
    B[bi] -= cnt;
    score += ai < bi ? cnt : (ai > bi ? -cnt : 0);
    // cout << "Assigned " << cnt << " people from " << bi << " to " << ai <<
    // endl; cout << "Score " << score << endl;
  };

  while (asum - A[aj] >= sum) {
    asum -= A[aj];
    A[aj] = 0;
    aj--;
  }
  if (asum > sum) {
    int d = asum - sum;
    A[aj] -= d;
  }

  while (sum > 0) {
    while (A[ai] == 0) {
      ai++;
    }
    while (A[aj] == 0) {
      aj--;
    }
    while (B[bi] == 0) {
      bi++;
    }
    while (B[bj] == 0) {
      bj--;
    }
    if (ai < bi) {
      // Cualquiera va a ser feliz si asignamos a ai
      // Asignemos a los primeros que sean felices
      assign(ai, bi);
    } else if (aj < bj) {
      // bj a fuerza va a ser feliz, que sea feliz con lo menos
      assign(aj, bj);
    } else {
      // ai >= bi && aj >= bj
      // No hay manera que bi sea feliz, y la persona que este
      // asignada a aj no hay manera que sea feliz.
      // Conviene asignar a la persona bi a aj.
      assign(aj, bi);
    }
  }

  cout << score << endl;

  return 0;
}
