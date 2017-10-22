#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define lld long long int
using namespace std;

int n, k;
int arr[MAXN];
map < int, int > cubeta;

int resp;

void barrido() {
    int i = 1, j = 0;
    while(i <= n) {
        while(cubeta.size() <= k && j < n) 
            cubeta[arr[++j]]++;
        if(cubeta.size() > k) {
            cubeta.erase(arr[j]);
            j--;
        }
        resp = max(resp, cubeta[arr[i]]);
        cubeta[arr[i]]--;
        if(!cubeta[arr[i]])
            cubeta.erase(arr[i]);
        i++;
    }
}

int main()
{
	optimizar;
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    cin >> n >> k;
    k++;
    for(int i = 1; i <= n; i++) 
        cin >> arr[i];
    barrido();
    cout << resp << "\n";
    return 0;
}