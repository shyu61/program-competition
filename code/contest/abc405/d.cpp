#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// 🔷抑えるべき抽象論は？
// 多始点bfsは初期queueに入れる要素が複数になるだけであとはbfsと全く同じ
// dfsやbfs,dpなど順に遷移する操作は、遷移元を保存しておけば経路復元できる

vector<int> dx = {0,0,1,-1}, dy = {1,-1,0,0};
const string direction = "<>^v";

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    queue<P> que;
    vector<vector<P>> dist(h, vector<P>(w, {-1, -1}));
    rep(i, h) rep(j, w) {
        if (mas[i][j] == 'E') {
            que.emplace(i, j);
            dist[i][j] = {0, -1};
        }
    }

    while (!que.empty()) {
        auto [i, j] = que.front(); que.pop();
        rep(r, 4) {
            int nh = i + dx[r], nw = j + dy[r];
            if (nh < 0 || nh >= h || nw < 0 || nw >= w) continue;
            if (mas[nh][nw] != '.') continue;
            if (dist[nh][nw].first != -1) continue;
            que.emplace(nh, nw);
            dist[nh][nw] = {dist[i][j].first + 1, r};
        }
    }

    rep(i, h) rep(j, w) {
        if (mas[i][j] != '.') continue;
        mas[i][j] = direction[dist[i][j].second];
    }

    rep(i, h) cout << mas[i] << '\n';
}
