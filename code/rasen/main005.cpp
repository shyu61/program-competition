#include <iostream>
#include <string>

struct P {
    std::string name;
    int q;
};

const int LEN = 100000;
int head, tail;
P queue[LEN];

void enqueue(P x) {
    tail = (tail + 1) % LEN;
    queue[tail] = x;
}

P dequeue() {
    P x = queue[head];
    head = (head + 1) % LEN;
    return x;
}

int main() {
    int n, q, time = 0;

    std::cin >> n >> q;

    for (int i = 0; i < n; i++) {
        std::cin >> queue[i].name >> queue[i].q;
    }
    tail = n - 1;

    while (head != tail) {
        P proc = dequeue();
        int left = proc.q - q;
        if (left > 0) {
            time += q;
            proc.q = left;
            enqueue(proc);
        } else {
            time += left + q;
            std::cout << proc.name << " " << time << std::endl;
        }
    }
    return 0;
}