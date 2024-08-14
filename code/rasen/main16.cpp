#include <cmath>
#include <iostream>
#include <limits>
using namespace std;

const int MAX = 500000;
int cnt = 0;


void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[mid + i];
    }
    L[n1] = R[n2] = numeric_limits<int>::max();;

    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        cnt++;
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

void mergeSort(int A[], int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid, right);
        merge(A, left, mid, right);
    }
}

int main() {
    int n, S[MAX];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    mergeSort(S, 0, n);

    for (int i = 0; i < n; i++) {
        if (i == 0) cout << S[i];
        else cout << " " << S[i];
    }
    cout << endl << cnt << endl;
}