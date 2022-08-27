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

const int MAXN = 5002;

int n;
int arr[MAXN];

int sigTorre[MAXN][MAXN];
void precalculaSigTorre() { // O(n^2)
    for (int j = 0; j < n; ++j) {
        int suma_ij = 0;
        int suma_jk = 0;
        int k = j;
        for (int i = j; i >= 0; --i) {
            suma_ij += arr[i];
            while (k < n && suma_ij > suma_jk) {
                k++;
                suma_jk += arr[k];
            }
            sigTorre[i][j] = k >= n ? -1 : k;
        } 
    }
}

bool vis[MAXN][MAXN];
int memo[MAXN][MAXN];
// Quiero maximizar la cantidad de torres si la última supertorre es de (i,j)
int torres(int i, int j) { // O(n^2)
    if (!vis[i][j]) {
        vis[i][j] = true;
        if (j >= n-1) {
            return memo[i][j] = 1;
        }
        int k = sigTorre[i][j];
        if (k == -1) {
            // No puedo crear una siguiente super torre
            return memo[i][j] = 1;
        }
        // Creo una superTorre nueva o extiendo la que ya existe
        memo[i][j] = max(torres(j + 1, k) + 1, torres(i, j + 1));
    }
    return memo[i][j];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    precalculaSigTorre();
    cout << n - torres(0, 0) << endl;
    return 0;
}
