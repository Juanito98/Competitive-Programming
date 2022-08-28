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

const int MAXN = 502;
const int MAXS = 102;
const int INF = 1e9;

int n, S;
pair<int, int> arr[MAXN];  // first -> puntos, second -> tiempo

bool vis[MAXN][MAXS];
int memo[MAXN][MAXS];
// regresa la menor cantidad de tiempo para juntar S puntos al menos, si ya tengo p
int troto(int i, int p) {
    if (p >= S) {
        return 0;
    }
    if (i >= n) {
        // Ya terminamos de evaluar sobre tomar o no tomar tareas, y no llegamos a S
        return INF;
    }
    if (!vis[i][p]) {
        vis[i][p] = true;
        // Min entre tomar y no tomar
        memo[i][p] = min(
            troto(i + 1, p),                                // NO tomar
            troto(i + 1, p + arr[i].first) + arr[i].second  // Tomar (implica un costo en tiempo de arr[i].second)
        );
    }
    return memo[i][p];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> S;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
    }

    cout << troto(0, 0);

    return 0;
}
