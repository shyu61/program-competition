#include <iostream>
#include <vector>

struct Card {
    char suit, value;
};

void bubble(Card C[], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > i; j--) {
            if (C[j].value < C[j - 1].value) {
                std::swap(C[j], C[j - 1]);
            }
        }
    }
}

void selection(Card C[], int N) {
    for (int i = 0; i < N; i++) {
        int minj = i;
        for (int j = i + 1; j < N; j++) {
            if (C[j].value < C[minj].value) {
                minj = j;
            }
        }
        std::swap(C[minj], C[i]);
    }
}

// bool isStable(Card bubble[], Card selection[], int N) {
//     //
//     bubbleは常に安定なので、bubbleと比較することでselectionが安定か判定する
//     for (int i = 0; i < N; i++) {
//         if (bubble[i].suit != selection[i].suit) {
//             return false;
//         }
//     }
//     return true;
// }

bool isStable(Card in[], Card out[], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (in[i].value == in[j].value) {
                bool is_found = false;
                for (int a = 0; a < N; a++) {
                    if (out[a].suit == in[i].suit && out[a].value == in[i].value) {
                        is_found = true;
                    }
                    if (out[a].suit == in[j].suit && out[a].value == in[j].value && !is_found) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int N;
    Card C1[36], C2[36];

    char C[36];

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> C1[i].suit >> C1[i].value;
    }

    for (int i = 0; i < N; i++) C2[i] = C1[i];

    bubble(C1, N);
    selection(C2, N);

    for (int i = 0; i < N; i++) {
        std::cout << C1[i].suit << C1[i].value << " ";
    }
    std::cout << std::endl << "Stable" << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << C2[i].suit << C2[i].value << " ";
    }
    if (isStable(C1, C2, N)) {
        std::cout << std::endl << "Stable" << std::endl;
    } else {
        std::cout << std::endl << "Not Stable" << std::endl;
    }

    return 0;
}