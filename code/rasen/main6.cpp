#include <iostream>
#include <cstdio>
#include <cstring>

const int MAX_KEYS = 100000;
const int MAX_COMMANDS = 2000000;

int stack[MAX_KEYS];
int top = -1;

void _insert(int x) { stack[++top] = x; }

void _delete(int x) {
    if (stack[top] == x) {
        stack[top--] = -1;
        return;
    }
    for (int i = top; i >= 0; i--) {
        if (stack[i] == x) {
            stack[i] = -1;
            break;
        }
    }
}

void _delete_first() { stack[top--] = -1; }

void _delete_last() {
    for (int i = 0; i <= top; i++) {
        if (stack[i] != -1) {
            stack[i] = -1;
            break;
        }
    }
}

int main() {
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        char fn[20];
        int key = -1;
        scanf("%s%d", fn, &key);

        if (fn[0] == 'i') {
            _insert(key);
        } else if (std::strlen(fn) == 6) {
            _delete(key);
        } else if (fn[6] == 'F') {
            _delete_first();
        } else if (fn[6] == 'L') {
            _delete_last();
        }
    }

    bool is_first = true;
    for (int i = top; i >= 0; i--) {
        int key = stack[i];
        if (key != -1) {
            if (is_first) {
                std::cout << key;
            } else {
                std::cout << " " << key;
            }
            is_first = false;
        }
    }
    std::cout << std::endl;

    return 0;
}