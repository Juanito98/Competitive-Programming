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

int main() {
    long long ans = 100;
    long long s = 100;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s += a;
        ans = max(ans, s);
    }
    cout << ans << '\n';
    return 0;
}
