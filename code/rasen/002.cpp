#include <iostream>

int selectionSort(int A[], int N) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int minj = i;
        for (int j = i+1; j < N; j++) {
            if (A[j] < A[minj]) {
                minj = j;
            }
        }
        if (i != minj) {
            cnt++;
            std::swap(A[i], A[minj]);
        }
    }
    return cnt;
}

int main() {
    int N, A[100];

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    int cnt = selectionSort(A, N);

    for (int i = 0; i < N; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl << cnt << std::endl;

    return 0;
}
