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

const int MAXN = 1002, MAXK = 12;

bool vis[MAXN][MAXK];
bool memo[MAXN][MAXK];

vector<int> contacted[MAXN][MAXK];  // quién contactó la persona i el día k

bool contactOtherAfterInfection(int nodo, int k) {
    for (int i = k + 2; i < MAXK; ++i) {
        if (contacted[nodo][i].size() > 0) {
            return true;
        }
    }
    return false;
}

// canCatchDisease tells you if person nodo could have catched
// disease on day k
bool canCatchDisease(int nodo, int k) {
    if (!vis[nodo][k]) {
        vis[nodo][k] = true;
        if (contactOtherAfterInfection(nodo, k)) {
            return memo[nodo][k] = false;
        }
        if (k == 0) {
            return memo[nodo][k] = true;
        }
        for (int i = 0; i < contacted[nodo][k].size(); ++i) {
            int other = contacted[nodo][k][i];
            if (canCatchDisease(other, k - 1)) {
                return memo[nodo][k] = true;
            }
        }
    }
    return memo[nodo][k];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k, c;
    cin >> n >> k >> c;
    for (int i = 0; i < c; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        contacted[a][t].push_back(b);
        contacted[b][t].push_back(a);
    }
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (canCatchDisease(i, k)) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << "\n";
    }
    return 0;
}
