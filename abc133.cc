/*
ABC #134 (2020.04.23 バーチャル参加)

大変難しい。
Cは一つのケースでWAが出てしまい、最後まで解消できなかった。
解説を読んでもバグがどこに潜んでいるか判らない。要確認。
*/
#include "bits/stdc++.h"

using namespace std;

#define rep(loop, N) for (int loop = 0; loop < N; loop++)

struct Node {
	Node* parent = NULL;
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
long long gcd(long long num1, long long num2) {
	return num2 == 0 ? num1 : gcd(num2, num1 % num2);
}

struct Memo {
	long long fact = 0;
	long long fact_inv = 0;
	long long inv = 0;
};
class Combination1 {
private:
	long long m_module = 1000000007;
	vector<struct Memo> memo;
public:
	long long calculate(int, int);
	Combination1(int, long long);
};
long long Combination1::calculate(int n, int k) {
	return ((memo[n].fact * memo[k].fact_inv) % m_module * memo[n - k].fact_inv) % m_module;
}
Combination1::Combination1(int memo_max, long long module = 1000000007) {
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

void A_T_or_T(void) {

	int N, A, B; cin >> N >> A >> B;

	cout << min(A * N, B) << endl;
	return;
}

void B_Good_Distance(void) {

	int N, D; cin >> N >> D;
	vector<vector<int>> X(N, vector<int>(D));
	for (vector<int>& point : X) {
		for (int& coordinate : point) cin >> coordinate;
	}

	int counter = 0;
	rep(i, N) {
		for (int j = i + 1; j < N; j++) {
			int distance = 0;
			rep(index, D) {
				distance += (int)pow((X[i][index] - X[j][index]), 2);
			}
			rep(num, 130) {
				if (distance == (int)pow(num, 2)) {
					counter++;
					break;
				}
			}
		}
	}

	cout << counter << endl;
	return;
}

void C_Remainder_Minimization_2019(void) {

	int L, R; cin >> L >> R;

	vector<bool> remainder(2019);
	for (int num = L; num <= R; num++) {
		remainder[num % 2019] = true;
		if (num % 2019 == 0) break;
	}

	int answer = 2018;
	for (int i = 0; i < 2019; i++) {
		if (remainder[i]) {
			for (int j = i + 1; j < 2019; j++) {
				if (remainder[j]) {
					answer = min(answer, (i * j) % 2019);
				}
			}
		}
	}
	
	cout << answer << endl;
	return;
}

int main(void) {

	cout << fixed << setprecision(15);

	//A_T_or_T();
	//B_Good_Distance();
	C_Remainder_Minimization_2019();
	return 0;
}
