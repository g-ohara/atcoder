#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#define rep(loop, N) for (int loop = 0; loop < N; loop++)

using namespace std;

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

void A_Password(void) {

	int N; cin >> N;

	cout << N * N * N << flush;
	return;
}

void B_Buffet(void) {

	int N; cin >> N;
	vector<int> A(N); for (int& it : A)cin >> it;
	int sum = 0;
	rep(loop, N) {
		int B; cin >> B;
		sum += B;
	}
	vector<int> C(N - 1); for (int& it : C)cin >> it;
	
	rep(index, N - 1) if (A[index] + 1 == A[index + 1]) sum += C[A[index] - 1];

	cout << sum << flush;
	return;
}

void C_Maximal_Value(void) {

	int N; cin >> N;
	vector<int> B(N - 1); for (int& it : B)cin >> it;

	int sum = B[0] + B[N - 2];
	for (int index = 0; index < N - 2; index++) {
		sum += min(B[index], B[index + 1]);
	}

	cout << sum << flush;
	return;
}

void E_Second_Sum(void) {

	int N; cin >> N;
	vector<int> P(N); for (int& it : P)cin >> it;

	long long sum = 0;
	rep(index, N) {
		int leftMax = -1, leftMin = -1;
		for (int left = index - 1; left >= 0; left--) {
			if (P[left] > P[index]) {
				if (leftMin == -1) {
					leftMin = left;
				}
				else {
					leftMax = left;
					break;
				}
			}
		}
		int rightMax = N, rightMin = N;
		for (int right = index + 1; right < N; right++) {
			if (P[right] > P[index]) {
				if (rightMin == N) {
					rightMin = right;
				}
				else {
					rightMax = right;
					break;
				}
			}
		}
		sum += ((long long)leftMin - (long long)leftMax) * ((long long)rightMin - (long long)index) * (long long)P[index];
		sum += ((long long)index - (long long)leftMin) * ((long long)rightMax - (long long)rightMin) * (long long)P[index];
	}

	cout << sum << flush;
	return;
}

int main(void) {

	//A_Password();
	//B_Buffet();
	//C_Maximal_Value();
	E_Second_Sum();
	return 0;
}
