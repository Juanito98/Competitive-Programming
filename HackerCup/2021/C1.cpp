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

const int MAXN = 52;

int n;
lld arr[MAXN];
vector<int> adj[MAXN];

void clear() {
    for (int i = 1; i <= n; ++i)
        adj[i].clear();
}

lld richestPath(int nodo, int p) {
    lld ans = 0;
    for (auto h : adj[nodo]) {
        if (h == p) continue;
        ans = max(ans, richestPath(h, nodo));
    }
    return ans + arr[nodo];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cin >> n;
        clear();
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
        }        
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        lld p1 = 0, p2 = 0;
        for (int h : adj[1]) {
            lld vh = richestPath(h, 1);
            if (vh > p2) p2 = vh;
            if (p2 > p1) swap(p1, p2);
        }

        cout << "Case #" << caso << ": ";
        cout << arr[1] + p1 + p2 << "\n";
    }

    return 0;
}