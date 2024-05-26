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

const int maxN = 10000002;

vector<lld> prime;
bool is_composite[maxN];

void sieve() {
    std::fill(is_composite, is_composite + maxN, false);
    for (lld i = 2; i < maxN; ++i) {
        if (!is_composite[i]) prime.push_back(i);
        for (lld j = 0; j < prime.size() && i * prime[j] < maxN; ++j) {
            is_composite[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sieve();

    string s;
    cin >> s;
    int m = s.size();
    sort(s.begin(), s.end());

    lld ans = LONG_MAX;

    do {
        lld n1 = 0;
        if (s[0] == '0') continue;
        for (int j = 1; j < m; ++j) {
            n1 *= 10;
            n1 += s[j - 1] - '0';
            if (s[j] == '0' || is_composite[n1] || n1 == 1) continue;
            lld n2 = 0;
            for (int k = j + 1; k < m; ++k) {
                n2 *= 10;
                n2 += s[k - 1] - '0';
                if (s[k] == '0' || is_composite[n2] || n2 == 1) continue;
                lld n3 = 0;
                for (int l = k; l < m; ++l) {
                    n3 *= 10;
                    n3 += s[l] - '0';
                }
                if (is_composite[n3] || n3 == 1) continue;
                ans = min(ans, n1 * n2 * n3);
            }
        }
    } while (next_permutation(s.begin(), s.end()));

    if (ans == LONG_MAX) {
        cout << "Bob lies\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}