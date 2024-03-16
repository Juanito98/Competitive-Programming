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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        bool impossible = false;
        int last = 100;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] > last) {
                // I need to split a[i]
                int d1 = a[i] / 10;
                int d2 = a[i] % 10;
                if (d1 > d2 || d2 > last) {
                    impossible = true;
                }
                last = d1;
            } else {
                last = a[i];
            }
        }
        cout << (impossible ? "NO" : "YES") << "\n";
    }

    return 0;
}
