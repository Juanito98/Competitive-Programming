#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
using namespace std;

int n;
int arr[MAXN];

int v[2000000];

int main() {
    optimizar;
	int i, j, k, resp, p, val;
	cin >> n;
	resp = p = 0;

	for(i=0; i < n; i++)
        cin >> arr[i];

	for(i=0; i<n; i++)
        if( arr[i] )
            for(j=0 ; j<n; j++)
                for(k=0 ; k<n; k++)
                    v[p++] = arr[i]*(arr[j]+arr[k]);

	sort(v, v+p);
	for(i=0 ; i<n; i++) {
		for(j=0 ; j<n; j++) {
			for(k=0 ; k<n; k++) {
				val = arr[i]*arr[j]+arr[k];
				resp += upper_bound( v, v+p, val) - lower_bound( v, v+p, val );
			}
		}
	}

	cout << resp << "\n";
	return 0;
}

