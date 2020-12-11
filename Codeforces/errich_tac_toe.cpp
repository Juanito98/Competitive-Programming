/*
    Matrix 3-coloring
    Principio de palomas
    https://codeforces.com/contest/1450/problem/C2
*/
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; --T) {
        int n;
        cin >> n;
        char arr[n][n];
        vector<int> cnt(3), cntX(3), cntO(3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> arr[i][j];
                if (arr[i][j] == 'O')
                    cntO[(i + j) % 3]++;
                else if (arr[i][j] == 'X')
                    cntX[(i + j) % 3]++;
            }
        }
        for (int i = 0; i < 3; ++i) cnt[i] = cntX[i] + cntO[i];
        int k = cnt[0] + cnt[1] + cnt[2];
        int O, X;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (i == j) continue;
                if (cntX[i] + cntO[j] <= k / 3) {
                    O = i;
                    X = j;
                }
            }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (arr[i][j] != '.') {
                    if ((i + j) % 3 == O) arr[i][j] = 'O';
                    if ((i + j) % 3 == X) arr[i][j] = 'X';
                }
                cout << arr[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}