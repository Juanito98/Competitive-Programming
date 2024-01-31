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

const int MAXN = 200002;

// Su sig más pequeño a el 
int nextL[MAXN];
// La distancia a su sig más pequeño a la der
int nextR[MAXN]; 

int n;
int arr[MAXN];


void calculateNextL(int ans[] = nextL) {
    // Calculate nextL and put answer in array ans
    stack<int> s;
    for (int i = 0; i < n; ++i) {
        // push it 
        while (!s.empty() && s.top() >= arr[i]) {
            s.pop();
        }
        if (s.empty()) {
            ans[i] = -1;
        } else {
            ans[i] = s.top();
        }
        s.push(arr[i]);
    }
}

void calculateNextR() {
    // Reverse arr
    reverse(arr, arr + n);
    // Calculate nextL
    calculateNextL(nextR);
    // Reverse nextR
    reverse(nextR, nextR + n);
    // reverse arr
    reverse(arr, arr + n);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        calculateNextL();
        calculateNextR();

        int zeros = 0;
        bool possible = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                zeros++;
                continue;
            }
            possible &= (nextL[i] + 1 == arr[i] || nextR[i] + 1 == arr[i]);
        }
        possible &= (zeros == 1);

        cout << (possible ? "YES" : "NO") << "\n";
    }

    return 0;
}
