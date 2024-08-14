#include <iostream>
using namespace std;
const int MAX = 100000;

int n, A[MAX];

int partition(int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int idx = partition(0, n-1);

    for (int i = 0; i < n; i++) {
        if (i == 0) cout << A[i];
        else if (i == idx) {
            cout << " [" << A[idx] << "]";
        } else {
            cout << " " << A[i];
        }
    }
    cout << endl;
}