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

const int MAXN = 3002;
const int INF = 1e9;

int n, A, B;

pair <pii, int> arr[MAXN];

int memo[MAXN][MAXN];
bool vis[MAXN][MAXN];
int dp(int i, int b) {
    if (b > i) return -INF;
    if (i <= 0) return 0;
    if (!vis[i][b]) {
        vis[i][b] = true;
        // No lo tomo para B
        memo[i][b] = dp(i - 1, b) + (i - b <= A ? arr[i].first.first : 0); 
        // Tomo para B
        if (b > 0)
            memo[i][b] = max(memo[i][b], dp(i - 1, b - 1) + arr[i].first.second);
    }
    return memo[i][b];
}

void imprime(vector<int> &a) {
    sort(a.begin(), a.end());
    for (int x : a) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> A >> B;
    for (int i = 1; i <= n; ++i) 
        cin >> arr[i].first.first;

    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].first.second;
        arr[i].second = i;
    }

    sort(arr + 1, arr + n + 1);
    reverse(arr + 1, arr + n + 1);

    cout << dp(n, B) << "\n";

    vector <int> idA, idB;

    for (int i = n, b = B; i > 0; --i) {
        // Veo si me conviente ponerlo en B
        if (b > 0 && dp(i, b) == dp(i-1, b-1) + arr[i].first.second) {
            b--;
            idB.push_back(arr[i].second);
        } else if (i - b <= A) {
            idA.push_back(arr[i].second);
        }
    }
    imprime(idA);
    imprime(idB);
    
    

    return 0;
}