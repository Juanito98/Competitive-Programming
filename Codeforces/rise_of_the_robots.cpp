/*
    Smallest enclosing circle 
    Check thesis: https://codeforces.com/blog/entry/23554
    2.2 A subgradient method
*/
#include <limits.h>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
struct PT {
    double x, y;
    PT() {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator-(const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator*(double c) const { return PT(x * c, y * c); }
    PT operator/(double c) const { return PT(x / c, y / c); }
    bool operator<(const PT &p) const { return x < p.x || (x == p.x && y < p.y); }
};

double dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double dist(PT p, PT q) { return sqrt(dist2(p, q)); }

// O(n*ITER)
const int ITER = 30000;
PT smallestEnclosingCircle(const vector<PT> &P) {
    PT C(0, 0);
    double r2, alfa = 0.1;
    for (auto p : P)
        C = C + p;
    C = C / P.size();
    for (int it = ITER; it; --it) {
        int idx = 0;
        r2 = dist2(C, P[0]);
        for (int i = 1; i < P.size(); ++i) {
            double _rr2 = dist2(C, P[i]);
            if (r2 < _rr2) {
                idx = i;
                r2 = _rr2;
            }
        }
        C = C + (P[idx] - C) * alfa;
        alfa *= 0.999;
    }
    return C;  // radius = sqrt(r2)
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("robots.in", "r")) freopen("robots.in", "r", stdin);
    int T;
    for (cin >> T; T; --T) {
        int n;
        double R, r;
        cin >> n >> R >> r;
        vector<PT> P(n+1);
        P[0] = PT(0, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> P[i].x >> P[i].y;
            P[i] = P[i] + P[i-1];
        }

        PT C = smallestEnclosingCircle(P);
        C = C*-1;
        cout << setprecision(9) << fixed;
        cout << C.x << " " << C.y << "\n";
    }
    return 0;
}