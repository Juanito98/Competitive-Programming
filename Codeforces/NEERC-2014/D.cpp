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
typedef pair<lld, int> pli;

int n;
lld m;

vector<pli> zeros, ones;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        lld a, b;
        cin >> a >> b;
        if (b == 0) {
            zeros.push_back({a, i});
        } else {
            ones.push_back({a, i});
        }
    }
    sort(zeros.begin(), zeros.end());
    sort(ones.begin(), ones.end());
    reverse(zeros.begin(), zeros.end());
    reverse(ones.begin(), ones.end());

    if (zeros.empty()) {
        zeros.push_back({0, -1});
        n++;
    }

    vector<lld> sum(zeros.size());
    for (int i = 0; i < zeros.size(); ++i) {
        sum[i] = zeros[i].first;
        if (i > 0) sum[i] += sum[i-1];
    }

    int min_servers = n+1;
    int low_v = 0;

    int j = zeros.size() - 1;

    while (j >= 0 && sum[j] >= m) {
        min_servers = j + 1;
        j--;
    }
    if (j < zeros.size()-1) j++;

    lld acum = 0;
    for (int i = 0; i < ones.size(); ++i) {
        acum += ones[i].first;
        //cout << i << " " << acum << " je\n";
        int used = i + 1;
        if (acum < m) {
            while (j > 0 && acum + sum[j] >= m) {
                j--;
            }
            if (j+1 < zeros.size() && acum + sum[j] < m) j++;
            if (acum + sum[j] < m) continue;
            used += j + 1;
        }
        //cout << i << " " << j << endl;
        if (used < min_servers || (used == min_servers && low_v < i + 1)) {
            min_servers = used;
            low_v = i+1;
        }
    }

    cout << min_servers << " " << low_v << "\n";

    for (int i = 0; i < low_v; ++i) {
        cout << ones[i].second << " ";
    }
    for (int i = 0; i < min_servers - low_v; ++i) {
        cout << zeros[i].second << " ";
    }
    cout << "\n";

    return 0;
}