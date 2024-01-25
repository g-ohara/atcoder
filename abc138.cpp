/*
ABC #138 (2020.04.05 バーチャル参加)
Dは木構造の問題であり、今まで触れなかったところであった。
今回ごく簡単な木構造のクラスを設計した。
今後必要に応じて設計を更新していく。
また、プリコンパイル済みヘッダファイルを用意してビルド時間の短縮を図った。
*/
#include "bits/stdc++.h"

#define rep(loop, N) for (int loop = 0; loop < N; loop++)
using namespace std;

struct Node {
	Node* parent;
	vector<Node*> child;
	long long value = 0;
};
struct Edge {
	int parent = 0;
	int child = 0;
	bool operator <(const Edge& right) const { return parent < right.parent; }
};
struct Tree {
	vector<Node> node;
	Tree(int, vector<Edge>);
};
Tree::Tree(int nodeNum, vector<Edge> edge) {
	node.resize(nodeNum);
	for (Edge& it : edge) {
		node[it.child].parent = &node[it.parent];
		node[it.parent].child.push_back(&node[it.child]);
	}
}

map<long long, int> factorization(long long N) {
	map<long long, int> re;
	while (true) {
		if (N % 2 == 0) {
			N /= 2;
			re[2]++;
			if (N == 1) break;
		}
		else {
			break;
		}
	}
	for (int loop = 3; (long long)loop * (long long)loop <= N; loop += 2) {
		if (N % loop == 0) {
			N /= loop;
			re[loop]++;
			loop -= 2;
			if (N == 1) break;
		}
	}
	if (N > 1) re[N]++;
	return re;
}

struct Memo {
	long long fact = 0;
	long long fact_inv = 0;
	long long inv = 0;
};
class Combination1 {
private:
	int m_module = 1000000007;
	vector<struct Memo> memo;
public:
	int calculate(int, int);
	Combination1(int, int);
};
int Combination1::calculate(int n, int k) {
	return ((memo[n].fact * memo[k].fact_inv) % m_module * memo[n - k].fact_inv) % m_module;
}
Combination1::Combination1(int memo_max, int module = 1000000007) {
	m_module = module;
	memo.push_back({ 1,1,0 });
	memo.push_back({ 1,1,1 });
	for (int loop = 2; loop <= memo_max; loop++) {
		struct Memo temp;
		temp.fact = (memo[loop - 1].fact * loop) % m_module;
		temp.inv = m_module - (memo[m_module % loop].inv * int(m_module / loop)) % m_module;
		temp.fact_inv = (memo[loop - 1].fact_inv * temp.inv) % m_module;
		memo.push_back(temp);
	}
}

class Combination2 {
private:
	int size = 0;
	bool add(int);
public:
	vector<int> sequence;
	bool next_combination(void);
	Combination2(int, int);
};
bool Combination2::add(int index) {
	if (index == (int)sequence.size() - 1 && sequence[index] == size - 1
		|| index < (int)sequence.size() - 1 && sequence[index] == sequence[index + 1] - 1) {
		if (index == 0) {
			return false;
		}
		else {
			bool re = add(index - 1);
			sequence[index] = sequence[index - 1] + 1;
			return re;
		}
	}
	else {
		sequence[index]++;
		return true;
	}
}
bool Combination2::next_combination(void) {
	return (sequence.size() == 0) ? false : add(sequence.size() - 1);
}
Combination2::Combination2(int n, int r) {
	size = n;
	for (int loop = 0; loop < r; loop++) sequence.push_back(loop);
	return;
}

void A_Red_or_Not(void) {

	int a; string s; cin >> a >> s;

	cout << (a >= 3200 ? s : "red") << flush;
	return;
}

void B_Resistors_in_Parallel(void) {

	int N; cin >> N;
	double denominator = 0;
	rep(loop, N) {
		int A; cin >> A;
		denominator += (1.0 / A);
	}

	cout << setprecision(20) << 1.0 / denominator << flush;
	return;
}

void C_Alchemist(void) {

	int N; cin >> N;
	vector<double> v(N); for (double& it : v)cin >> it;
	sort(v.begin(), v.end());
	double value = v[0] / pow(2, N - 1);
	for (int loop = 1; loop < N; loop++) {
		if (N - loop < 20) value += v[loop] / pow(2, N - loop);
	}

	cout << setprecision(20) << value << flush;
	return;
}

void D_Ki(void) {
	
	int N, Q; cin >> N >> Q;
	vector<Edge> edge(N - 1);
	for (Edge& it : edge) {
		cin >> it.parent >> it.child;
		it.parent--;
		it.child--;
	}
	Tree tree(N, edge);
	/*
	rep(loop, Q) {
		int p, x; cin >> p >> x;
		p--;
		tree.node[p].value += x;
		for (Node* offspring : tree.node[p].descendant) (*offspring).value += x;
	}
	*/
	rep(loop, Q) {
		int p, x; cin >> p >> x; p--;
		tree.node[p].value += x;
	}
	for (int index = 1; index < N; index++) tree.node[index].value += (*tree.node[index].parent).value;

	for (Node it : tree.node) cout << it.value << " ";
	cout << flush;
	return;
}

int main(void) {
	
	//A_Red_or_Not();
	//B_Resistors_in_Parallel();
	//C_Alchemist();
	D_Ki();
	return 0;
}
