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

int deboBorrar[10];
int faltanLlegar[10];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    for (char c : s) {
        faltanLlegar[c-'0']++;
    }
    for (int d = 1; d <= 9; ++d) {
        cin >> deboBorrar[d];
    }

    string ans;
    for (char c : s) {
        int d = c - '0';
        // Checar si lo tengo que eliminar
        if (deboBorrar[d] >= faltanLlegar[d]) {
            deboBorrar[d]--;
            faltanLlegar[d]--;
            continue;
        }
        // No necesariamente lo tengo que poner, vamos a quickear
        while (!ans.empty() && ans.back() < c) {
            // Me conviene quickear
            if (deboBorrar[ans.back()-'0'] > 0) {
                deboBorrar[ans.back()-'0']--;
                ans.pop_back();
            } else {
                break;
            }
        }
        ans.push_back(c);
        faltanLlegar[d]--;
    }
    cout << ans << "\n";

    return 0;
}