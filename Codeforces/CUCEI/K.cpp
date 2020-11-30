#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int med3(int a, int b, int c) {
    cout << "? " << a << " " << b << " " << c << "\n";
    cout.flush();
    int x;
    cin >> x;
    return x;
}

void answer(int x) {
    cout << "! " << x << "\n";
    cout.flush();
}

int ternary_search(vector<int>& arr, int i, int j, int kth, int smallest, int greatest) {
    if (i == j) return arr[i];
    int len = j - i + 1;
    int pivot1 = arr[i + (rand() % len)];
    int pivot2 = arr[i + (rand() % len)];
    while (pivot1 == pivot2)
        pivot2 = arr[i + (rand() % len)];

    if (smallest != -1 || greatest != -1) {
        // Si hay un orden ya
        if (smallest != -1) {
            int f = med3(smallest, pivot1, pivot2);
            if (f == pivot2) {
                swap(pivot1, pivot2);
            }
        } else {
            int f = med3(pivot1, pivot2, greatest);
            if (f == pivot1) {
                swap(pivot1, pivot2);
            }
        }
    }

    vector<int> L, R, M;
    for (int a = i; a <= j; ++a) {
        if (arr[a] == pivot1) continue;
        if (arr[a] == pivot2) continue;
        int f = med3(pivot1, arr[a], pivot2);
        if (f == pivot1) {
            L.push_back(arr[a]);
        } else if (f == pivot2) {
            R.push_back(arr[a]);
        } else {
            M.push_back(arr[a]);
        }
    }

    int p = i;
    for (int x : L) arr[p++] = x;
    arr[p++] = pivot1;
    for (int x : M) arr[p++] = x;
    arr[p++] = pivot2;
    for (int x : R) arr[p++] = x;

    if (L.size() + 1 == kth) return pivot1;
    if (L.size() + 1 + M.size() + 1 == kth) return pivot2;

    if (kth <= L.size()) return ternary_search(arr, i, i + L.size() - 1, kth, -1, pivot1);
    if (kth <= L.size() + 1 + M.size()) return ternary_search(arr, i + L.size() + 1, i + L.size() + M.size(), kth - L.size() - 1, pivot1, pivot2);
    return ternary_search(arr, i + L.size() + M.size() + 2, j, kth - L.size() - M.size() - 2, pivot2, -1);
}

void medianStrength(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = i + 1;
    answer(ternary_search(arr, 0, n - 1, (n + 1) / 2, -1, -1));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    medianStrength(n);

    return 0;
}