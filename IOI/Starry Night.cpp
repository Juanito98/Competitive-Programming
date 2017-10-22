#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
using namespace std;

int n, m;
int arr[MAXN][MAXN];

int matriz[MAXN][MAXN];


struct ura {
    int N, S, E, O;
    int c;

    bool cmp1(int x1, int x2, int stepx, int y1, int y2, int stepy) {
        int a = 1, b;
        for(int i = x1; i != x2; i += stepx) {
            b = 1;
            for(int j = y1; j != y2; j+= stepy) {
                if(arr[i][j] == c && !matriz[a][b]) return false;
                if(arr[i][j] != c && matriz[a][b]) return false;
                b++;
            }
            a++;
        }
        return true;
    }

    bool cmp2(int x1, int x2, int stepx, int y1, int y2, int stepy) {
        int a = 1, b;
        for(int j = y1; j != y2; j+= stepy) {
            b = 1;
            for(int i = x1; i != x2; i += stepx) {
                if(arr[i][j] == c && !matriz[a][b]) return false;
                if(arr[i][j] != c && matriz[a][b]) return false;
                b++;
            }
            a++;
        }
        return true;
    }

    bool check(ura &b) {
        if(S - N + 1 == b.S - b.N + 1 && E - O + 1 == b.E - b.O + 1) {
            if(cmp1(N, S + 1, 1, O, E + 1, 1)) return true;
            if(cmp1(N, S + 1, 1, E, O - 1, -1)) return true;
            if(cmp1(S, N - 1, -1, O, E + 1, 1)) return true;
            if(cmp1(S, N - 1, -1, E, O - 1, -1)) return true;
        }
        if(E - O + 1 == b.S - b.N + 1 && S - N + 1 == b.E - b.O + 1) {
            if(cmp2(N, S + 1, 1, O, E + 1, 1)) return true;
            if(cmp2(N, S + 1, 1, E, O - 1, -1)) return true;
            if(cmp2(S, N - 1, -1, O, E + 1, 1)) return true;
            if(cmp2(S, N - 1, -1, E, O - 1, -1)) return true;
        }
        return false;
    }

    bool igual(ura &b) {
        for(int i = b.N; i <= b.S; i++)
            for(int j = b.O; j <= b.E; j++)
                matriz[i - b.N + 1][j - b.O + 1] = arr[i][j] == b.c ? 1 : 0;

        bool flag = check(b);

        for(int i = b.N; i <= b.S; i++)
            for(int j = b.O; j <= b.E; j++)
                matriz[i - b.N + 1][j - b.O + 1] = 0;

        return flag;
    }
};

vector < ura > clusters;
int padre[MAXN];

int mov[8][2] = {
-1, -1,
-1, 0,
-1, 1,
0, -1,
0, 1,
1, -1,
1, 0,
1, 1,
};

void colorea(int i, int j, ura &nueva) {
    if(arr[i][j] != -1) return;
    arr[i][j] = nueva.c;
    nueva.N = min(nueva.N, i);
    nueva.S = max(nueva.S, i);
    nueva.E = max(nueva.E, j);
    nueva.O = min(nueva.O, j);
    for(int k = 0; k < 8; k++)
        colorea(i + mov[k][0], j + mov[k][1], nueva);
}

int main()
{
    optimizar;
    int color = 0;
    cin >> m >> n;
    char car;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            cin >> car;
            if(car == '1') arr[i][j] = -1;
        }
    ura nueva;
    bool flag;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(arr[i][j] == -1) {
                nueva.N = nueva.S = i;
                nueva.E = nueva.O = j;
                nueva.c = ++color;
                colorea(i, j, nueva);
                flag = true;
                for(int k = 0; k < clusters.size(); k++) {
                    if(clusters[k].igual(nueva)) {
                        padre[color] = k;
                        flag = false; break;
                    }
                }
                if(flag) { padre[color] = clusters.size(); clusters.push_back(nueva); };
            }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            car = arr[i][j] ? padre[arr[i][j]] + 'a' : '0';
            cout << car;
        }
        cout << "\n";
    }
    return 0;
}
