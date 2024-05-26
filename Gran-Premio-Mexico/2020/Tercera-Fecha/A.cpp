#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef int64_t ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

#define MINF -1000000000000
#define MOD 1000000007

#define m(a, b) (a % b + b) % b
#define loop(i, a, b) for (int i = a; i < b; ++i)
#define invl(i, a, b) for (int i = a; i > b; --i)

const int maxN = 2 * 1e5 + 5;
const int maxT = 12, maxP = 105, maxE = 105;
int t, p;
int energy[maxT], dif[maxP], score[maxP];

int dp[2048 + 10][maxP][maxE];
bool visited[2048 + 10][maxP][maxE];

int DP(int mask, int pi, int acum) {
    if (acum > 100) return -1000000;
    if (mask == ((1 << t) - 1) || pi == p) return acum > 0 ? -1000000 : 0;

    if (!visited[mask][pi][acum]) {
        visited[mask][pi][acum] = 1;
        int op1, op2, op3;
        //lo resuelvo
        op1 = score[pi] + DP(mask, pi + 1, acum + dif[pi]);

        //lo resuelvo y corto
        op2 = -1000000;
        int indxMin = -1, difMin = 10000000;
        for (int i = 0; i < t; ++i) {
            if (((1 << i) & mask) == 0 && energy[i] >= acum + dif[pi]) {
                if (difMin > energy[i] - acum - dif[pi]) {
                    indxMin = i;
                    difMin = energy[i] - acum - dif[pi];
                }
            }
        }
        if (indxMin > -1) {
            op2 = score[pi] + DP((mask | (1 << indxMin)), pi + 1, 0);
        }

        //no resuelvo
        op3 = DP(mask, pi + 1, acum);

        dp[mask][pi][acum] = max(op1, max(op2, op3));
    }
    return dp[mask][pi][acum];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    cin >> t >> p;
    loop(i, 0, t) {
        cin >> energy[i];
    }
    loop(i, 0, p) {
        cin >> dif[i];
    }
    loop(i, 0, p) {
        cin >> score[i];
    }

    cout << DP(0, 0, 0) << "\n";
}
