/*
    Suffix array
    https://www.urionlinejudge.com.br/judge/es/problems/view/1530
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
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

// O(nlogn)
vector<int> suffix_array(string& s) {
    s.push_back('$');
    int N = s.size();
    vector<int> p(N), c(N);
    {  // k = 0
        vector<pair<char, int>> a(N);
        for (int i = 0; i < N; ++i)
            a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < N; ++i)
            p[i] = a[i].second;
        for (int i = 1; i < N; ++i)
            c[p[i]] = a[i].first == a[i - 1].first ? c[p[i - 1]] : c[p[i - 1]] + 1;
    }
    for (int k = 0; (1 << k) < N; ++k) {
        for (int i = 0; i < N; ++i)
            p[i] = (p[i] - (1 << k) + N) % N;
        {  // Counting sort
            vector<int> cnt(N), pos(N), p_new(N);
            for (auto x : c)
                cnt[x]++;
            for (int i = 1; i < N; ++i)
                pos[i] = pos[i - 1] + cnt[i - 1];
            for (auto x : p)
                p_new[pos[c[x]]++] = x;
            p = p_new;
        }
        vector<int> c_new(N);
        for (int i = 1; i < N; ++i) {
            pii prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % N]};
            pii now = {c[p[i]], c[(p[i] + (1 << k)) % N]};
            c_new[p[i]] = now == prev ? c_new[p[i - 1]] : c_new[p[i - 1]] + 1;
        }
        c = c_new;
    }
    s.pop_back();
    return vector<int>(p.begin() + 1, p.end());
}

// lcp[i] = lcp(i, i+1)
// lcp(x, y) = min(lcp[x], lcp[x+1], ... lcp[y-1])
vector<int> lcp_array(string& s, vector<int>& p) {
    int N = s.size();
    vector<int> c(N), lcp(N);
    for (int i = 0; i < N; ++i)
        c[p[i]] = i;
    int k = 0;
    for (int i = 0; i < N; ++i) {
        if (c[i] < N - 1) {
            int j = p[c[i] + 1];
            while (max(i, j) + k < N && s[i + k] == s[j + k])
                k++;
            lcp[c[i]] = k;
            k = max(k - 1, 0);
        }
    }
    return lcp;
}

int query(int i, int j, vector<vector<int>>& sparse) {
    int n = sparse[0].size();
    if (i > j) return -1;  // Imposible
    int ans = min(sparse[0][i], sparse[0][j]);
    for (int l = sparse.size() - 1; l >= 0; --l) {
        if (i + (1 << l) <= j) {
            ans = min(ans, sparse[l][i]);
            i += (1 << l);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const int LOG_N = 22;

    string s;
    while (cin >> s) {
        string t;
        for (char c : s)
            if (c != '?') t.push_back(c);
        reverse(t.begin(), t.end());

        int n = t.size();
        vector<int> p = suffix_array(t);
        vector<int> lcp = lcp_array(t, p);
        vector<int> pp(n);
        for (int i = 0; i < n; ++i) {
            pp[p[i]] = i;
        }

        // Sparse table
        vector<vector<int>> sparse(LOG_N, vector<int>(n, 0));
        sparse[0] = lcp;
        for (int l = 1; l < LOG_N; ++l) {
            for (int i = 0; i < n; ++i) {
                if (i + (1 << (l - 1)) >= n) break;
                sparse[l][i] = min(sparse[l - 1][i], sparse[l - 1][i + (1 << (l-1))]);
            }
        }
        vector<lld> dp(n);
        lld curr = 0;
        int j = 0;
        set<int> yaMeti;
        for (int i = 0; i < n; ++i) {
            while (s[j] == '?') {
                cout << curr << "\n";
                j++;
            }
            // Calcula dp
            if (i > 0) dp[i] = dp[i - 1];
            int idx = n - i - 1;

            auto it = yaMeti.lower_bound(pp[idx]);
            // Vemos el sig
            int menor = i + 1;
            if (it != yaMeti.end()) {
                int l = query(pp[idx], *it - 1, sparse);
                menor = min(menor, i + 1 - l);
            }
            if (it != yaMeti.begin()) {
                --it;
                int l = query(*it, pp[idx] - 1, sparse);
                menor = min(menor, i + 1 - l);
            }
            yaMeti.insert(pp[idx]);
            dp[i] += menor;
            curr = dp[i];
            j++;
        }
        while (j < s.size() && s[j] == '?') {
            cout << curr << "\n";
            j++;
        }
    }

    return 0;
}