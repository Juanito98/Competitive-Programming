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

const int MAXN = 2000002;

struct modelo {
    int costume;
    bool used;
};
modelo arr[MAXN];

int sig[MAXN];
bool matchedSig[MAXN];
bool matchedCurr[MAXN];

int n, m;

bool operator<(modelo a, modelo b) {
    if (a.costume == b.costume) {
        return a.used > b.used;
    }
    return a.costume < b.costume;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";

        cin >> n >> m;
        int cnt = 0;

        for (int i = 0; i < m; ++i) {
            cin >> arr[i].costume;
            arr[i].used = false;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> sig[j];
            }
            fill(matchedSig, matchedSig + m, false);
            fill(matchedCurr, matchedCurr + m, false);
            sort(arr, arr + m);
            sort(sig, sig + m);
            {
                // Quitamos las que tendrán el mismo costume
                int k = 0;
                for (int j = 0; j < m; ++j) {
                    while (k < m && sig[k] < arr[j].costume) {
                        k++;
                    }
                    if (k < m && sig[k] == arr[j].costume) {
                        matchedSig[k] = true;
                        matchedCurr[j] = true;
                        k++;
                    }
                }
            }
            {
                // Matcheamos las que tenemos que matchear
                int k = 0;
                for (int j = 0; j < m; ++j) {
                    if (matchedCurr[j]) continue;
                    while (matchedSig[k]) {
                        k++;
                    }
                    matchedCurr[j] = true;
                    matchedSig[k] = true;
                    if (arr[j].used) {
                        cnt++;
                    } else {
                        arr[j].used = true;
                    }
                    arr[j].costume = sig[k];
                }
            }
            //cout << i << " " << cnt << endl;
        }

        cout << cnt << "\n";


    }

    return 0;
}