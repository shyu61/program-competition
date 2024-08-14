#include <iostream>
#include <string>
using namespace std;

const int MAX = 2000000;

int n, A[MAX + 1];

int parent(int i) { return i / 2; }
int left(int i) { return i * 2; }
int right(int i) { return i * 2 + 1; }

void upHeapify(int i) {
    int p = parent(i);
    if (p >= 1 && A[i] > A[p]) {
        swap(A[i], A[p]);
        upHeapify(p);
    }
}

void insert(int key) {
    A[++n] = key;
    if (n > 1) upHeapify(n);
}

void downHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= n && A[l] > A[largest]) largest = l;
    if (r <= n && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        downHeapify(largest);
    }
}

int extractMax() {
    int root = A[1];
    A[1] = A[n--];
    downHeapify(1);
    return root;
}

int main() {
    string com;
    while (true) {
        int key;
        cin >> com;
        if (com == "insert") {
            cin >> key;
            insert(key);
        }
        else if (com == "extract") cout << extractMax() << endl;
        else break;
    }
}