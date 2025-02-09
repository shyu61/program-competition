#include <vector>
using namespace std;

struct UnionFind {
    vector<int> parents;
    UnionFind(int n) : parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) {
        return -parents[leader(x)];
    }
};

// struct UnionFind {
//     // 親のインデックスを保持する
//     // rootは負の値を取り、その絶対値がその木における要素数を表す
//     vector<int> parents;
//     UnionFind(int n) : parents(n, -1) {}

//     void init(int n) {
//         parents.assign(n, -1);
//     }

//     int leader(int x) {
//         // 経路圧縮
//         return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
//     }

//     bool same(int x, int y) {
//         return leader(x) == leader(y);
//     }

//     bool merge(int x, int y) {
//         x = leader(x), y = leader(y);
//         if (x == y) return false;
//         // 常に小さい木を大きい木に結合する
//         if (parents[x] > parents[y]) swap(x, y);
//         parents[x] += parents[y];
//         parents[y] = x;
//         return true;
//     }

//     int size(int x) {
//         return -parents[leader(x)];
//     }
// };
