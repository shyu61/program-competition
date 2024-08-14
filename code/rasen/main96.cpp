// 8クイーン問題
#include <iostream>
#include <vector>
using namespace std;
const int N = 8;

vector<bool> init_rows(N, false);
vector<vector<bool>> board(N, vector<bool>(N, false));

bool isSafe(int row, int col) {
    for (int i = 0; i < N; i++) {
        // 縦方向
        if (board[i][col]) return false;
        // 右下対角線
        if (row + i < N && col + i < N && board[row + i][col + i]) return false;
        // 左下対角線
        if (row + i < N && col - i >= 0 && board[row + i][col - i]) return false;
        // 右上対角線
        if (row - i >= 0 && col + i < N && board[row - i][col + i]) return false;
        // 左上対角線
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i]) return false;
    }
    return true;
}


bool solve(int row) {
    if (row >= N) return true;
    if (init_rows[row]) {
        if (solve(row + 1)) return true;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = true;
            if (solve(row + 1)) return true;
            // バックトラック
            board[row][col] = false;
        }
    }
    return false;
}

int main() {
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        board[r][c] = true;
        init_rows[r] = true;
    }

    if (solve(0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] ? "Q" : ".");
            }
            cout << endl;
        }
    }
}
