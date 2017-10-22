#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0)
#define lld long long int
#define MAXN 5610
using namespace std;

lld DP[MAXN];
pair < lld, lld > arr[MAXN];

lld _min(lld a, lld b) {
    if(a == -1) return b;
    if(b == -1) return a;
    return a < b ? a : b;
}

int main()
{
    optimizar;
    int n = 1;
    while(cin >> arr[n].second)
        cin >> arr[n++].first;
    n--;
    sort(arr + 1, arr + n + 1);
    for(int i = 1; i <= n; i++) DP[i] = -1;
    for(int i = 1; i <= n; i++)
        for(int j = i; j >= 1; j--) {
            if(DP[j-1] == -1) continue;
            DP[j] = _min(DP[j], DP[j - 1] + arr[i].second <= arr[i].first ? DP[j - 1] + arr[i].second : DP[j]);
        }
    for(int i = n; i >= 0; i--)
        if(DP[i] != -1) {
            cout << i << "\n";
            break;
        }
    return 0;
}
