// Lake Counting: p35
#include <bits/stdc++.h>
using namespace std;

// 問題のジャンルはグリッド問題かつ到達可能性問題
// 連結成分の個数を求める問題なので、dfsで到達可能な範囲を求め、それが何回の実行が必要かで連結成分の数をカウントする, 多分union-findでも解ける
// dfsなどで状態遷移する際の計算量は、O(状態数 x 遷移パターン)になる
// 今回は各マスは1回ずつしか呼び出されず、遷移パターンは8通りなので、O(8*n*m)になる

int n, m;
vector<vector<bool>> a;
vector<vector<int>> r{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

void dfs(int h, int w) {
    a[h][w] = false;
    for (int i = 0; i < 8; i++) {
        int nh = h + r[i][1];
        int nw = w + r[i][0];
        if (nh >= 0 && nh < n && nw >= 0 && nw < m) {
            if (a[nh][nw]) dfs(nh, nw);
        }
    }
}

int main() {
    cin >> n >> m;
    a = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char s; cin >> s;
            a[i][j] = s == 'W';
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) continue;
            dfs(i, j);
            ans++;
        }
    }

    cout << ans << endl;
}
