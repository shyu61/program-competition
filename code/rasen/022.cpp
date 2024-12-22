#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000;
const int VMAX = 10000;
int n, minimum = VMAX, cost = 0, A[MAX], D[MAX], T[VMAX+1];
bool B[MAX];

void solve() {
    sort(D, D + n);
    for (int i = 0; i < n; i++) {
        T[D[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        if (B[i]) continue;
        int dest = i;
        int sum = 0, m = VMAX, size = 0;
        while (true) {
            B[dest] = true;
            sum += A[dest]; m = min(m, A[dest]); size++;
            dest = T[A[dest]];
            if (B[dest]) break;
        }

        cost += min(sum + (size - 2) * m, sum + m + (size + 1) * minimum);
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        D[i] = A[i];
        B[i] = false;
        minimum = min(minimum, A[i]);
    }
    solve();
    cout << cost << endl;
}