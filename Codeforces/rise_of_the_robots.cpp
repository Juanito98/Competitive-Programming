/*
    Smalles enclosing circle 
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

typedef long double llf;

struct PT {
    llf x, y;
    PT() {}
    PT(llf x, llf y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator-(const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator*(double c) const { return PT(x * c, y * c); }
    PT operator/(double c) const { return PT(x / c, y / c); }
    bool operator<(const PT &p) const { return x < p.x || (x == p.x && y < p.y); }
};

llf dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
llf dist2(PT p, PT q) { return dot(p - q, p - q); }
llf dist(PT p, PT q) { return sqrt(dist2(p, q)); }

struct Circle {
    PT c;
    llf r;
    Circle() {}
    Circle(const PT &c, double r) : c(c), r(r) {}
};

// O(n * ITER)
const int ITER = 50000;
Circle smallestEnclosingCircle(const vector<PT> &C) {
    PT P(0, 0);
    llf r, alfa = 0.1;
    for (auto p : C)
        P = P + p;
    P = P / C.size();
    for (int it = ITER; it; --it) {
        int idx = 0;
        r = dist2(P, C[0]);
        for (int i = 1; i < C.size(); ++i) {
            llf _rr = dist2(P, C[i]);
            if (r < _rr) {
                idx = i;
                r = _rr;
            }
        }
        P = P + (C[idx] - P) * alfa;
        alfa *= 0.999;
    }
    return Circle(P, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("robots.in", "r")) freopen("robots.in", "r", stdin);
    int T;
    for (cin >> T; T; --T) {
        int n;
        llf R, r;
        cin >> n >> R >> r;
        vector<PT> C(n+1);
        C[0] = PT(0, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> C[i].x >> C[i].y;
            C[i] = C[i] + C[i-1];
        }

        Circle c = smallestEnclosingCircle(C);
        c.c = c.c*-1;
        cout << setprecision(9) << fixed;
        cout << c.c.x << " " << c.c.y << "\n";
    }
    return 0;
}