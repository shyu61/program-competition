#include <iostream>
#include <queue>
using namespace std;
const int MAX = 100;
const int NIL = -1;

int A[MAX][MAX], D[MAX], visited[MAX], n = 0;

int next(int v) {
    for (int k = 0; k < n; k++) {
        if (A[v][k] && !visited[k]) return k;
    }
    return NIL;
}

void bfs() {
    queue<int> Q;
    int v = 0;
    Q.push(v); D[v] = 0; visited[v] = 1;

    while (!Q.empty()) {
        int prev = Q.front();
        v = next(prev);
        if (v != NIL) {
            Q.push(v);
            D[v] = D[prev] + 1;
            visited[v] = 1;
        } else {
            Q.pop();
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        D[i] = -1;
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
            int k; cin >> k;
            A[id][--k] = 1;
        }
    }

    bfs();

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << D[i] << endl;
    }
}