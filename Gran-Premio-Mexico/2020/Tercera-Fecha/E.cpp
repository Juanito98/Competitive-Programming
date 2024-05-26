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
    lld B;
    cin >> n >> B;

    vector<int> arr(n);
    vector<lld> ans(n);

    priority_queue<pii> monti;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        if (arr[i] > 0) monti.push({-arr[i], i});
    }

    while (!monti.empty()) {
        int idx = monti.top().second;
        monti.pop();
        lld paga = B;
        if (arr[(idx+1) % n] < arr[idx])
            paga = max(paga, ans[(idx + 1) % n] + B);
        if (arr[(idx-1+n) % n] < arr[idx])
            paga = max(paga, ans[(idx - 1 + n) % n] + B);
        ans[idx] = paga;
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}