#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define INF (1 << 30)
#define MAXN 1002
#define MAX_M 2002
using namespace std;

int n, m;

struct ura {
    int a, b;
    int c;
};
ura arr[MAX_M];

bool cicloNegativo;

void bellmanFord() {
    int dist[MAXN];
    for(int i=0; i<=n+1; i++)
        dist[i]= INF;
    dist[0]= 0;

    for(int i=1; i <= n - 1; i++) {
        for(int j=1; j<=m; j++) {
            if(dist[arr[j].a] != INF && dist[arr[j].a] + arr[j].c < dist[arr[j].b])
                dist[arr[j].b] = dist[arr[j].a] + arr[j].c;
        }
    }

    for(int j=1; j <= m; j++)
        if(dist[arr[j].a] != INF && dist[arr[j].a] + arr[j].c < dist[arr[j].b])
            cicloNegativo = true;
}

int main() {
	optimizar;

	int cases;
	int a, b, c;
	for(cin >> cases; cases >= 1; cases--) {

        cin >> n >> m;
        for(int i=1; i<=m; i++)
            cin >> arr[i].a >> arr[i].b >> arr[i].c;

        cicloNegativo= false;
        bellmanFord();

        if(cicloNegativo)
            cout << "possible\n";
        else
            cout << "not possible\n";
	}

	return 0;
}
