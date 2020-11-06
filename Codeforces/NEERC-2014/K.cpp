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

const int MAXN = 2002;
int n;
int adj[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; T--) {
        cin >> n;
        vector<int> erased(n+1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> adj[i][j];
            }
        }
        vector<pii> edges;
        for (int j = n; j > 1; --j) {
            int nodo = adj[1][j];
            int k = 2;
            for (k = 2; k < n && erased[adj[nodo][k]]; ++k)
                ;
            edges.push_back({nodo, adj[nodo][k]});
            erased[nodo] = true;
        }

        for (auto p : edges) {
            cout << p.first << " " << p.second << "\n";
        }
        if (T > 1) cout << "\n";
    }

    return 0;
}