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

void print(vector<lld> &arr) {
    int n = arr.size();
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

lld gcd(lld a, lld b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    lld L;
    int n;
    cin >> L >> n;

    lld ans = 0;
    for (int i = 0; i < n; ++i) {
        lld p;
        int d;
        cin >> p >> d;
        if (d == 0)
            ans = max(ans, p);
        else 
            ans = max(ans, L - p);
    }

    cout << ans << "\n";

    return 0;
}