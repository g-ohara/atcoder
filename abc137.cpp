/*
ABC #137 (2020.04.06 バーチャル参加)
Dでは意気揚々と動的計画法を実装したが、TLE。
解説を参考に、優先度付きキューを用いて正解した。
こりゃ便利だ。
*/
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

void A(void) {

	int A, B; cin >> A >> B;

	cout << max({ A + B, A - B, A * B }) << flush;
	return;
}

void B_One_Clue(void) {

	int K, X; cin >> K >> X;

	int loopMin = max(X - K + 1, -1000000);
	int loopMax = min(X + K - 1, 1000000);
	
	for (int loop = loopMin; loop <= loopMax; loop++) cout << loop << " ";
	cout << flush;
	return;
}

void C_Green_Bin(void) {

	int N; cin >> N;
	map<map<char, int>, int> dict;
	rep(loop, N) {
		string s; cin >> s;
		map<char, int> word;
		for (char it : s) word[it]++;
		dict[word]++;
	}

	long long counter = 0;
	for (auto loop = dict.begin(); loop != dict.end(); loop++) {
		if (loop->second > 1) counter += (long long)loop->second * ((long long)loop->second - 1) / 2;
	}

	cout << counter << flush;
	return;
}

void D_Summer_Vacation(void) {

	struct Job { 
		int day = 0; 
		int salary = 0;
		bool operator < (const Job& right) { return day < right.day; }
	};
	
	int N, M; cin >> N >> M;
	auto c1 = [](Job l, Job r) { return l.day > r.day; };
	priority_queue < Job, vector<Job>, decltype(c1) > job(c1);
	rep(loop, N) {
		int A, B; cin >> A >> B;
		job.push({ A,B });
	}

	auto c2 = [](Job l, Job r) { return l.salary < r.salary; };
	priority_queue < Job, vector<Job>, decltype(c2) > candidate(c2);
	int income = 0;
	for (int day = M; day >= 0; day--) {
		while (1) {
			if (job.size() > 0 && job.top().day == M - day) {
				candidate.push(job.top());
				job.pop();
			}
			else {
				break;
			}
		}
		if (candidate.size() > 0) {
			income += candidate.top().salary;
			candidate.pop();
		}
	}

	cout << income << flush;
	return;
}

int main(void) {

	//A();
	//B_One_Clue();
	//C_Green_Bin();
	D_Summer_Vacation();
	return 0;
}
