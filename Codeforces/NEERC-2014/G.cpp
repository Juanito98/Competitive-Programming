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

    int n, k;
    cin >> n >> k;
    vector<lld> arr(n);

    lld minimo = 0;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        minimo = min(minimo, arr[i]);
    }


    stack<int> restar; // Cuanto puedo restar

    int j;
    lld suma = 0;
    for (j = 0; j < k; ++j) {
        suma += arr[j];
        restar.push(j);
    }

    lld ans = 0;
    for (int i = 0; j <= n; ++i) {
        //cout << i << " " << j << " " << suma << endl;
        // checa
        while (suma >= 0) {
            int sig = restar.top();
            lld quita = min(suma + 1, arr[sig] - minimo);
            ans += quita;
            arr[sig] -= quita;
            suma -= quita;
            if (arr[sig] == minimo) {
                restar.pop();
            }
        }
        // slide
        suma -= arr[i];
        if (j < n) {
            restar.push(j);
            suma += arr[j];
        }
        j++;
    }

    cout << ans << "\n";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}