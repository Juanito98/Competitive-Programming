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

const int MAXN = 100002;

int n;
int arr[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr, arr + n);
        int curr = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] > curr) {
                curr++;
            }
        }
        cout << curr << endl;
    }

    return 0;
}
