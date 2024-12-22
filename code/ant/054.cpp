// Union-Find木(食物連鎖): p85
#include <bits/stdc++.h>
using namespace std;

// 集合の問題かつ更新あり -> Union-Findを検討 -> 同集合だけでなく捕食関係を表現する必要がある 
// -> 捕食関係を"異なる集合でないとけない"と表現するか、"同じ集合"として表現するかの2択になる
// -> "異なる集合でないといけない"はUnion-Findの設計思想に反するので表現が難しい
// -> 捕食関係も"同じ集合"として表現したい -> 同じunion木であることは"同時に起こりうる事象"とする必要があることに気付く

// 別の角度から考えるなら、求めたいのは"情報に矛盾がないかどうか"であって、xとyが同じ集合であるかではない
// 従って、矛盾がない事象同士をuniteしていけば良い -> "同時に起こりうる事象"をuniteすると考えることができる

vector<int> par, ranks;

void init(int n) {
    par = ranks = vector<int>(n);
    for (int i = 0; i < n; i++) par[i] = i;
}

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (ranks[x] > ranks[y]) par[y] = x;
    else {
        par[x] = y;
        if (ranks[x] == ranks[y]) ranks[y]++;
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}


int main() {
    int n, k; cin >> n >> k;
    init(n * 3);

    int ans = 0;
    for (int i = 0; i < k; i++) {
        int t, x, y; cin >> t >> x >> y;
        x--; y--;

        if (x < 0 || x >= n || y < 0 || y >= n) {
            cerr << i << endl;
            ans++;
            continue;
        }

        if (t == 1) {
            // xとyが異なるなら加算
            if (same(x, y + n) || same(x, y + n * 2)) {
                cerr << i << endl;
                ans++;
            }
            else {
                unite(x, y);
                unite(x + n, y + n);
                unite(x + n * 2, y + n * 2);
            }
        } else {
            // xとyが捕食関係にないなら加算
            if (same(x, y) || same(x, y * n * 2)) {
                cerr << i << endl;
                ans++;
            }
            else {
                unite(x, y + n);
                unite(x + n, y + n * 2);
                unite(x + n * 2, y);
            }
        }
    }
    cerr << "-----" << endl;
    cout << ans << endl;
}
