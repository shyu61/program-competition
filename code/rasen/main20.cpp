#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 10000;

int n, A[MAX];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    stable_sort(&A[0], &A[n-1]);
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
}