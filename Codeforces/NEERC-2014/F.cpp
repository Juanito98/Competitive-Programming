#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
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
typedef pair<lld, lld> pii;

void calcula(vector<lld> &arr, vector<lld>& L, int k) {
    int n = arr.size();
    int i = 0;
    lld power = 0;
    for (int j = 0; j < n; ++j) {
        power += arr[j];
        if (j - i + 1 > k) 
            power -= arr[i++];
        L[j] = power;
        if (j > 0) L[j] = max(L[j], L[j-1]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<lld> arr(n);
    for (int i = 0; i < n; ++i) 
        cin >> arr[i];

    vector<lld> L(n), R(n);

    calcula(arr, L, k);
    reverse(arr.begin(), arr.end());
    calcula(arr, R, k),
    reverse(R.begin(), R.end());


    lld ans = R[0];
    for (int i = 1; i < n; ++i) {
        ans = max(ans, L[i-1] + R[i]);
    }

    cout << ans << "\n";
    return 0;
}