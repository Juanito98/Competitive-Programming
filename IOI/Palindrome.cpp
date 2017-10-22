#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0);
#define MAXN 5002
using namespace std;

int n;
int arr[MAXN];
int memo1[MAXN];
int memo2[MAXN];


// memo2 -> j, memo1 -> j-1

int main()
{
    optimizar;
    cin >> n;
    char aux;

    for(int i=1; i<=n; i++) {
        cin >> aux;
        arr[i]= aux;
    }

    for(int j=1; j<=n; j++) {
        for(int i=j; i>=1; i--) {
            if(arr[i] == arr[j])
                memo2[i]= memo1[i+1];
            else
                memo2[i]= min(memo2[i+1], memo1[i]) + 1;
        }
        for(int i=1; i<=n; i++)
            memo1[i]= memo2[i];
    }

    cout << memo1[1] << "\n";
    return 0;
}