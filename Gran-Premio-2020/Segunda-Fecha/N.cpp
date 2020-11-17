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
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

typedef int64_t ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

#define MINF -1000000000000
#define MOD 1000000007

#define m(a, b) (a % b + b) % b
#define loop(i, a, b) for (int i = a; i < b; ++i)
#define invl(i, a, b) for (int i = a; i > b; --i)

const int maxN = 31622774;
vector<int> prime;
bool primo[maxN];

void sieve(int n) {
    fill(primo, primo + n, true);
    primo[0] = primo[1] = false;
    for (int i = 2; i < n; ++i) {
        if (primo[i]) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < n; ++j) {
            primo[i * prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    sieve(maxN);

    int it = 0;
    int n, m, k;
    cin >> m >> n >> k;

    ll num[n + 5];
    loop(i, 1, n + 1) {
        cin >> num[i];
    }

    vector<pii> adj[m + 5];
    int a, b, c;
    loop(i, 0, k) {
        cin >> a >> b >> c;
        adj[a].push_back(pii(b, c));
    }

    ll resp[m + 5], nd;
    int indxN;
    for (int i = 1; i <= m; ++i) {
        indxN = adj[i][0].first;
        nd = num[indxN];

        while (it < prime.size() && nd % prime[it] > 0) {
            ++it;
        }

        if (it == prime.size()) {
            resp[i] = nd;
        } else {
            resp[i] = prime[it];
        }

        for (pii x : adj[i]) {
            for (int d = 0; d < x.second; ++d)
                num[x.first] /= resp[i];
        }
    }

    cout << resp[1];
    loop(i, 2, m + 1) {
        cout << " " << resp[i];
    }
    cout << "\n";

    return 0;
}
