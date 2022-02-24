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

const int L = 30;

int floyd[L][L];  // Cuanto me tardo en cambiar i -> j

void clear() {
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j)
            floyd[i][j] = -1;
        floyd[i][i] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        string s;
        cin >> s;
        int k;
        cin >> k;
        clear();

        for (int i = 0; i < k; ++i) {
            char a, b;
            cin >> a >> b;
            if (a != b) floyd[a - 'A'][b - 'A'] = 1;
        }

        for (int l = 0; l < L; ++l) {
            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L; ++j) {
                    if (floyd[i][l] == -1 || floyd[l][j] == -1) continue;
                    if (floyd[i][j] == -1) {
                        floyd[i][j] = floyd[i][l] + floyd[l][j];
                    } else {
                        floyd[i][j] = min(floyd[i][j], floyd[i][l] + floyd[l][j]);
                    }
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < L; ++i) {
            int curr = 0;
            for (auto c : s) {
                if (floyd[c - 'A'][i] == -1) {
                    curr = -1;
                    break;
                }
                curr += floyd[c - 'A'][i];
            }
            if (ans == -1) ans = curr;
            if (curr != -1) ans = min(curr, ans);
        }

        cout << "Case #" << caso << ": ";
        cout << ans << "\n";
    }

    return 0;
}