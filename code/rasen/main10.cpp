#include <iostream>
using namespace std;

int n, S[100000];

int binarySearch(int key) {
    // 両開区間
    int left = -1;
    int right = n;

    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (key == S[mid]) {
            return 1;
        } else if (key < S[mid]) {
            right = mid;
        } else if (key > S[mid]) {
            left = mid;
        }
    }
    return 0;
}

int main() {
    int q, key, c = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> key;
        if (binarySearch(key)) c++;
    }

    cout << c << endl;

    return 0;
}