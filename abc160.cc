/*
ABC #160 (2020.03.28 参加)
AからEまでわりあいスムーズに正解できた。
今までで最も良い出来だろうか。
解説を読んでも、アルゴリズムに間違いはない。
ただ、Eはかなり冗長で可読性の低いコードになってしまった。
もっと上手い書き方がありそうだが…
Fのような木の問題は、データ構造を勉強しなくては歯が立ちそうもない。
*/

#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

map<long long, int> factorization(long long N) {
	map<long long, int> re;
	while (true) {
		if (N % 2 == 0) {
			N /= 2;
			re[2]++;
			if (N == 1) break;
		}
	}
	if (N > 1) re[N]++;
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

void A_Coffee(void) {
	
	string S; cin >> S;
	
	cout << ((S[2] == S[3] && S[4] == S[5]) ? "Yes" : "No");
	return;
}

void B_Golden_Coins(void) {
	
	int X; cin >> X;
	
	int happy = 0;
	happy = int(X / 500) * 1000 + int(X % 500 / 5) * 5;
	
	cout << happy << flush;
	return;
}

void C_Traveling_Salesman_around_Lake(void) {
	
	int K, N; cin >> K >> N;
	vector<int> A(N); for (int& it : A) cin >> it;

	int dMax = A[0] + (K - A[N - 1]);
	for (int loop = 1; loop < N; loop++) dMax = max(dMax, A[loop] - A[loop - 1]);

	cout << K - dMax << flush;
	return;
}

void D_Line(void) {

	int N, X, Y; cin >> N >> X >> Y;

	vector<int> counter(N - 1);
	for (int start = 1; start < N; start++) {
		for (int goal = start + 1; goal <= N; goal++) {
			int k = min(goal - start, abs(X - start) + abs(Y - goal) + 1);
			counter[k - 1]++;
		}
	}

	for (int it : counter) cout << it << endl;
	return;
}

void E_Red_and_Green_Apples(void) {

	int X, Y, A, B, C; cin >> X >> Y >> A >> B >> C;
	vector<int> p(A), q(B), r(C);
	for (int& it : p) cin >> it;
	for (int& it : q) cin >> it;
	for (int& it : r) cin >> it;
	sort(p.begin(), p.end(), greater<int>());
	sort(q.begin(), q.end(), greater<int>());
	sort(r.begin(), r.end(), greater<int>());

	int pFlag = 0, qFlag = 0, rFlag = 0;
	int counter = 0;
	long long taste = 0;
	while (counter < X + Y && (pFlag < X || qFlag < Y)) {
		if (pFlag == X) {
			if (r[rFlag] > q[qFlag]) {
				taste += r[rFlag];
				rFlag++;
			}
			else {
				taste += q[qFlag];
				qFlag++;
			}
		}
		else if (qFlag == Y) {
			if (r[rFlag] > p[pFlag]) {
				taste += r[rFlag];
				rFlag++;
			}
			else {
				taste += p[pFlag];
				pFlag++;
			}
		}
		else {
			if (rFlag < C && r[rFlag] > p[pFlag] && r[rFlag] > q[qFlag]) {
				taste += r[rFlag];
				rFlag++;
			}
			else {
				if (p[pFlag] > q[qFlag]) {
					taste += p[pFlag];
					pFlag++;
				}
				else {
					taste += q[qFlag];
					qFlag++;
				}
			}
		}
		counter++;
	}

	cout << taste << flush;
	return;
}

int main(void) {

	//A_Coffee();
	B_Golden_Coins();
	//C_Traveling_Salesman_around_Lake();
	//D_Line();
	//E_Red_and_Green_Apples();
	return 0;
}
