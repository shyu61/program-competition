#include <iostream>
#include <sstream>
#include <vector>

int top, stack[1000];

void push(int x) {
    top++;
    stack[top] = x;
}

int pop() {
    top--;
    return stack[top + 1];
}

int main() {
    int a, b;
    std::vector<std::string> v;
    std::string str, s;

    std::getline(std::cin, s);
    std::stringstream ss;
    ss << s;

    while (std::getline(ss, s, ' ')) {
        if (s[0] == '+') {
            a = pop();
            b = pop();
            push(a + b);
        } else if (s[0] == '-') {
            a = pop();
            b = pop();
            push(b - a);
        } else if (s[0] == '*') {
            a = pop();
            b = pop();
            push(a * b);
        } else {
            push(stoi(s));
        }
    }

    std::cout << pop() << std::endl;

    return 0;
}