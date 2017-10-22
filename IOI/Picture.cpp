#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 5002
using namespace std;

int n;
int upper[20002];
int lower[20002];
int left_[20002];
int right_[20002];

int ind1, ind2;

struct rectangle {
    int x1, x2, y1, y2;

    void update(int arr[ ], int i, int j) { arr[i]++; arr[j]--; }

    void substract(rectangle &b) {
        //upper
        if(x1 >= b.x1 && x1 <= b.x2)
        if(y2 > b.y1 && y1 < b.y2) {
            if(x1 != b.x1 && x1 != b.x2) {
                update(upper, max(y1, b.y1) - y1 + 1, min(b.y2, y2) - y1 + 1);
            } else {
                if(ind1 > ind2 || x1 == b.x2)
                    update(upper, max(y1, b.y1) - y1 + 1, min(b.y2, y2) - y1 + 1);
            }
        }
        //lower
        if(x2 >= b.x1 && x2 <= b.x2)
        if(y2 > b.y1 && y1 < b.y2) {
            if(x2 != b.x1 && x2 != b.x2) {
                update(lower, max(y1, b.y1) - y1 + 1, min(b.y2, y2) - y1 + 1);
            } else {
                if(ind1 > ind2 || x2 == b.x1)
                    update(lower, max(y1, b.y1) - y1 + 1, min(b.y2, y2) - y1 + 1);
            }
        }

        //left
        if(y1 >= b.y1 && y1 <= b.y2)
        if(x2 > b.x1 && x1 < b.x2) {
            if(y1 != b.y1 && y1 != b.y2) {
                update(left_, max(x1, b.x1) - x1 + 1, min(b.x2, x2) - x1 + 1);
            } else {
                if(ind1 > ind2 || y1 == b.y2)
                    update(left_,  max(x1, b.x1) - x1 + 1, min(b.x2, x2) - x1 + 1);
            }
        }
        //right
        if(y2 >= b.y1 && y2 <= b.y2)
        if(x2 > b.x1 && x1 < b.x2) {
            if(y2 != b.y1 && y2 != b.y2) {
                update(right_,  max(x1, b.x1) - x1 + 1, min(b.x2, x2) - x1 + 1);
            } else {
                if(ind1 > ind2 || y2 == b.y1)
                    update(right_,  max(x1, b.x1) - x1 + 1, min(b.x2, x2) - x1 + 1);
            }
        }
    }
};
rectangle arr[MAXN];

void init() {
    for(int i = 1; i <= arr[ind1].y2 - arr[ind1].y1 + 1; i++)
        upper[i] = lower[i] = 0;
    for(int i = 1; i <= arr[ind1].x2 - arr[ind1].x1 + 1; i++)
        left_[i] = right_[i] = 0;
}

int P;
void count() {
    for(int i = 1; i <= arr[ind1].y2 - arr[ind1].y1; i++) {
        upper[i] += upper[i - 1];
        lower[i] += lower[i - 1];
        if(!lower[i]) P++;
        if(!upper[i]) P++;
    }
    for(int i = 1; i <= arr[ind1].x2 - arr[ind1].x1; i++) {
        left_[i] += left_[i - 1];
        right_[i] += right_[i - 1];
        if(!left_[i]) P++;
        if(!right_[i]) P++;
    }
}

int main()
{
    optimizar;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr[i].y1 >> arr[i].x1 >> arr[i].y2 >> arr[i].x2;

    for(ind1 = 1; ind1 <= n; ind1++) {
        init();
        for(ind2 = 1; ind2 <= n; ind2++) {
            if(ind1 == ind2) continue;
            arr[ind1].substract(arr[ind2]);
        }
        count();
    }
    cout << P << "\n";
    return 0;
}