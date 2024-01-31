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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for (cin >> T; T; T--) {
        int n;
        cin >> n;
        int a = n + 2; // n + 2 is greater than any A_i
        int b = n + 2;
        
        int penalty = 0;
        for (int i = 0; i < n; ++i) {
            // w.l.o.g. a <= b
            if (b < a) {
                swap(a, b);
            }

            int x;
            cin >> x;
            if (x <= a) { // x <= a <=b. No penalty
                a = x;
            } else if (x > b) { // x > b >= a. There will be penalty
                a = x;
                penalty++;
            } else { // a < x < b. Chose no penalty for one penalty free in future
                /*
                If we've chosen a=x, we would've had to pay a penalty and heads would be
                (a'= x, b' = b)
                But if we choose b=x, we don't have to pay a penalty and heads would be
                (a'= a, b' = x).
                To prove optimally, we could treat a' as b for "free"
                (a' = x, b' = b fake ) b fake is a with penalty of replacing b
                */
                b = x;
            }
        }

        cout << penalty << "\n";
    }

    return 0;
}
