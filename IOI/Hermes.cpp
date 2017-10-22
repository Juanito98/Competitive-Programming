#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 20002
#define COOR 1000
#define x first
#define y second
using namespace std;

int n;
pair < int, int > arr[MAXN];

int memo[2][COOR * 2 + 5][2]; // i, coor, im_in_x
int ant = 0;
int act = 1;

int f(int a) {
    return a + COOR;
}

int cost(int a, int b) {
    return abs(a - b);
}

void DP() {
    int x, y;
    for(int i = n - 1; i > 0; i--) {
        y = arr[i].y;
        for(x = - COOR; x <= COOR; x++) {
            memo[act][f(x)][false] = min(memo[ant][f(y)][true] + cost(x, arr[i+1].x),
                memo[ant][f(x)][false] + cost(y, arr[i+1].y));
        }
        x = arr[i].x;
        for(y = - COOR; y <= COOR; y++) {
            memo[act][f(y)][true] = min(memo[ant][f(y)][true] + cost(x, arr[i+1].x),
                memo[ant][f(x)][false] + cost(y, arr[i+1].y));
        }
        swap(ant, act);
    }
    x = 0, y = 0;
    memo[act][f(0)][true] = memo[act][f(0)][false] =
        min(memo[ant][f(y)][true] + cost(x, arr[1].x),
                memo[ant][f(x)][false] + cost(y, arr[1].y));
    swap(act, ant);
}

int main()
{
    optimizar;
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> arr[i].x >> arr[i].y;
    DP();
    cout << memo[ant][f(0)][true] << "\n";
    return 0;
}
