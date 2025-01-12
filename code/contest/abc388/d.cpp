#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 数列, 逐次問題, 区間数え上げ

// 方針
// 逐次的に値が変化していくので、まずは更新法則を特定する。減る数はN-i-1で固定で、増える数は自身より前の1個以上石を持った成人数
// 故に増える数が特定できればよく、区間数え上げ問題になる。
// 区間の各要素で判定条件が同じじゃないと高速化できないので、予めoffsetを入れておくと、「区間内でi以上の要素数」を数えれば良いことがわかる
// あとは適当なデータ構造を使えば良い。

// ポイント
// - 単調性がある条件の数え上げ: 二分探索が使えるデータ構造を使う。
//   - 静的な場合: vectorをsortして二分探索
//   - 動的 && 削除して良い場合: set,multiset,priority_queue
//     - left,rightを指定したい場合: set,multiset
//     - leftは常に先頭で、rightを指定したい場合: priority_queue
//   - 動的 && 削除が許容されない場合: fenwick_tree
// - 区間数え上げは、条件が要素間で同じである必要がある。条件が要素間でずれる場合は、offsetなどを使って調整する
// - カウント配列という考え方
//   - 数え上げ問題で、条件判定に過去のカウントを参照する必要があるケースで有効
//   - 範囲が狭くdenseであることが前提
// - 逐次問題における未来への影響管理
//   - 蟻本p73のガソスタが類題
//   - 逐次問題である地点の影響が未来に及ぶ時、未来に対して情報を先に記録する/遅延する というアプローチが有効なケースがある

// mutisetによる解法
int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    multiset<int> st;
    for (int i = 0; i < N; i++) {
        auto s = st.begin(), t = st.lower_bound(i);
        while (s != t) s = st.erase(s);

        A[i] += st.size();
        st.insert(A[i] + i);
        A[i] = max(0, A[i] - (N - i - 1));
    }

    for (auto v : A) cout << v << ' ';
    cout << endl;
}

// priority_queueによる解法
int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; i++) {
        while (!pq.empty()) {
            int a = pq.top();
            if (a < i) pq.pop();
            else break;
        }

        A[i] += pq.size();
        pq.push(A[i] + i);
        A[i] = max(0, A[i] - (N - i - 1));
    }

    for (auto v : A) cout << v << ' ';
    cout << endl;
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<int> r(N);  // r[i]:=i年後に配り終える人数
    int s = 0;
    for (int i = 0; i < N; i++) {
        A[i] += s;
        r[min(A[i] + i, N - 1)]++;
        A[i] = max(0, A[i] - (N - i - 1));

        s++;
        s -= r[i];
    }

    for (auto v : A) cout << v << ' ';
    cout << endl;
}
