#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 10000002
using namespace std;

int n, k, m;
int arr[MAXN];

lld R[MAXN];
lld L[MAXN];

int dist(int a, int b) {
    if(a > b) return dist(b, a);
    return min(b - a, a + m - b);
}

lld solve() {
    lld S = 0;
    int ultima = 0;
    
    for(int i = 1; i <= n; i++) {
        L[i] = arr[i] + dist(0, arr[i]);
        if(i > k) L[i] += L[i - k];
    }
    for(int i = n; i >= 1; i--) {
        R[i] = m - arr[i] + dist(0, arr[i]);
        if(i + k <= n) R[i] += R[i + k]; 
    }
    
    lld r = m * 1ll * n * 1ll;
    for(int i = 0; i <= n; i++) 
        r = min(r, L[i] + R[i + 1]);
    return r;
}

int main()
{
    optimizar;
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++) 
        cin >> arr[i];

    cout << solve() << "\n";
    return 0;
}
