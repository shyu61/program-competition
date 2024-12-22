// Binary Indexed Tree(A Simple Problem with Integers): p163
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BIT {
    vector<T> bit;
    const T n;
    BIT(T n_) : bit(n_ + 1, 0), n(n_) {};

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    };

    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    };
};

// 遅延セグ木の場合と同様にBITでも区間の更新はコストがかかる。遅延セグ木と同様に、区間に対して一様に加わる変更を別の木で管理することで高速化できる。
// セグ木は区間の代表ノードがあるためそこに+x*要素数することで一括更新ができたが、BITはそれができないので、代わりに地点lに+xすると[l,∞]の区間全てに+xするという取り決めを作る。
// この取り決めは実際計算するときに、bit1.sum(i)*iのように要素数をかけることで解に落とす。
// こうすることで、区間に対して一様な影響と個別の影響を一次関数として表現できる。
// あとは区間ごとに場合わけして遷移を考える事で立式できる。iがi<lからr<iまで順に登っていく過程を立式するイメージ。

// 別視点で見ると、[l,r]に+xするために、bit1.add(l,x)をすると[l,∞]に影響するので、r+1以降の影響を打ち消すためにbit1.add(r+1,-x)する。
// さらにクエリするときに、bit1の影響はbit1.sum(i)*iという形で提供されるので、これは(0,i]の全ての地点に記録された変化量の合計値をi個加えることを表すことになるが、
// 例えばi-1の位置に記録された変化量は*1で十分なところを*iされてしまって過剰である。故にbit0側で調整するために、(l-1)個分+xが過剰なので、bit0.add(l,-x*(l-1)))をする。
// 同様の理由で打ち消し分も過剰になる。故にr個分-xが過剰なので、bit0.add(r+1,xr)をする。
// 別視点では、iの[l,r]における場合分けを使って立式もできる。注意点は影響が累積的なので遷移として扱うこと。r<iのiはi<lからl<=i<=rを経ていると考える。

// 知っておくと良いのは、区間更新は2つのBITを使って一次関数で表現できること。遅延セグ木も代表ノードに+x*要素数しているので一次関数として表現していると捉えて良い。
// 要するに個数の積を使う事で個数回+xするコストを削減しているわけである。だが何を個数分かけるのかという部分がBITの場合は多くのオフセットを考慮する必要があり複雑なわけである。

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    BIT<int> bit0(N), bit1(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        bit0.add(i + 1, a[i]);
    }

    for (int i = 0; i < Q; i++) {
        char c;
        cin >> c;
        if (c == 'C') {
            int l, r, x;
            cin >> l >> r >> x;
            // [l,r]のすべての要素にxを加える
            bit0.add(l, -x * (l - 1));
            bit1.add(l, x);
            bit0.add(r + 1, x * r);
            bit1.add(r + 1, -x);
        } else {
            int l, r;
            cin >> l >> r;
            // [l,r]の和を求める
            ll ans = (bit0.sum(r) - bit0.sum(l - 1)) +
                     (bit1.sum(r) * r - bit1.sum(l - 1) * (l - 1));
            cout << ans << endl;
        }
    }
}
