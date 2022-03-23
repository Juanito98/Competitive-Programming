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

int cnt_bits_memo[1 << 15];
int cnt_bits(int msc) {
    if (!msc) return 0;
    if (!cnt_bits_memo[msc]) {
        cnt_bits_memo[msc] = 1 + cnt_bits(msc - (msc&(-msc)));
    }
    return cnt_bits_memo[msc];
}

bool marked(int msc, int i) {
    return msc & (1 << i);
}

int mark(int msc, int i) {
    return msc | (1 << i);
}

int n, k;

int diag_inv(int i, int j) {
    return n + i - j - 1;
}

bool vis[15][1 << 15];
lld memo[15][1 << 15];
lld dp(int d, int msc) {
    if (cnt_bits(msc) == k) {
        return 1;
    }
    if (d >= 2*n - 1) {
        return 0;
    }
    if (!vis[d][msc]) {
        vis[d][msc] = true;
        // No tomar
        memo[d][msc] = dp(d + 1, msc);
        // Tomar
        for (int i = 0; i < n; i++) {
            int j = d - i;
            if (j < 0 || j >= n || marked(msc, diag_inv(i, j))) continue;
            memo[d][msc] += dp(d + 1, mark(msc, diag_inv(i, j)));
        }
    }
    return memo[d][msc];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    cout << dp(0, 0) << endl;

    return 0;
}