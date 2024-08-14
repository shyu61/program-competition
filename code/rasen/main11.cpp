#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int M = 1000003;
const int L = 15;
char D[M][L];

int convAtoi(char x) {
    if (x == 'A')
        return 1;
    else if (x == 'T')
        return 2;
    else if (x == 'G')
        return 3;
    else
        return 4;
}

long long convStrtoi(char x[]) {
    long long sum = 0;
    int pow = 1;
    for (int j = 0; j < strlen(x); j++) {
        sum += pow * convAtoi(x[j]);
        pow *= 5;
    }
    return sum;
}

int h1(int x) { return x % M; }

int h2(int x) { return 1 + x % (M - 1); }

int getHash(long long x_i, int i) { return (h1(x_i) + i * h2(x_i)) % M; }

void insert(char key[]) {
    long long x_i = convStrtoi(key);
    for (int i = 0; i < M; i++) {
        int hash = getHash(x_i, i);
        if (strlen(D[hash]) == 0) {
            strcpy(D[hash], key);
            break;
        }
    }
}

int find(char key[]) {
    long long x_i = convStrtoi(key);
    for (int i = 0; i < M; i++) {
        int hash = getHash(x_i, i);
        if (strlen(D[hash]) == 0) {
            return 0;
        } else if (strcmp(D[hash], key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    char command[10], key[L];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> command >> key;

        if (command[0] == 'i') {
            insert(key);
        } else if (command[0] == 'f') {
            if (find(key)) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }
    }
    return 0;
}