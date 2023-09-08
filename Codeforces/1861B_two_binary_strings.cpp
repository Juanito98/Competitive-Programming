#include <iostream>
#include <string>

/*
It is possible if there is i such that a[i] = b[i] = 0
and a[i+1] = b[i+1] = 1
*/
bool possible(const std::string& a, const std::string& b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == '0' && b[i] == '0' && a[i+1] == '1' && b[i+1] == '1') {
            return true;
        }
    }
    return false;
}

int main() {
    int cases;
    std::cin >> cases;
    for (int c = 0; c < cases; ++c) {
        std::string a, b;
        std::cin >> a >> b;
        std::cout << (possible(a, b) ? "YES" : "NO") << std::endl;
    }
}