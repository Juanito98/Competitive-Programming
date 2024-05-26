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
typedef int64_t ll;
const int MAXN = 1e5 + 5;
ll m[MAXN];
int a[MAXN], b[MAXN], g[MAXN];
int n;
ll ST[MAXN * 4];
void update(int index, int l, int r, int pos, ll newV) {
    if (l == r) {
        ST[index] = newV;
    } else {
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(index * 2, l, mid, pos, newV);
        } else {
            update(index * 2 + 1, mid + 1, r, pos, newV);
        }
        ST[index] = max(ST[index * 2], ST[index * 2 + 1]);
    }
}
int query(int qL, int qR, int l, int r, int index) {
    if (qL <= l && r <= qR)
        return ST[index];

    if (qR < l || r < qL || l > r)
        return 0;

    int mid = (l + r) / 2;
    return max(query(qL, qR, l, mid, 2 * index),
               query(qL, qR, mid + 1, r, 2 * index + 1));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> g[i] >> a[i] >> b[i];
    }
    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        m[i] = g[i] + query(i + min(n, a[i]), i + min(n, b[i]), 1, n, 1);
        ans = max(ans, m[i]);
        update(1, 1, n, i, m[i]);
    }
    cout << ans << '\n';
    return 0;
}
