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

int n;

pii apply(const vector<vector<char>>& a, int i, int j) {
    if (i < 0 || i >= 2 || j < 0 || j >= n) {
        return {-1, -1};
    }
    if (a[i][j] == '>') return {i, j + 1};
    if (a[i][j] == '<') return {i, j - 1};
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; --T) {
        cin >> n;
        vector<vector<char>> a(2, vector<char>(n));
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> a[i][j];
            }
        }
        vector<vector<bool>> vis(2, vector<bool>(n, false));
        queue<pii> q;
        q.push({0, 0});
        bool possible = false;
        while(!q.empty() && !possible) {
            auto [i, j] = q.front();
            q.pop();
            if (i == 1 && j == n - 1) {
                possible = true;
                continue;
            }
            if (i < 0 || i >= 2 || j < 0 || j >= n || vis[i][j]) {
                continue;
            }
            vis[i][j] = true;
            q.push(apply(a, i + 1, j));
            q.push(apply(a, i - 1, j));
            q.push(apply(a, i, j + 1));
            q.push(apply(a, i, j - 1));
        }
        cout << (possible ? "YES" : "NO") << "\n";
    }
    return 0;
}
