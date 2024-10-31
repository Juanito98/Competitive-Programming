// Source: https://oj.uz/problem/view/EGOI24_circlepassing
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

int cost(int i, int j, int n) {
  int d = std::abs(i - j);
  return std::min(d, 2 * n - d);
}

int jump(int i, int n) { return (i + n) % (2 * n); }

int main() {
  int n, m, q;
  std::cin >> n >> m >> q;
  std::vector<int> bff(m);
  for (int i = 0; i < m; i++) {
    std::cin >> bff[i];
  }
  std::sort(bff.begin(), bff.end());

  // answer queries
  for (int i = 0; i < q; i++) {
    int a, b;
    std::cin >> a >> b;
    if (a >= n && b >= n) {
      a %= n;
      b %= n;
    }
    if (a > b) {
      std::swap(a, b);
    }
    const std::vector<int>::iterator j =
        std::lower_bound(bff.begin(), bff.end(), a);

    int pos = (j - bff.begin());

    int R = (pos < m ? bff[pos] : jump(bff[0], n));
    int L = (pos < m && bff[pos] == a
                 ? bff[pos]
                 : (pos > 0 ? bff[pos - 1] : jump(bff[m - 1], n)));

    int ans = cost(a, b, n);
    ans = std::min(ans, cost(a, R, n) + 1 + cost(jump(R, n), b, n));
    ans = std::min(ans, cost(a, L, n) + 1 + cost(jump(L, n), b, n));

    std::cout << ans << std::endl;
  }

  return 0;
}
