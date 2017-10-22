#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define llf long double
using namespace std;
const int MAXN = 100002;

int c;
lld res[3];

int main()
{
    optimizar;
    string S;
    while(cin >> S) {
        c = res[1] = res[2] = 0;
        res[0] = 1;
        lld r = 0;
        for(int i = 0; i < S.size(); i++) {
            if(S[i] < '0' || S[i] > '9') {
                c = res[1] = res[2] = 0;
                res[0] = 1;
                continue;
            }
            c += S[i] - '0';
            c %= 3;
            r += res[c];
            res[c]++;
        }
        cout << r << "\n";
    }
    return 0;
}
