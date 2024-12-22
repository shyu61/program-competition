// 配列を使った解法
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int NIL = -1;
const int MAX_N = 500000;

struct Point { int id, x, y; };
struct Node { int parent, left, right, point_id, x, y; };  // key: Pにおけるindex

Point P[MAX_N];  // indexに意味はない
Node T[MAX_N];  // indexがnode番号

bool xLess(const Point& a, const Point& b) { return a.x < b.x; }
bool yLess(const Point& a, const Point& b) { return a.y < b.y; }

int np = 0;
int makeKDTree(int left, int right, int depth) {
    if (left >= right) return NIL;
    int mid = (left + right) / 2;

    if (depth % 2 == 0) {
        sort(P + left, P + right, xLess);
    } else {
        sort(P + left, P + right, yLess);
    }
    int t = np++;

    Point mid_point = P[mid];

    T[t].point_id = mid_point.id;
    T[t].x = mid_point.x;
    T[t].y = mid_point.y;
    T[t].left = makeKDTree(left, mid, depth + 1);
    T[t].right = makeKDTree(mid + 1, right, depth + 1);

    return t;
}

vector<int> ans;
void searchArea(int node_id, int x0, int y0, int x1, int y1, int depth) {
    int x = T[node_id].x;
    int y = T[node_id].y;

    if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
        ans.push_back(T[node_id].point_id);  // 点番号を格納
    }

    if (depth % 2 == 0) {
        if (T[node_id].left != NIL && x0 <= x) {
            searchArea(T[node_id].left, x0, y0, x1, y1, depth + 1);
        }
        if (T[node_id].right != NIL && x <= x1) {
            searchArea(T[node_id].right, x0, y0, x1, y1, depth + 1);
        }
    } else {
        if (T[node_id].left != NIL && y0 <= y) {
            searchArea(T[node_id].left, x0, y0, x1, y1, depth + 1);
        }
        if (T[node_id].right != NIL && y <= y1) {
            searchArea(T[node_id].right, x0, y0, x1, y1, depth + 1);
        }
    }
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        P[i] = Point{i, x, y};
        T[i].left = T[i].right = T[i].parent = NIL;
    }
    makeKDTree(0, n, 0);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int x0, x1, y0, y1;
        cin >> x0 >> x1 >> y0 >> y1;
        searchArea(0, x0, y0, x1, y1, 0);

        sort(ans.begin(), ans.end());
        for (int j = 0; j < ans.size(); j++) {
            cout << ans[j] << endl;
        }
        cout << endl;
        ans.clear();
    }
}