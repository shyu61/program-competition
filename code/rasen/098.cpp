// 8パズル
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;
const int N = 3;
const int N2 = 9;
vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8, 9};

struct Node {
    int space;
    string path;
    vector<int> puzzle;
    Node() {}
    Node(int space, string path, vector<int> puzzle)
        : space(space), path(path), puzzle(puzzle) {}
};

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
const char dir[4] = {'u', 'l', 'd', 'r'};

int solve(Node root) {
    map<vector<int>, bool> seen;
    seen[root.puzzle] = true;

    queue<Node> que;
    que.push(root);

    while (!que.empty()) {
        Node v = que.front();
        que.pop();

        if (v.puzzle == ans) return v.path.size();

        int sx = v.space / N;
        int sy = v.space % N;
        for (int i = 0; i < 4; i++) {
            int tx = sx + dx[i];
            int ty = sy + dy[i];
            if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;

            int space = tx * N + ty;
            Node child(space, v.path, v.puzzle);
            swap(child.puzzle[v.space], child.puzzle[child.space]);

            if (!seen[child.puzzle]) {
                seen[child.puzzle] = true;
                child.path += dir[i];
                que.push(child);
            }
        }
    }
    return -1;
}

int main() {
    Node root(0, "", vector<int>(N2, 0));
    for (int i = 0; i < N2; i++) {
        cin >> root.puzzle[i];
        if (root.puzzle[i] == 0) {
            root.puzzle[i] = N2;
            root.space = i;
        }
    }
    cout << solve(root) << endl;
}
