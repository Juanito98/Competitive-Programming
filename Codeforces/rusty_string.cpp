/*
    FFT Problem
    https://codeforces.com/contest/827/problem/E
*/
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
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
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
typedef complex<double> base;

void fft(vector<base>& a, bool invert) {
    int n = (int)a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * (M_PI) / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; ++j) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> res(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = (int)round(fa[i].real());
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; --T) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        // Creamos A y B
        vector<int> A(n), B(n);
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'V') A[i] = 1;
            if (s[i] == 'K') B[n - i - 1] = 1;
        }

        vector<int> arr = multiply(A, B);

        // Checar periodos
        vector<int> res;
        for (int k = 1; k <= n; ++k) {
            bool period = true;
            for (int i = n - 1; i >= 0; i -= k)
                if (arr[i] > 0) period = false;  // No hay periodo
            // Hacia delante
            for (int i = n - 1; i < arr.size(); i += k)
                if (arr[i] > 0) period = false;  // No hay periodo

            if (period) res.push_back(k);
        }

        cout << res.size() << "\n";
        for (int k : res) {
            cout << k << " ";
        }
        cout << "\n";
    }

    return 0;
}