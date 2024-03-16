/*
ABC #151

*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Memo {
	long long fact = 0;
	long long fact_inv = 0;
	long long inv = 0;
};
class Combination {
private:
	int m_module = 1000000007;
	vector<struct Memo> memo;
public:
	int calculate(int, int);
	Combination(int, int);
};
int Combination::calculate(int n, int k) {
	return ((memo[n].fact * memo[k].fact_inv) % m_module * memo[n - k].fact_inv) % m_module;
}
Combination::Combination(int memo_max, int module = 1000000007) {
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

void A_Next_Alphabet(void) {

	char C;
	cin >> C;
	cout << char(C + 1) << flush;
	return;
}

void B_Achieve_the_Goal(void) {

	int N, K, M;
	cin >> N >> K >> M;

	vector<int> A(N - 1);
	for (int& it : A) cin >> it;

	int re = M * N - accumulate(A.begin(), A.end(), 0);

	if (re < 0)			cout << 0 << flush;
	else if (re > K)	cout << -1 << flush;
	else				cout << re << flush;
	return;
}

void C_Welome_to_AtCoder(void) {

	int N, M;
	cin >> N >> M;

	struct Problem {
		bool correct = false;
		int penalty = 0;
	};
	vector<struct Problem> problem(N);
	for (int loop = 0; loop < M; loop++) {
		int p;
		string S;
		cin >> p >> S;

		if (S.compare("AC") == 0) problem[p - 1].correct = true;
		else if (!problem[p - 1].correct) problem[p - 1].penalty++;
	}

	int corSum = 0;
	int penSum = 0;
	for (struct Problem it :problem) {
		if (it.correct) {
			corSum++;
			penSum += it.penalty;
		}
	}
	cout << corSum << " " << penSum << flush;
	return;
}

void E_Max_Min_Sum(void) {

	int N, K;
	cin >> N >> K;
	vector<int> A(N);
	for (int& it : A) cin >> it;
	sort(A.begin(), A.end());

	if (K == 1) {
		cout << 0 << flush;
	}
	else {
		class Combination com(N - 1);
		long long sumMax = 0;
		for (int loop = K - 1; loop < N; loop++) {
			sumMax = (sumMax + (long long)A[loop] * (long long)com.calculate(loop, K - 1)) % 1000000007;
		}
		long long sumMin = 0;
		for (int loop = 0; loop <= N - K; loop++) {
			sumMin = (sumMin + (long long)A[loop] * (long long)com.calculate(N - loop - 1, K - 1)) % 1000000007;
		}
		cout << sumMax - sumMin << flush;
		/*
		long long sum = 0;
		for (int start = 0; start < N; start++) {
			for (int goal = start + K - 1; goal < N; goal++) {
				sum = (sum + ((long long)A[goal] - A[start]) * com.calculate(goal - start - 1, K - 2) % 1000000007) % 1000000007;
			}
		}
		cout << sum << flush;
		*/
	}
	return;
}

int main(void) {

	//A_Next_Alphabet();
	//B_Achieve_the_Goal();
	//C_Welome_to_AtCoder();
	E_Max_Min_Sum();
	return 0;
}
