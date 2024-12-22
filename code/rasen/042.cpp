#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100;

int A[MAX][MAX], F[MAX], B[MAX], visited[MAX], n = 0, ts = 1;

void dfs(int id) {
    if (visited[id]) return;
    F[id] = ts++;
    visited[id] = 1;
    for (int i = 0; i < n; i++) {
        if (A[id][i] == 0) continue;
        dfs(i);
    }
    B[id] = ts++;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int id, deg;
        cin >> id >> deg;
        id--;
        for (int j = 0; j < deg; j++) {
            int k;
            cin >> k;
            k--;
            A[id][k] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << F[i] << " " << B[i] << endl;
    }
}