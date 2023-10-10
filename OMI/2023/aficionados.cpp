#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    int L = -1, R = -1;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && a[i] == a[i-1]) {
            L = i-1;
            R = i;
        }
        if (i > 1 && a[i] == a[i-2]) {
            L = i-2;
            R = i;
        }
    }

    if (L == -1) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << L+1 << " " << R+1 << std::endl;
    }

    return 0;
}