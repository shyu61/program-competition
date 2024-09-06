// ポインターを使った解法
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 500000;

struct Point { int id, x, y; };
struct Node {
    int point_id, x, y;
    Node *parent, *left, *right;
};

vector<Node> nodes(MAX_N);
Node *NIL;
vector<Point> points;
int node_count = 0;

bool xLess(const Point& a, const Point& b) { return a.x < b.x; }
bool yLess(const Point& a, const Point& b) { return a.y < b.y; }

Node* makeKDTree(vector<Point>::iterator left, vector<Point>::iterator right, int depth) {
    int dist = right - left;
    if (dist <= 0) return NIL;

    int mid = dist / 2;
    if (depth % 2 == 0) {
        sort(left, right, xLess);
    } else {
        sort(left, right, yLess);
    }

    Point mid_point = *(left + mid);
    // newで動的にメモリを確保するとタイムオーバーになる
    Node* node = &nodes[node_count++];
    node->point_id = mid_point.id;
    node->x = mid_point.x;
    node->y = mid_point.y;

    node->left = makeKDTree(left, left + mid, depth + 1);
    node->right = makeKDTree(left + mid + 1, right, depth + 1);

    return node;
}

vector<int> ans;
void searchArea(Node* node, int x0, int y0, int x1, int y1, int depth) {
    if (node == NIL) return;
    int x = node->x;
    int y = node->y;

    if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
        ans.push_back(node->point_id);
    }

    if (depth % 2 == 0) {
        if (x0 <= x) {
            searchArea(node->left, x0, y0, x1, y1, depth + 1);
        }
        if (x <= x1) {
            searchArea(node->right, x0, y0, x1, y1, depth + 1);
        }
    } else {
        if (y0 <= y) {
            searchArea(node->left, x0, y0, x1, y1, depth + 1);
        }
        if (y <= y1) {
            searchArea(node->right, x0, y0, x1, y1, depth + 1);
        }
    }
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        Point point = {i, x, y};
        points.push_back(point);
    }
    Node *root = makeKDTree(points.begin(), points.end(), 0);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int x0, x1, y0, y1;
        cin >> x0 >> x1 >> y0 >> y1;
        searchArea(root, x0, y0, x1, y1, 0);

        sort(ans.begin(), ans.end());
        for (int j = 0; j < ans.size(); j++) {
            cout << ans[j] << endl;
        }
        cout << endl;
        ans.clear();
    }
}