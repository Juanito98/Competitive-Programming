#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    int sum = a + b + c;
    int ab = a + b;
    int ac = a + c;
    int bc = b + c;
    int ans = 5005;
    if (sum >= 500) {
        sum -= 100;
    }
    ans = min(ans, sum);
    if (c >= 500) {
        ab = ab >= 500 ? ab - 100 : ab;
        ans = min(ab + c - 100, ans);
    } else {
        ab = ab >= 500 ? ab - 100 : ab;
        ans = min(ab + c, ans);
    }

    if (b >= 500) {
        ac = ac >= 500 ? ac - 100 : ac;
        ans = min(ac + b - 100, ans);
    } else {
        ac = ac >= 500 ? ac - 100 : ac;
        ans = min(ac + b, ans);
    }

    if (a >= 500) {
        bc = bc >= 500 ? bc - 100 : bc;
        ans = min(bc + a - 100, ans);
    } else {
        bc = bc >= 500 ? bc - 100 : bc;
        ans = min(bc + a, ans);
    }
    if (a >= 500 && b >= 500 && c >= 500) {
        ans = min(ans, a - 100 + b - 100 + c - 100);
    }
    cout << ans << '\n';
    return 0;
}
