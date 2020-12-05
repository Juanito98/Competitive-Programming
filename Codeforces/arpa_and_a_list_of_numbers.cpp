/*
    Teoría de números
    https://codeforces.com/contest/851/problem/D
*/
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

const int MAX = 1000002;

lld sum[MAX], sumCnt[MAX];

lld query(lld s[], int i, int j) {
    j = min(MAX - 1, j);
    if (i > j) return 0;
    return s[j] - s[i - 1];
}

int n;
lld x, y;
int maxA;

lld f(int g) {
    int len = min(x / y, g - 1ll);
    lld res = 0;
    for (int k = g; k - g < maxA; k += g) {
        // Veamos los que van de (k-g, k]
        // Los que les conviene y
        lld cnt = query(sumCnt, k - len, k);
        res += (cnt * k - query(sum, k - len, k)) * y;
        // Los que les conviene x
        res += query(sumCnt, k - g + 1, k - len - 1) * x;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> x >> y;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum[a[i]] += a[i];
        sumCnt[a[i]]++;
        maxA = max(maxA, a[i]);
    }

    for (int i = 1; i < MAX; ++i) {
        sum[i] += sum[i - 1];
        sumCnt[i] += sumCnt[i - 1];
    }

    lld ans = 1ll << 60;
    if (maxA == 1) {
        ans = (lld) (n) * min(x, y);
    }
    for (int g = 2; g <= maxA; ++g)
        ans = min(ans, f(g));

    cout << ans << "\n";

    return 0;
}