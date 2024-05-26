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

int main() {
    string c;
    cin >> c;
    int t = c.size();
    bool sacaL = true;
    int curR = 0, curL = 0;
    int wL = 0, wR = 0;
    for (int i = 0; i < t; i++) {
        if (c[i] == 'S') {
            if (sacaL) {
                curL++;
            } else {
                /// sacaR
                curR++;
            }
            if (curL >= 5 && curL - curR >= 2) {
                wL++;
                sacaL = true;
                curL = 0;
                curR = 0;

            } else if (curR >= 5 && curR - curL >= 2) {
                wR++;
                sacaL = false;
                curL = 0;
                curR = 0;
            } else if (curL == 10) {
                wL++;
                sacaL = true;
                curL = 0;
                curR = 0;
            } else if (curR == 10) {
                wR++;
                sacaL = false;
                curL = 0;
                curR = 0;
            }
        } else if (c[i] == 'R') {
            if (sacaL) {
                curR++;
                sacaL = false;
            } else {
                /// sacaR
                curL++;
                sacaL = true;
            }

            if (curL >= 5 && curL - curR >= 2) {
                wL++;
                sacaL = true;
                curL = 0;
                curR = 0;

            } else if (curR >= 5 && curR - curL >= 2) {
                wR++;
                sacaL = false;
                curL = 0;
                curR = 0;
            } else if (curL == 10) {
                wL++;
                sacaL = true;
                curL = 0;
                curR = 0;
            } else if (curR == 10) {
                wR++;
                sacaL = false;
                curL = 0;
                curR = 0;
            }
        } else if (c[i] == 'Q') {
            if (wR >= 2) {
                cout << wL << " - " << wR << " (winner)\n";
            } else if (wL >= 2) {
                cout << wL << " (winner) - " << wR << '\n';
            } else {
                if (sacaL) {
                    cout << wL << " (" << curL << "*) - " << wR << " (" << curR << ")\n";
                } else {
                    cout << wL << " (" << curL << ") - " << wR << " (" << curR << "*)\n";
                }
            }
        }
    }
    return 0;
}
