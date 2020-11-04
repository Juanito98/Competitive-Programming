#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
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

    int n = 18;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int ans = 0;

    string s;
    getline(cin, s);
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        //cout << s;
        if (s == "par") {
            ans += arr[i];
        } else if (s == "hole in one") {
            ans ++;
        } else if (s == "condor") {
            ans += arr[i] - 4;
        } else if (s == "albatross") {
            ans += arr[i] - 3;
        } else if (s == "eagle") {
            ans += arr[i] - 2;
        } else if (s == "birdie") {
            ans += arr[i] - 1;
        } else if (s == "bogey") {
            ans += arr[i] + 1;
        } else if (s == "double bogey") {
            ans += arr[i] + 2;
        } else if (s == "triple bogey") {
            ans += arr[i] + 3;
        }
        //cout << ans << endl;
    }

    cout << ans << "\n";

    return 0;
}