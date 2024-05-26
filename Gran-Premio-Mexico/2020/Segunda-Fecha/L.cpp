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

const int MAXN = 42;

int n, m;
char arr[MAXN][MAXN];

int id;
int special[MAXN][MAXN];

bool check_anagram(string &s, int i, int j, int di, int dj) {
    vector<int> f(30, 0);
    for (auto c : s) {
        f[c - 'A']++;
    }
    int x = i, y = j;
    for (int l = 0; l < s.size(); ++l) {
        if (i < 0 || j < 0 || i >= n || j >= m) return false;
        if (f[arr[i][j] - 'A'] == 0) return false;
        f[arr[i][j] - 'A']--;
        i += di;
        j += dj;
    }
    // Sí es anagrama
    //cout << id << " en " << x << " " << y << endl;
    for (int l = 0; l < s.size(); ++l) {
        special[x][y] |= (1 << id);
        x += di;
        y += dj;
    }
    return true;
}

void mark(string &s) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            check_anagram(s, i, j, -1, 1);
            check_anagram(s, i, j, 0, 1);
            check_anagram(s, i, j, 1, 1);
            check_anagram(s, i, j, 1, 0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> arr[i][j];

    int k;
    cin >> k;
    for (id = 0; id < k; ++id) {
        string st;
        cin >> st;
        mark(st);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (special[i][j] > 0 && (special[i][j] & (-special[i][j])) != special[i][j])
                ans++;

    cout << ans << "\n";

    return 0;
}