#include <bits/stdc++.h>
using namespace std;

// ジャンル
// - 数論, 桁, 桁和, 剰余, 倍数判定, 構築問題

// 方針
// 桁問題だが、数え上げではなく条件に合致するものを「構築」する問題なので桁dpではなく法則に則り生成することを考える。
// 構築問題はまず、解が(1)一意なのか(2)無数にあるのかを見極める。
// (1)なら正確に求解するために厳密に法則を見抜く必要がある。(2)なら考えやすいものについて調べれば良い。
// 今回はsampleにもあるように(2)なので、桁和と倍数が直接結びつく3,9の倍数を起点に考える。
// (3)桁和が2の偶数と、(4)桁和が8の8の倍数(下3桁が8の倍数)のどちらかが作れれば良いことになる。(これで全てをカバーできない場合は3,9の倍数以外を考える必要が出てくる)
// N<=a,a+1<=2Nという条件下で先の数を作れるかを調べていく。
// (3)2...0を作れるのは、1...となっている数のみ, 11...0を作れるのは10...もしくは2Nで繰り上がる場合なので、s[0]>=6。
// (3)でカバーできなかったものを(4)でカバーすればよく、それはs[0]が2,3,4,5のケースなので、適当に上の桁を2つ使って最上位桁dが消える形で和が8になる数を作ればよい。d-1,7-dとする。

// ポイント
// - 倍数判定は知識として知っておく: https://manabitimes.jp/math/951
//   - 2の倍数: 下一桁が偶数
//   - 3の倍数: 桁和が3の倍数
//   - 4の倍数: 下二桁が4の倍数
//   - 5の倍数: 下一桁が5の倍数
//   - 6の倍数: 2の倍数かつ3の倍数
//   - 7の倍数: x
//   - 8の倍数: 下三桁が8の倍数
//   - 9の倍数: 各桁の和が9の倍数
//   - 10の倍数: 下一桁が0
//   - 11の倍数: 各桁を交互に足し引きした値が11の倍数
//   - 12の倍数: 3の倍数かつ4の倍数

bool is_div(int n) {
    string s = to_string(n);
    int sum = 0;
    for (char c : s) sum += c - '0';
    return n % sum == 0;
}

int main() {
    string s; cin >> s;

    if (s.size() >= 5){
        if(s[0] >= '6'){
            cout << 11 << string(s.size() - 1, '0') << endl;
        } else if (s[0] == '1' && s[1] == '0') {
            cout << 11 << string(s.size() - 2, '0') << endl;
        } else if (s[0] == '1') {
            cout << 2 << string(s.size() - 1, '0') << endl;
        } else {
            int d = s[0] - '0';
            cout << d + 1 << 7 - d << string(s.size() - 2, '0') << endl;
        }
    } else {
        int n = stoi(s);
        for (int i = n; i + 1 <= n * 2; i++) {
            if (is_div(i) && is_div(i + 1)) {
                cout << i << endl;
                return 0;
            }
        }
        cout << -1 << endl;
    }
}
