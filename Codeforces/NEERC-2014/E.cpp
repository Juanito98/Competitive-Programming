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
typedef pair<int, int> pii;

bool isWinner(pii p) {
    return p.first > p.second;
}

pii operator + (pii a, pii b) {
    return {a.first + b.first, a.second + b.second};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> arr(n);

    int winner = 0;
    int tot = n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        if (isWinner(arr[i]))
            winner++;
    }

    vector<pii> ans;
    for (int i = 1; winner * 2 <= tot && i < n; ++i) {
        // Intentaré juntar i con i-1
        // No juntar GG
        if (isWinner(arr[i]) && isWinner(arr[i-1])) continue;
        bool juntar = false;
        if (!isWinner(arr[i]) && !isWinner(arr[i-1]))
            juntar = true;
        if (isWinner(arr[i] + arr[i-1]))
            juntar = true;
        if (juntar) {
            tot--;
            ans.push_back({i, i + 1});
            i++;
        }
    }

    if (winner * 2 > tot) {
        cout << ans.size() << "\n";
        for (auto p : ans) {
            cout << p.first << " " << p.second << "\n";
        }
    } else {
        cout << "-1\n";
    }

    return 0;
}