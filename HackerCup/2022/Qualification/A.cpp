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
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr, arr + n);
        bool possible = (n <= 2 * k);
        for (int i = 1; i < n - 1; ++i) {
            if (arr[i] == arr[i - 1] && arr[i] == arr[i + 1]) {
                possible = false;
            }
        }
        cout << (possible ? "YES" : "NO") << "\n";
    }

    return 0;
}
