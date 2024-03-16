/*
ABC #134 (2020.04.22 バーチャル参加)

Eまでスムーズに進めた。
Eは二分探索するところを最初に逐次探索にして提出してTLEになってしまった。
闇雲に提出すると不正解のペナルティが出るから、計算量をあらかじめ計算して安心できるところまで進めたい。
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

void A_Dodecagon(void) {

	int r; cin >> r;
	
	cout << 3 * r * r << endl;
	return;
}

void B_Golden_Apple(void) {

	int N, D; cin >> N >> D;

	cout << (int)ceil((double)N / (double)(2 * D + 1)) << endl;
	return;
}

void C_Exception_Handling(void) {

	int N; cin >> N;
	vector<int> A(N); for (int& it : A) cin >> it;

	int max_index = distance(A.begin(), max_element(A.begin(), A.end()));
	int max_num = A[max_index];
	A[max_index] = 0;
	int second_index = distance(A.begin(), max_element(A.begin(), A.end()));
	int second_num = A[second_index];

	rep(index, N) {
		if (index == max_index) cout << second_num << endl;
		else					cout << max_num << endl;
	}
	return;
}

void D_Preparing_Boxes(void) {

	struct Box { int num; bool ball; };

	int N; cin >> N;
	vector<Box> box(N); for (Box& it : box) cin >> it.num;

	int M = 0;
	for (int index = N - 1; index >= 0; index--) {
		int num = index + 1;
		int sum = 0;
		for (int index2 = index + num; index2 < N; index2 += num) {
			if (box[index2].ball) sum++;
		}
		if (sum % 2 != box[index].num) {
			box[index].ball = true;
			M++;
		}
	}

	cout << M << endl;
	rep(index, N) {
		if (box[index].ball) cout << index + 1 << " ";
	}
	cout << endl;
	return;
}

void E_Sequence_Decomposing(void) {

	int N; cin >> N;
	vector<int> color;
	rep(loop, N) {
		int A; cin >> A;
		int start = 0, end = color.size();
		if (end > 0) {
			if (color[0] < A) {
				color[0] = A;
			}
			else {
				while (1) {
					if (end == start + 1) break;
					int index = (start + end) / 2;
					if (color[index] < A)	end = index;
					else					start = index;
				}
				if (end == color.size())	color.push_back(A);
				else						color[end] = A;
			}
		}
		else {
			color.push_back(A);
		}
	}

	cout << color.size() << endl;
	return;
}

int main(void) {

	cout << fixed << setprecision(15);

	//A_Dodecagon();
	//B_Golden_Apple();
	//C_Exception_Handling();
	//D_Preparing_Boxes();
	E_Sequence_Decomposing();
	return 0;
}
