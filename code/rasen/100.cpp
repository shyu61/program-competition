// 15パズル: IDA*（グローバル変数を使う方法）
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
Node state;
int limit;

int getMD(vector<int> pz) {
    int sum = 0;
    for (int i = 0; i < N2; i++) {
        if (pz[i] == N2) continue;
        sum += MDT[pz[i] - 1][i];
    }
    return sum;
}

int dfs(int depth, int prev) {
    if (state.MD == 0) return depth;
    if (depth + state.MD > limit) return -1;

    int sx = state.space / N;
    int sy = state.space % N;

    Node tmp;
    for (int r = 0; r < 4; r++) {
        // 前回と逆方向の操作は元に戻るだけなので禁止
        if (abs(r - prev) == 2) continue;
        int tx = sx + dx[r];
        int ty = sy + dy[r];
        if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;

        tmp = state;
        int space = tx * N + ty;
        // 今、spaceにある要素がstate.spaceに移動する
        int move = state.pz[space] - 1;
        state.MD += MDT[move][state.space] - MDT[move][space];
        swap(state.pz[state.space], state.pz[space]);
        state.space = space;

        int ans = dfs(depth + 1, r);
        if (ans != -1) return ans;
        state = tmp;
    }
    return -1;
}

int solve(Node root) {
    for (limit = root.MD; limit <= LIMIT; limit++) {
        state = root;
        int ans = dfs(0, 6);
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
