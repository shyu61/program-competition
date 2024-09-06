// 15パズル: IDA*
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int space, depth, MD;  // マンハッタン距離
    vector<int> pz;
    Node() {}
    Node(int space, int depth, int MD, vector<int> pz)
        : space(space), depth(depth), MD(MD), pz(pz) {}
};

const int N = 4;
const int N2 = 16;
const int LIMIT = 45;
int MDT[N2][N2];
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
int limit;

int getMD(vector<int> pz) {
    int sum = 0;
    for (int i = 0; i < N2; i++) {
        if (pz[i] == N2) continue;
        sum += MDT[pz[i] - 1][i];
    }
    return sum;
}

int dfs(Node v, int prev) {
    if (v.MD == 0) return v.depth;
    if (v.depth + v.MD > limit) return -1;

    int sx = v.space / N;
    int sy = v.space % N;
    for (int r = 0; r < 4; r++) {
        // 前回と逆方向の操作は元に戻るだけなので禁止
        if (abs(r - prev) == 2) continue;
        int tx = sx + dx[r];
        int ty = sy + dy[r];
        if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;

        int space = tx * N + ty;
        Node child(space, v.depth + 1, v.MD, v.pz);
        swap(child.pz[v.space], child.pz[child.space]);
        // 今、spaceにある要素がv.spaceに移動する
        int move = v.pz[space] - 1;
        child.MD += MDT[move][v.space] - MDT[move][space];

        int ans = dfs(child, r);
        if (ans != -1) return ans;
    }
    return -1;
}

int solve(Node root) {
    for (limit = root.MD; limit <= LIMIT; limit++) {
        int ans = dfs(root, 6);
        if (ans != -1) return ans;
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
    cout << solve(root) << endl;
}
