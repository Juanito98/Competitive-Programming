#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 105
#define INF 200000.0
using namespace std;
int n;

struct pto {
    int x;
    int y;
};

pto arr[MAXN];
double floyd[MAXN][MAXN];

double dist(pto a, pto b) {
    double x = a.x - b.x;
    double y = a.y - b.y;
    double c = sqrt((x*x) + (y*y));
    if(c > 10.0)
        return INF;
    return c;
}

int main()
{
    optimizar;
    int cases;
    cin >> cases;
    for(int cont = 1; cont <= cases; cont++) {
        cin >> n;

        for(int i=1; i<=n; i++)
            cin >> arr[i].x >> arr[i].y;

        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                floyd[i][j] = dist(arr[i], arr[j]);

        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);

        double resp= -1.0;
        bool imprime = false;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++) {
                if(floyd[i][j] == INF) imprime = true;
                resp = max(resp, floyd[i][j]);
            }

        cout << "Case #" << cont << ":" << "\n";
        if(imprime)
            cout << "Send Kurdy\n";
        else {
            cout.precision(4);
            cout << fixed << resp << "\n";
        }
        cout << "\n";
    }
    return 0;
}
