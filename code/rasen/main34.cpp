#include <iostream>
using namespace std;

int n;

int valid(int i) { return i >= 1 && i <= n; }

int main() {
    cin >> n;
    int A[n];
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for (int i = 1; i <= n; i++) {
        int parent = i / 2;
        int left = i * 2;
        int right = i * 2 + 1;

        cout << "node " << i << ": " << "key = " << A[i] << ", ";
        if (valid(parent)) cout << "parent key = " << A[parent] << ", ";
        if (valid(left)) cout << "left key = " << A[left] << ", ";
        if (valid(right)) cout << "right key = " << A[right] << ", ";
        cout << endl;
    }
}