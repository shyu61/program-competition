// E - Yet Another Sigma Problem
// https://atcoder.jp/contests/abc353/tasks/abc353_e
// trie木を作りながらcntする方法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 文字列に関する操作で、LCPやPrefix、辞書順などが絡む問題はTrie木を検討する
// Trie木は、Prefixについての共通祖先やPrefixの個数、辞書順探索に優れている

struct Trie {
    struct Node {
        unordered_map<char, int> to;  // prefix文字と総数を保持
        int cnt;
        Node(): cnt(0) {};
    };
    vector<Node> d;
    ll ans = 0;
    Trie(): d(1) {};
    void add(const string& s) {
        int v = 0;
        for (char c : s) {
            if (!d[v].to.count(c)) {
                // 配列の末尾に新しくNodeを追加する
                d[v].to[c] = d.size();
                d.push_back(Node());
            }
            v = d[v].to[c];
            d[v].cnt++;
        }
    }

    void dfs(int v) {
        ll res = d[v].cnt;
        // rootはカウントしない
        if (v) ans += res * (res - 1) / 2;
        for (auto child : d[v].to) {
            dfs(child.second);
        }
    }

    ll solve() {
        ans = 0;
        // Rootからdfsしながらcntを加算していく
        dfs(0);
        return ans;
    }
};

int main() {
    int n; cin >> n;
    Trie tr = Trie();
    
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        tr.add(s);
    }

    ll ans = tr.solve();
    cout << ans << endl;
}
