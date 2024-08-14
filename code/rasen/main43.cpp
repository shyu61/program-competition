#include <iostream>
#include <stack>
using namespace std;
const int MAX = 100;

int A[MAX][MAX], F[MAX], B[MAX], visited[MAX], n = 0, ts = 1;

int forward(int v) {
    int dst = -1;
    for (int i = 0; i < n; i++) {
        if (A[v][i] && visited[i] == 0) {
            dst = i;
            break;
        }
    }
    return dst;
}

void dfs(int v) {
    stack<int> S;
    S.push(v);
    visited[v] = 1;
    F[v] = ts++;

    while (!S.empty()) {
        v = S.top();
        int dst = forward(v);
        if (dst != -1) {
            S.push(dst);
            visited[dst] = 1;
            F[dst] = ts++;
        } else {
            S.pop();
            visited[v] = 2;
            B[v] = ts++;
        }
    }
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