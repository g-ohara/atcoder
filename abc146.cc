#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits.h>
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

void A_Cannot_Wait_for_Holiday(void) {

	string S;
	cin >> S;

	if		(S.compare("SUN") == 0) cout << 7 << flush;
	else if (S.compare("MON") == 0) cout << 6 << flush;
	else if (S.compare("TUE") == 0) cout << 5 << flush;
	else if (S.compare("WED") == 0) cout << 4 << flush;
	else if (S.compare("THU") == 0) cout << 3 << flush;
	else if (S.compare("FRI") == 0) cout << 2 << flush;
	else							cout << 1 << flush;

	return;
}

void B_ROT_N(void) {

	int N;
	string S;
	cin >> N >> S;

	for (char it : S) cout << char(((int)it - (int)'A' + N) % 26 + (int)'A') << flush;
	return;
}

void C_Buy_an_Integer(void) {

	long long A, B, X;
	cin >> A >> B >> X;

	long long N = 0;
	for (long long d = 1; d < 10; d++) {
		long long cand = (X - B * d) / A;
		if (cand >= (long long)pow(10, d - 1) && cand < (long long)pow(10, d)) N = cand;
	}
	if (X >= A * 1000000000 + (B * 10)) N = 1000000000;
	cout << N << flush;
	return;
}

void E_Rem_of_Sum_is_Num(void) {

	int N, K; cin >> N >> K;
	vector<long long> sum(N + 1);
	sum[0] = 0;
	for (int loop = 1; loop <= N; loop++) {
		int A; cin >> A;
		sum[loop] = A + sum[loop - 1];
	}

	long long counter = 0;
	for (int size = 1; size < K; size++) {
		for (int start = 1; start <= N - size + 1; start++) {
			int end = start + size - 1;
			if ((sum[end] - sum[start - 1]) % K == size) counter++;
		}
	}

	cout << counter << flush;
	return;
}

int main(void) {

	//A_Cannot_Wait_for_Holiday();
	//B_ROT_N();
	C_Buy_an_Integer();
	//E_Rem_of_Sum_is_Num();
	return 0;
}
