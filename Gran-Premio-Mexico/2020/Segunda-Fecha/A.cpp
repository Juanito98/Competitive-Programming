/*
    Esperanza condicional + Barrido
    En = 1 + 1/(B-A+1) * sum i=A to B de E{n-i}
*/
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, A, B;
    cin >> n >> A >> B;
    vector<llf> E(n + 1);
    E[0] = 0;
    int l = -B, r = -A;
    llf sum = 0;
    for (int i = 1; i <= n; ++i) {
        // Quito l
        if (l >= 0) sum -= E[l];
        l++;
        // Agrego r
        r++;
        if (r >= 0) sum += E[r];

        E[i] = 1.0 + (1.0 / (llf)(B - A + 1)) * sum;
        if (A == 0) {
            // Corrijo
            E[i] *= (llf)(B + 1.0) / (llf)(B);
            // Corrijo suma
            sum += E[i];
        }
    }

    cout << setprecision(5) << fixed << E[n] << "\n";

    return 0;
}