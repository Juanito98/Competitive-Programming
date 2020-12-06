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

int n, G;
int total;
int arr[22];

vector<pii> res[22]; // score, msc



void genera(int i, int msc, int score, int taken) {
    if (i >= n) {
        if (score * 100 >= G * total)
            res[taken].push_back({msc, score});
    } else {
        // no tomar
        genera(i+1, msc, score, taken);
        // tomar
        genera(i+1, msc|(1 << i), score+arr[i], taken+1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> G;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        total += arr[i];
    }
    genera(0, 0, 0, 0);

    {
        int i = 0;
        for (; res[i].empty(); ++i);
        sort(res[i].begin(), res[i].end());
        cout << i << " " << res[i].size() << "\n";
        for (auto p : res[i]) {
            int msc = p.first;
            cout << (p.second * 100) / total;
            for (int j = 0; j < n; ++j) {
                if (msc & (1 << j))
                    cout << " " << j+1;
            }
            cout << "\n";
        }
    }

    return 0;
}