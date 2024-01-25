#include "bits/stdc++.h"

#define rep(loop, N) for (int loop = 0; loop < N; loop++)
using namespace std;

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

void A_Transfer(void) {

	int A, B, C; cin >> A >> B >> C;

	cout << max(-A + B + C, 0) << flush;
	return;
}

void B_Uneven_Numbers(void) {

	int N; cin >> N;

	int counter = 0;
	for (int length = 1; length <= 6; length+=2) {
		if (N < (int)pow(10, length)) {
			counter += max(N - (int)pow(10, length - 1) + 1, 0);
			break;
		}
		else {
			counter += (int)pow(10, length) - (int)pow(10, length - 1);
		}
	}

	cout << counter << flush;
	return;
}

void C_Build_Stairs(void) {

	int N; cin >> N;
	vector<int> H(N); for (int& it : H)cin >> it;

	for (int index = N - 2; index >= 0; index--) {
		if (H[index] > H[index + 1]) H[index]--;
		if (H[index] > H[index + 1]) {
			cout << "No" << flush;
			return;
		}
	}
	cout << "Yes" << flush;
	return;
}

void D_Gathering_Children(void) {

	string S; cin >> S;
	
	vector<int> num;
	int index = -1;
	for (char& it : S) {
		if (num.size() % 2 == 0 && it == 'R' || num.size() % 2 == 1 && it == 'L') {
			num.push_back(1);
			index++;
		}
		else {
			num[index]++;
		}
	}

	rep(index, num.size()) {
		if (index % 2 == 0) {
			rep(loop, num[index] - 1) {
				cout << 0 << " ";
			}
			cout << (num[index] + 1) / 2 + num[index + 1] / 2 << " ";
		}
		else {
			cout << (num[index] + 1) / 2 + num[index - 1] / 2 << " ";
			rep(loop, num[index] - 1) {
				cout << 0 << " ";
			}
		}
	}
	cout << endl;
	return;
}

void E_Max_GCD(void) {

	int N, K; cin >> N >> K;
	vector<int> A(N); for (int& it : A) cin >> it;

	sort(A.begin(), A.end());
	for (int X = A[N - 1] + K; X > 1; X--) {
		long long pCounter = 0, mCounter = 0;
		for (int it : A) {
			if (it % X <= X / 2)	mCounter += it % X;
			else					pCounter += X - it % X;
		}
		if ((pCounter - mCounter) % (long long)X == 0 && (long long)max(pCounter, mCounter) <= (long long)K) {
			cout << X << endl;
			return;
		}
	}

	cout << 1 << endl;
	return;
}

int main(void) {

	//A_Transfer();
	//B_Uneven_Numbers();
	//C_Build_Stairs();
	//D_Gathering_Children();
	E_Max_GCD();
	return 0;
}
