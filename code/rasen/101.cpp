// 15パズル: A*
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int space, depth, MD, cost;  // マンハッタン距離
    vector<int> pz;
    Node() {}
    Node(int space, int depth, int MD, vector<int> pz)
        : space(space), depth(depth), MD(MD), pz(pz) {}

    // minヒープとして使う
    bool operator<(const Node& n) const { return cost > n.cost; };
};

const int N = 4;
const int N2 = 16;
int MDT[N2][N2];
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};

int getMD(vector<int> pz) {
    int sum = 0;
    for (int i = 0; i < N2; i++) {
        if (pz[i] == N2) continue;
        sum += MDT[pz[i] - 1][i];
    }
    return sum;
}

int solve(Node root) {
    priority_queue<Node> pq;
    pq.push(root);

    map<vector<int>, bool> seen;
    seen[root.pz] = true;

    while (!pq.empty()) {
        Node v = pq.top();
        pq.pop();

        if (v.MD == 0) return v.depth;

        int sx = v.space / N;
        int sy = v.space % N;
        for (int r = 0; r < 4; r++) {
            int tx = sx + dx[r];
            int ty = sy + dy[r];
            if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;

            int space = tx * N + ty;
            Node child(space, v.depth + 1, v.MD, v.pz);
            swap(child.pz[v.space], child.pz[space]);

            if (!seen[child.pz]) {
                seen[child.pz] = true;
                int move = v.pz[space] - 1;
                child.MD += MDT[move][v.space] - MDT[move][space];
                child.cost = child.depth + child.MD;
                pq.push(child);
            }
        }
    }
    return -1;
}

int main() {
    for (int i = 0; i < N2; i++) {
        for (int j = 0; j < N2; j++) {
            // 正しい位置をiとする時、位置jからのマンハッタン距離
            MDT[i][j] = abs(i / N - j / N) + abs(i % N - j % N);
        }
    }

    Node root(0, 0, 0, vector<int>(N2, 0));
    for (int i = 0; i < N2; i++) {
        cin >> root.pz[i];
        if (root.pz[i] == 0) {
            root.pz[i] = N2;
            root.space = i;
        }
    }
    root.MD = getMD(root.pz);
    root.cost = root.depth + root.MD;
    cout << solve(root) << endl;
}
