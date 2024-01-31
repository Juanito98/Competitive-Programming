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
    for (cin >> T; T; T--) {
        int n;
        cin >> n;
        int balance = 0;
        string s;
        cin >> s;
        for (char c : s) {
            balance += (c == '+' ? 1 : -1);
        }
        cout << abs(balance) << "\n";
    }

    return 0;
}
