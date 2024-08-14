#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

double sin60 = sin(60 * M_PI / 180.0);
double cos60 = cos(60 * M_PI / 180.0);

struct Point {
    double x, y;
};

void print(Point p) {
    printf("%.8f %.8f\n", p.x, p.y);
}

void koch(Point p1, Point p2, int n) {
    if (n == 0) return;

    Point s, u, t;
    s.x = (2 * p1.x + p2.x) / 3.0;
    s.y = (2 * p1.y + p2.y) / 3.0;
    t.x = (p1.x + 2 * p2.x) / 3.0;
    t.y = (p1.y + 2 * p2.y) / 3.0;

    u.x = (t.x - s.x) * cos60 - (t.y - s.y) * sin60 + s.x;
    u.y = (t.x - s.x) * sin60 + (t.y - s.y) * cos60 + s.y;

    koch(p1, s, n - 1);
    print(s);
    koch(s, u, n - 1);
    print(u);
    koch(u, t, n - 1);
    print(t);
    koch(t, p2, n - 1);
}

int main() {
    int n;
    cin >> n;
    Point p1, p2;
    p1.x = 0;
    p1.y = 0;
    p2.x = 100;
    p2.y = 0;

    print(p1);
    koch(p1, p2, n);
    print(p2);
}