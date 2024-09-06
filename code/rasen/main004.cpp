#include <iostream>
#include <vector>

int cnt = 0;
std::vector<int> G;

int insertSort(int A[], int n, int g) {
    int cnt = 0;
    for (int i = g; i < n; i++) {
        int v = A[i];
        int j = i - g;
        while (j >= 0 && A[j] > v) {
            A[j+g] = A[j];
            j -= g;
            cnt++;
        }
        A[j+g] = v;
    }
    return cnt;
}

void shellSort(int A[], int n) {
    int h = 1;
    while (h < n) {
        G.push_back(h);
        h = 3*h + 1;
    }
    for (int i = G.size()-1; i >= 0; i--) {
        cnt += insertSort(A, n, G[i]);
    }
}

int main() {
    int n, A[1000000];

    std::cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);

    shellSort(A, n);

    std::cout << G.size() << std::endl;
    for (int i = 0; i < G.size(); i++) {
        printf("%d ", G[i]);
    }
    printf("\n");

    printf("%d\n", cnt);
    for (int i = 0; i < n; i++) printf("%d\n", A[i]);

    return 0;
}