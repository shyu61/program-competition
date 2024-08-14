#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_V = 100;

int v;
int A[MAX_V][MAX_V];

void floyd() {
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (A[i][k] != INF && A[k][j] != INF) {
                    A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
                }
            }
        }
    }
}

int main() {
    int e; cin >> v >> e;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i == j) A[i][j] = 0;
            else A[i][j] = INF;
        }
    }
    for (int i = 0; i < e; i++) {
        int e0, e1, w; cin >> e0 >> e1 >> w;
        A[e0][e1] = w;
    }

    floyd();

    bool has_neg_cycle = false;
    for (int i = 0; i < v; i++) {
        if (A[i][i] < 0) {
            has_neg_cycle = true;
            break;
        }
    }

    if (has_neg_cycle) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (j == 0) {
                    if (A[i][j] == INF) cout << "INF";
                    else cout << A[i][j];
                } else {
                    if (A[i][j] == INF) cout << " " << "INF";
                    else cout << " " << A[i][j];
                }
            }
            cout << endl;
        }
    }
}