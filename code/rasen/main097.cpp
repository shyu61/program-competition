// 8パズル
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const int N = 9;
vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8, 9};

struct Node {
    int space, depth;
    vector<int> puzzle;
    Node() {}
    Node(int space, int depth, vector<int> puzzle)
        : space(space), depth(depth), puzzle(puzzle) {}
};

bool isAns(vector<int>& p) { return p == ans; }

vector<Node> getChildren(Node parent) {
    vector<Node> children;
    // 右側
    if ((parent.space + 1) % 3 != 0) {
        Node child(parent.space + 1, parent.depth + 1, parent.puzzle);
        swap(child.puzzle[parent.space], child.puzzle[child.space]);
        children.push_back(child);
    }

    // 左側
    if (parent.space - 1 >= 0 && (parent.space - 1) % 3 != 2) {
        Node child(parent.space - 1, parent.depth + 1, parent.puzzle);
        swap(child.puzzle[parent.space], child.puzzle[child.space]);
        children.push_back(child);
    }

    // 下側
    if ((parent.space + 3) < N) {
        Node child(parent.space + 3, parent.depth + 1, parent.puzzle);
        swap(child.puzzle[parent.space], child.puzzle[child.space]);
        children.push_back(child);
    }

    // 上側
    if ((parent.space - 3) >= 0) {
        Node child(parent.space - 3, parent.depth + 1, parent.puzzle);
        swap(child.puzzle[parent.space], child.puzzle[child.space]);
        children.push_back(child);
    }

    return children;
}

int solve(Node root) {
    if (isAns(root.puzzle)) return 0;
    map<vector<int>, bool> seen;
    seen[root.puzzle] = true;

    queue<Node> que;
    que.push(root);

    while (!que.empty()) {
        Node v = que.front();
        que.pop();
        for (auto& child : getChildren(v)) {
            if (seen.find(child.puzzle) != seen.end()) continue;
            if (isAns(child.puzzle)) return child.depth;
            seen[child.puzzle] = true;
            que.push(child);
        }
    }
    return -1;
}

int main() {
    Node root;
    root.depth = 0;
    root.puzzle = vector<int>(N, 0);
    for (int i = 0; i < N; i++) {
        int c;
        cin >> c;
        if (c == 0) {
            c = N;
            root.space = i;
        }
        root.puzzle[i] = c;
    }
    cout << solve(root) << endl;
}
