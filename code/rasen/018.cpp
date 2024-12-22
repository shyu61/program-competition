#include <cmath>
#include <iostream>
#include <limits>
using namespace std;
const int MAX = 100000;

struct Card {
    char suit;
    int number;
};

void merge(Card A[], int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    Card L[n1 + 1], R[n2 + 1];
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[mid + i];
    }
    L[n1].number = R[n2].number = numeric_limits<int>::max();
    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        if (L[i].number <= R[j].number) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void mergeSort(Card A[], int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid, right);
        merge(A, left, mid, right);
    }
}

int partition(Card A[], int p, int r) {
    int x = A[r].number;
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j].number <= x) {
            swap(A[++i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quickSort(Card A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int main() {
    int n;
    Card A[MAX], B[MAX];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i].suit >> A[i].number;
        B[i] = A[i];
    }
    quickSort(A, 0, n - 1);
    mergeSort(B, 0, n);

    int is_stable = 1;
    for (int i = 0; i < n; i++) {
        if (A[i].suit != B[i].suit) {
            is_stable = 0;
            break;
        }
    }

    if (is_stable) {
        cout << "Stable" << endl;
    } else {
        cout << "Not stable" << endl;
    }

    for (int i = 0; i < n; i++) {
        cout << A[i].suit << " " << A[i].number << endl;
    }
}