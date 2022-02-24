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

const int MAXN = 1000002;

int n;
int arr[MAXN];

stack <pii> pila;
// Devuelve el tiempo en el que estará libre de diregir
int metePlanta(int x) {
    int t = 0;
    // Mientras me pueda comer a la siguiente
    while (!pila.empty() && pila.top().first < x) {
        t = max(t + 1, pila.top().second);
        pila.pop();
    }
    pila.push({x, t});
    return t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    int ans = 0;
    for (int i = n-1; i >= 0; --i) {
        ans = max(ans, metePlanta(arr[i]));
    }

    cout << ans << "\n";
    return 0;
}