#include <iostream>
using namespace std;
const int MAX = 2000000;

int n, A[MAX];

void countingSort(int B[], int k) {
    int C[k + 1];
    for (int i = 0; i <= k; i++) {
        C[i] = 0;
    }

    // C[i]にiの出現回数を記録
    for (int i = 0; i < n; i++) {
        C[A[i]]++;
    }

    // C[i]にi以下の数の出現数を記録する
    for (int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
}

int main() {
    int k = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (A[i] > k) {
            k = A[i];
        }
    }

    int B[n];
    countingSort(B, k);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            cout << B[i];
        } else {
            cout << " " << B[i];
        }
    }
    cout << endl;
}