// ギリギリを考えよ: p229
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double g = 9.8;
const double EPS = 1e-6;

// 連続値を離散値に変換するのが肝の問題
// 題意を満たす条件が複数ありそうなので、一つずつ整理して考えていく
// 1. 豚の上までたどり着ける
// 2. かつ、豚の真上まで障害物に衝突しない
// 3. かつ、豚までの間に障害物がない
// そしてこれらの条件をチェックする打ち出し角が連続値なので、なんとか離散値に持ち込めないか考える
// 幾何の問題では境界を考えるがセオリー。条件を満たす角度の区間の候補が複数あると考えるとき、各候補が本当に条件を満たすかを判定するには境界を調べれば十分であることがわかる
// 障害物の上端がその区間の下限になるはずで、その上端で題意を満たすならその区間が存在し、題意を満たさないならその区間は存在しないつまり、次の下限値までは題意を満たし得ないと言える。
// 故に各障害物の上端(上左右端)を全て調べればよくO(N)であることがわかる

// 残るは2の衝突判定で、線分同士の衝突判定をもとに考える。ccwを使った判定は、比較先が比較元を「跨ぐ」かどうかを判定に使っていた。放物線と矩形の場合もこのセオリーに則れば判定ができる。
// 一方の判定だけでは不十分そうなのは線分同士の判定からなんとなく予想つく。しかし放物線と矩形は、線分同士と違って異種であり対称性がない。故に別の判定が必要そうと発想を飛ばせれば、
// 幾何のセオリー通りエッジケースを考える、つまり放物線のエッジケースといえば頂点(定義域,閾値の端)だと思いつくことができ、頂点が矩形の中に含まれるかどうかは頂点でのx,y座標で判定ができることがわかる

// 難しい問題を解くためのセオリーは、「既存の知識に基づいてアプローチを試み、そこから反例や不足を見つけ、最適な条件を補う」というプロセスを踏むこと。

int N, V, X, Y;
vector<int> L, B, R, T;

// 速度vyで打ち出した時のt秒後の位置
double calc(double vy, double t) {
    return vy * t - g * t * t / 2;
}

// aのlbとubに対する相対的な位置
int cmp(double lb, double ub, double a) {
    return a < lb + EPS ? -1 : a > ub - EPS ? 1 : 0;
}

// 点(qx,qy)を通るように打ち出した時に豚に卵をぶつけられるか判定
bool check(double qx, double qy) {
    double a = g * g / 4, b = g * qy - V * V, c = qx * qx + qy * qy;
    double D = b * b - 4 * a * c;
    if (D < 0 && D > -EPS) D = 0;
    if (D < 0) return false;
    for (int d = -1; d <= 1; d += 2) {
        double t2 = (-b + d * sqrt(D)) / (2 * a);
        if (t2 <= 0) continue;;
        double t = sqrt(t2);
        double vx = qx / t, vy = (qy + g * t * t / 2) / t;

        // 豚より上を通過できるか判定
        double yt = calc(vy, X / vx);
        if (yt < Y - EPS) continue;

        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (L[i] >= X) continue;
            // 豚の真上まで来た時に、間に障害物がないか判定
            if (R[i] == X && Y <= T[i] && B[i] <= yt) ok = false;  // 座標圧縮していることに注意
            // 途中で障害物にぶつからないか判定
            int yL = cmp(B[i], T[i], calc(vy, L[i] / vx));
            int yR = cmp(B[i], T[i], calc(vy, R[i] / vx));
            int xH = cmp(L[i], R[i], vx * (vy / g));
            int yH = cmp(B[i], T[i], calc(vy, vy / g));
            if (xH == 0 && yH >= 0 && yL < 0) ok = false;
            if (yL * yR <= 0) ok = false;
        }
        if (ok) return true;
    }
    return false;
}

int main() {
    cin >> N >> V >> X >> Y;
    L = B = R = T = vector<int>(N);
    for (int i = 0; i < N; i++) cin >> L[i] >> B[i] >> R[i] >> T[i];

    // 座標圧縮
    for (int i = 0; i < N; i++) R[i] = min(R[i], X);

    bool ok = check(X, Y);  // 直接ぶつける場合
    for (int i = 0; i < N; i++) {
        ok |= check(L[i], T[i]);  // 左上
        ok |= check(R[i], T[i]);  // 右上
    }
    cout << (ok ? "Yes" : "No") << endl;
}
