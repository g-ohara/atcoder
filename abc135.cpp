/*
ABC #135 (2020.04.19 バーチャル参加)

約2週間ぶりの参加。やはり多少の腕のなまりを感じる。
Dは、動的計画法で解けることに気づかなかった。
しっかり勘を取り戻そう。
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

void A_Harmony(void) {

	int A, B; cin >> A >> B;

	if ((A + B) % 2 == 0)	cout << (A + B) / 2 << endl;
	else					cout << "IMPOSSIBLE" << endl;
	return;
}

void B(void) {

	int N; cin >> N;
	vector<int> p(N); for (int& it : p) cin >> it;

	int counter = 0;
	rep(index, N) if (p[index] != index + 1) counter++;

	cout << (counter <= 2 ? "YES" : "NO") << endl;
	return;
}

void C_City_Saver(void) {

	int N; cin >> N;
	vector<int> A(N + 1), B(N);
	for (int& it : A) cin >> it;
	for (int& it : B) cin >> it;

	long long counter = 0;
	rep(index, N) {
		int enemy = min(A[index] + A[index + 1], B[index]);
		counter += enemy;
		A[index + 1] -= max(enemy - A[index], 0);
	}

	cout << counter << endl;
	return;
}

void D_Digits_Parade(void) {

	string S; cin >> S;
	
	vector<int> dp(13), dpNew(13);
	dp[0] = 1;
	rep(index, (int)S.size()) {
		if (S[index] == '?') {
			rep(index2, 13) {
				rep(num, 10) {
					rep(target, 13) {
						if ((target * 10 + num) % 13 == index2) {
							dpNew[index2] = (dpNew[index2] + dp[target]) % 1000000007;
						}
					}
				}
			}
		}
		else {
			int num = S[index] - '0';
			rep(index2, 13) {
				rep(target, 13) {
					if ((target * 10 + num) % 13 == index2) {
						dpNew[index2] = (dpNew[index2] + dp[target]) % 1000000007;
					}
				}
			}
		}
		dp = dpNew;
		fill(dpNew.begin(), dpNew.end(), 0);
	}

	cout << dp[5] << endl;
	return;
}

int main(void) {

	//A_Harmony();
	//B();
	//C_City_Saver();
	D_Digits_Parade();
	return 0;
}
