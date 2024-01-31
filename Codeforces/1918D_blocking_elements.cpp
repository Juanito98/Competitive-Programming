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
typedef pair<lld, int> pii;



lld sum(const vector<int>& a) {
    lld ans = 0;
    for (int x : a) {
        ans += x;
    }
    return ans;
}

/*
Gives you the minimum cost to segment the array
in which each segment has a sum <= C
The first and last element should be taken
*/
lld dp(const vector<int>& arr, lld C) {
    int n = arr.size();
    vector<lld> memo(n, 0);
    // Deque will help me keep track of the minimum
    deque<pii> dq;
    int j = 0;
    lld sumji = 0;
    memo[0] = arr[0];
    // cout << "C = " << C << " n = " << n << '\n';
    dq.push_back({memo[0], 0});
    for (int i = 1; i < n; sumji += arr[i++]) {
        // dp(i) = arr[i] + min(dp(k)) for all k < i and sum(arr[j+1..k-1]) <= C
        // j is the last index such that sum(arr[j+1..i-1]) <= C.
        while (sumji > C) {
            j++;
            sumji -= arr[j];
        }
        while (!dq.empty() && dq.front().second < j) {
            dq.pop_front();
        }
        memo[i] = arr[i] + dq.front().first;
        // Push the new element
        while (!dq.empty() && dq.back().first >= memo[i]) {
            dq.pop_back();
        }
        dq.push_back({memo[i], i});
        // cout << "dp(" << i << ") = " << memo[i] << '\n';
    }
    return memo[n - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; --T) {
        int n;
        cin >> n;
        vector<int> a(n + 2);
        a[0] = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        a[n + 1] = 0;
        // Bin search in the answer
        lld lo = 0, hi = sum(a);
        while (lo < hi) {
            lld mid = (lo + hi) / 2;
            // Check if mid is possible
            bool ok = dp(a, mid) <= mid;
            if (ok) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << lo << '\n';
    }

    return 0;
}
