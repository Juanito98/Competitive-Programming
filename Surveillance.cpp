#include <bits/stdc++.h>
#define lld long long int
using namespace std;
const int MAXN = 2000002;
const int LOGN = 31;

int skip[MAXN][LOGN];

int d(pair < int, int > a, pair < int, int > b) {
    return b.second - a.first + 1;
}

int minCameras(int n, vector < pair < int, int > > rangos) {
    if(!n) return 0;
    int m = rangos.size();
    int j = 0;
    for(int i = 0; i < m; i++) {
        while(j < m - 1 && rangos[j + 1].first - 1 <= rangos[i].second) j++;
        skip[i][0] = j == i ? -1 : j;
    }
    for(j = 1; j < LOGN; j++) {
        for(int i = 0; i < m; i++) {
            skip[i][j] = -1;
            if(skip[i][j - 1] == -1) continue;
            skip[i][j] = skip[skip[i][j - 1]][j - 1];
        }
    }
    int r = m + 1;
    for(int i = 0; i < m; i++) {
        int act = i, c = 1;
        if(rangos[i].second - rangos[i].first + 1 >= n) return 1;
        for(j = LOGN - 1; j >= 0; j--) {
            if(skip[act][j] == -1) continue;
            if(d(rangos[i], rangos[skip[act][j]]) < n) {
                act = skip[act][j];
                c += (1 << j);
            }
        }
        if(skip[act][0] == -1) continue;
        act = skip[act][0]; c++;
        if(d(rangos[i], rangos[act]) >= n) r = min(r, c);
    }
    return r > m ? -1 : r;
}

bool f(pair < int, int > a, pair < int, int > b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    while(cin >> n >> k) {
        vector < pair < int, int > > rangos;
        for(int i = 1; i <= k; i++) {
            int a, b;
            cin >> a >> b;
            if(a <= b) {
                rangos.push_back(make_pair(a, b));
                rangos.push_back(make_pair(a + n, b + n));
            } else {
                rangos.push_back(make_pair(a, b + n));
            }
        }
        sort(rangos.begin(), rangos.end(), f);
        vector < pair < int, int > > arr;
        arr.push_back(rangos[0]);
        for(int i = 1; i < rangos.size(); i++) {
            if(rangos[i].second > arr.back().second)
                arr.push_back(rangos[i]);
        }
        int r = minCameras(n, arr);
        if(r == -1) cout << "impossible\n";
        else cout << r << "\n";
    }
    return 0;
}
