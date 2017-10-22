#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
#define INF ( 1 << 30 )
using namespace std;

int n, m;
int memo[MAXN][MAXN];
int arr[MAXN][MAXN];

void DP() {
    for(int i=0; i < n; i++)
        memo[i][m-1]= arr[i][m-1];
    for(int j=m - 2; j>=0; j--) {
        for(int i=0; i<n; i++)
            memo[i][j]= min(memo[(i+n-1)%n][j+1],
                            min(memo[i][j+1], memo[(i+1)%n][j+1])) + arr[i][j];
    }
}

int ind; // auxiliar

int main()
{
    optimizar;

    while(cin >> n) {
        cin >> m;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin >> arr[i][j];

        DP();

        int resp= INF;
        int i=0, j=0;
        for(int a=0; a < n; a++) {
            if(memo[a][j] < resp) {
                resp= memo[a][j];
                i=a;
            }
        }
        int aux= resp;
        cout << i + 1;
        while(j < m - 1) {
            aux-= arr[i][j];
            ind=n;
            j++;
            if(memo[(i+n-1)%n][j] == aux)
                ind= (i+n-1)%n;

            if(memo[i][j] == aux && ind > i)
                ind= i;

            if(memo[(i+1)%n][j] == aux && (i+1)%n < ind)
                ind= (i+1)%n;

            cout << " " << ind + 1;
            i=ind;
        }

        cout << "\n" << resp << "\n";
    }
    return 0;
}
