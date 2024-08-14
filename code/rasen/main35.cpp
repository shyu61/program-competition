#include <iostream>
using namespace std;
const int MAX = 500001;

int n, A[MAX];

int parent(int i) { return i / 2; }
int left(int i) { return i * 2; }
int right(int i) { return i * 2 + 1; }

void maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= n && A[l] > A[largest]) largest = l;
    if (r <= n && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(largest);
    }
}

void buildMaxHeap() {
    for (int i = n / 2; i > 0; i--) {
        maxHeapify(i);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    buildMaxHeap();
    for (int i = 1; i <= n; i++) {
        cout << " " << A[i];
    }
    cout << endl;
}