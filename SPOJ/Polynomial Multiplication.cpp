#include <bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double llf;
typedef complex < llf > base;

const llf M_PI = atan(1) * 4;

void fft(vector < base > &a, bool invert = false) {
    int n = a.size();
    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for(; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if(i < j)
            swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        llf ang = 2*(M_PI) / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len) {
            base w(1);
            for(int j = 0; j < len/2; ++j) {
                base u = a[i + j], v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert) for(int i = 0; i < n; ++i)
        a[i] /= n;
}


void multiply(const vector < lld > &a, const vector < lld > &b, vector < lld > &res) {
    vector < base > fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while(n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa); fft(fb);

    for(size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];

    fft(fa, true);
    res.resize(n);
    for(size_t i = 0; i < n; i++)
        res[i] = (lld) round(fa[i].real());
    res.resize(a.size() + b.size() - 1);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    for(cin >> T; T; --T) {
        int n;
        cin >> n;
        vector < lld > a(n+1), b(n+1);
        for(int i = 0; i <= n; ++i)
            cin >> a[i];
        for(int i = 0; i <= n; ++i)
            cin >> b[i];

        vector < lld > ans; multiply(a, b, ans);
        for(int i = 0; i < ans.size(); ++i)
            cout << ans[i] << " ";
        cout << "\n";
    }
    return 0;
}
