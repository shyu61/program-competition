#include <bits/stdc++.h>
using namespace std;

struct Node {
    int depth;
    vector<int> p;
    array<int, 2> space;
    Node(int depth, vector<int> p, array<int, 2> space): depth(depth), p(p), space(space) {}
};

int main() {
    int n;
    string s, t;
    cin >> n >> s >> t;

    vector<int> start, target;
    start.reserve(n + 2);
    target.reserve(n + 2);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') start.push_back(1);
        if (s[i] == 'B') start.push_back(0);
        if (t[i] == 'W') target.push_back(1);
        if (t[i] == 'B') target.push_back(0);
    }
    for (int i = 0; i < 2; i++) {
        start.push_back(-1);
        target.push_back(-1);
    }

    // 可否の判定
    int wcnt = 0, bcnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') wcnt--;
        if (t[i] == 'W') wcnt++;
        if (s[i] == 'B') bcnt--;
        if (t[i] == 'B') bcnt++;
    }
    if (wcnt != 0 || bcnt != 0) {
        cout << -1 << endl;
        return 0;
    }

    // 操作回数の探索
    queue<Node> que;
    que.emplace(0, start, array<int, 2>{n, n + 1});
    map<vector<int>, bool> seen;
    seen[start] = true;

    while (!que.empty()) {
        Node v = que.front(); que.pop();

        // 目的の形になっているか判定
        if (v.p == target) {
            cout << v.depth << endl;
            return 0;
        }

        // 掘る
        for (int i = 1; i < n + 2; i++) {
            // 2個連続で石がある場合のみ操作可能
            if (v.p[i - 1] != -1 && v.p[i] != -1) {
                vector<int> p = v.p;
                swap(p[i - 1], p[v.space[0]]);
                swap(p[i], p[v.space[1]]);

                if (!seen[p]) {
                    seen[p] = true;
                    que.emplace(v.depth + 1, p, array<int, 2>{i - 1, i});
                }
            }
        }
    }
    cout << -1 << endl;
}
