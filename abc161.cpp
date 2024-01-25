/*
ABC #161(2020.04.04 バーチャル参加)
難しい。
Dでは最後まで正しい答えが出なかった。
解説によれば、Queueを用いるとよいようだ。
別段特別な概念ではないが、今までそういう基礎的なデータ構造を知らずにやってきた。
こういうイメージを持っておかないから、コードが乱雑になってしまう。反省。
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
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

void A_ABC_Swap(void) {

	int X, Y, Z; cin >> X >> Y >> Z;

	cout << Z << " " << X << " " << Y;
	return;
}

void B_Popular_Vote(void) {

	int N, M; cin >> N >> M;
	vector<int> A(N); for (int& it : A)cin >> it;

	sort(A.begin(), A.end(), greater<int>());
	int sum = accumulate(A.begin(), A.end(), 0);
	rep(index, M) {
		if (A[index] * 4 * M < sum) {
			cout << "No" << flush;
			return;
		}
	}
	cout << "Yes" << flush;
	return;
}

void C_Replacing_Integer(void) {

	long long N, K; cin >> N >> K;
	
	if (N > K) N -= (N / K - 1) * K;
	while (abs(N - K) < N) N = abs(N - K);
	
	cout << N << flush;
	return;
}

void D_Lunlun_Number(void) {

	int K; cin >> K;
	/*
	vector<int> num(10);
	fill(num.begin(), num.end(), 1);
	num[0] = 0;
	int counter = 9;
	if (K < 10) {
		cout << K << flush;
		return;
	}
	for (int length = 2;; length++) {
		vector<int> pre = num;
		num[0] = pre[0] + pre[1];
		num[9] = pre[8] + pre[9];
		for (int index = 1; index <= 8; index++) {
			num[index] = pre[index - 1] + pre[index] + pre[index + 1];
		}
		if (accumulate(num.begin(), num.end(), 0) <= K) {
			counter += accumulate(num.begin(), num.end(), 0);
		}
		else{
			counter++;
			fill(num.begin(), num.end(), 0);
			num[length - 1] = 1;
			while (counter < K) {
				int index = 0;
				while (1) {
					if (index < length - 1 && num[index] == num[index + 1] + 1) {
						index++;
					}
					else {
						num[index]++;
						for (int index2 = index - 1; index2 >= 0; index2--) {
							num[index2] = (num[index2 + 1] == 0 ? 0 : num[index2 + 1] - 1);
						}
						break;
					}
				}
				counter++;
			}
			for (int index = length - 1; index >= 0; index--)cout << num[index] << flush;
			return;
		}
	}
	*/
	return;
}

int main(void) {

	//A_ABC_Swap();
	//B_Popular_Vote();
	//C_Replacing_Integer();
	D_Lunlun_Number();
	return 0;
}
