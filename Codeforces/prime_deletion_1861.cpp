#include <iostream>
#include <string>

int ans(const std::string& s) {
    for (auto c : s) {
        if (c == '1') {
            // 1 came first, so 3 will be after
            // Then we can form 13
            return 13;
        } else if (c == '3') {
            // 3 came first, so 1 will be after
            // Then we can form 31
            return 31;
        }
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        std::cout << ans(s) << std::endl;
    }
    return 0;
}