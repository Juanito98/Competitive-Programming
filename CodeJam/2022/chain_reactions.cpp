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

const int MAXN = 100002;

int n;
int sig[MAXN];
bool isPointed[MAXN];
lld F[MAXN];

bool belongsToCycle[MAXN];

int vis[MAXN];
int color;
void fillCycle(int node) {
    color++;
    stack<int> p;
    p.push(node);
    vis[node] = color;
    while (true) {
        node = p.top();
        int h = sig[node];
        if (vis[h] > 0) {
            if (vis[h] < color) {
                return;
            }
            int curr = h;
            do {
                belongsToCycle[curr] = true;
                curr = sig[curr];
            } while (curr != h);

            return;
        }
        p.push(h);
        vis[h] = color;
    }
}

void findCycles() {
    fill(belongsToCycle, belongsToCycle + n + 1, false);
    fill(vis, vis + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 0) {
            fillCycle(i);
        }
    }
}

priority_queue<pair<lld, int> > q;
bool reacted[MAXN];

lld reactCycle(int node) {
    lld f = F[node];
    int curr = node;
    do {
        reacted[curr] = true;
        f = max(f, F[curr]);
        curr = sig[curr];
    } while (curr != node);
    return f;
}

lld reaction() {
    lld ans = 0;
    while (!q.empty()) {
        lld f = -q.top().first;
        int node = q.top().second;
        q.pop();
        int h = sig[node];
        if (reacted[h]) {
            ans += f;
            continue;
        }
        if (belongsToCycle[h]) {
            // Termina de reaccionar
            f = max(f, reactCycle(h));
            ans += f;
            continue;
        }
        q.push({-max(f, F[h]), h});
        reacted[h] = true;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        // Read input
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> F[i];
            isPointed[i] = false;
            reacted[i] = false;
        }
        for (int i = 1; i <= n; ++i) {
            cin >> sig[i];
            // Set is pointed
            isPointed[sig[i]] = true;
        }

        findCycles();

        lld ans = 0;
        // react chains
        for (int i = 1; i <= n; ++i) {
            if (!isPointed[i]) {
                q.push({-F[i], i});
                reacted[i] = true;
            }
        }
        ans += reaction();

        // react missing cycles
        for (int i = 1; i <= n; ++i) {
            if (!reacted[i]) {
                ans += reactCycle(i);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
