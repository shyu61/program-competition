#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<int> > A(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        int id, deg;
        cin >> id >> deg;
        for (int j = 0; j < deg; j++) {
            int k; cin >> k;
            A[id][k] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << " ";
            cout << A[i][j];
        }
        cout << endl;
    }
}