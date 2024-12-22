#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Rec {
    int height, pos;
    Rec (int height, int pos): height(height), pos(pos) {}
};

int H, W;
vector<vector<int>> tiles, hg;

int solve(vector<int> hists){
    stack<Rec> s;
    int maxv = 0;
    for (int i = 0; i <= W; i++){
        Rec rec(hists[i], i);
        if (s.empty()) {
            s.push(rec);
        } else {
            if (s.top().height < rec.height) {
                s.push(rec);
            } else if (s.top().height > rec.height) {
                int target = i;
                while (!s.empty()) {
                    Rec top = s.top();
                    if (top.height < rec.height) {
                        break;
                    }
                    maxv = max(maxv, top.height * (i - top.pos));
                    target = top.pos;
                    s.pop();
                }
                rec.pos = target;
                s.push(rec);
            }
        }
    }
    return maxv;
}


int main() {
    cin >> H >> W;
    tiles = vector<vector<int>>(H, vector<int>(W));
    hg = vector<vector<int>>(H, vector<int>(W + 1));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> tiles[i][j];

            // histgramを計算
            if (tiles[i][j]) {
                hg[i][j] = 0;
            } else {
                hg[i][j] = (i > 0) ? hg[i - 1][j] + 1 : 1;
            }
        }
        // 番兵
        hg[i][W] = 0;
    }

    int maxv = 0;
    for (int i = 0; i < H; i++) {
        maxv = max(maxv, solve(hg[i]));
    }
    cout << maxv << endl;
}