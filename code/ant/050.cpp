// プライオリティキューとヒープ: p71
#include <bits/stdc++.h>
using namespace std;

// heapは完全二分木なので親->子,子->親のノード番号を計算できる
// これを利用してheapではポインターではなく配列で表現されることが多い

const int MAXN = 1e6;
vector<int> heap(MAXN);
int sz = 0;

// 下から上へ
void push(int x) {
    int i = sz++;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= x) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

int top() {
    return heap[0];
}

// 上から下へ
void pop() {
    int x = heap[--sz];
    int i = 0;
    // leafに辿り着くまで -> 子のノード番号を計算できる範囲まで
    while (i * 2 + 1 < sz) {
        int a = i * 2 + 1;
        int b = i * 2 + 2;
        if (heap[a] > heap[b]) a = b;

        if (x <= heap[a]) break;
        heap[i] = heap[a];
        i = a;
    }
    heap[i] = x;
}

int main() {
    push(100);
    push(1);
    push(3);
    push(2);

    cout << top() << endl;
    pop();
    cout << top() << endl;
}
