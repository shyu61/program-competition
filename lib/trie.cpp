#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// trie木
// 文字列のprefix系や辞書順の問題と相性が良い
// そのまま使うというよりは、各ノードに問題にあった情報を持たせて拡張して使うことが多い

struct Trie {
    struct Node {
        // ノードの行き先 map<prefix,ノード番号>
        unordered_map<char, int> to;
        int cnt;  // 各ノードに持たせる情報
        Node(): cnt(0) {};
    };
    vector<Node> d;

    Trie(): d(1) {};  // 初期化時はルートノードのみ追加

    void add(const string& s) {
        int v = 0;
        for (char c : s) {
            if (!d[v].to.count(c)) {  // 行き先ノードがない場合
                d[v].to[c] = d.size();  // 追加するノードの番号は親側に持つ
                d.push_back(Node());
            }
            v = d[v].to[c];  // ポインターを進める
            d[v].cnt++;
        }
    };

    void dfs(int v, ll& total) {
        total += d[v].cnt;  // 各ノードに持たせた情報を集計する
        for (auto ch : d[v].to) {
            dfs(ch.second, total);
        }
    }
};
