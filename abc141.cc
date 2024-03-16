/*
ABC #141 (2020.04.03 バーチャル参加)
D,Eが解けなかった。
Eは二分探索の実装に手間取ってしまった。
探索範囲の両端の処理や終了条件の設定にまだ慣れていない。
解説によれば、Z-Algorithmというのを用いるとよいようだ。
まだまだ修行が足りない。
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

void A_Weather_Prediction(void) {

	string S; cin >> S;

	string weather[3] = { "Sunny","Cloudy","Rainy" };
	for (int loop = 0; loop < 3; loop++) {
		if (S == weather[loop]) {
			cout << weather[(loop + 1) % 3] << flush;
			break;
		}
	}
	return;
}

void B_Tap_Dance(void) {

	string S; cin >> S;

	for (int index = 0; index < (int)S.size(); index++) {
		if (index % 2 == 0 && S[index] == 'L' || index % 2 == 1 && S[index] == 'R') {
			cout << "No" << flush;
			return;
		}
	}
	cout << "Yes" << flush;
	return;
}

void C_Attack_Survival(void) {

	int N, K, Q; cin >> N >> K >> Q;
	vector<int> player(N);
	fill(player.begin(), player.end(), 0);
	for (int loop = 0; loop < Q; loop++) {
		int A; cin >> A;
		player[A - 1]++;
	}

	for (int it : player) cout << (it + K - Q > 0 ? "Yes" : "No") << endl;
	return;
}

void D_Powerful_Discount_Tickets(void) {

	int N, M; cin >> N >> M;
	vector<int> A(N); for (int& it : A) cin >> it;

	long long start = -1;
	long long end = accumulate(A.begin(), A.end(), 0LL);
	
	while (1) {
		long long X = (start + end) / 2;
		int counter = 0;
		for (int it : A) {
			for (int loop = 0; loop < M; loop++) {
				if (it / (int)pow(2, loop) <= X) {
					counter += loop;
					break;
				}
			}
		}
		if (counter > M)	start = X;
		else				end = X;
		if (counter == M || start + 1 == end) {
			if (start + 1 == end) X = end;
			for (int& it : A) {
				for (int loop = 0; loop < M; loop++) {
					if (it / (int)pow(2, loop) <= X) {
						it /= (int)pow(2, loop);
						break;
					}
				}
			}
			sort(A.begin(), A.end(), greater<int>());
			for (int loop = 0; loop < M - counter; loop++) {
				A[distance(A.begin(),max_element(A.begin(), A.end()))] /= 2;
			}
			break;
		}
	}
	
	cout << accumulate(A.begin(), A.end(), 0LL) << flush;
	return;
}

void E_Who_Says_A_Pun(void) {

	int N; cin >> N;
	string S; cin >> S;

	int start = 0;
	int end = N / 2 + 1; 
	for (int index = 0; index < N - 1; index++) {
		if (S.substr(index + 1, N - index - 1).find(S[index]) != string::npos) {
			while (1) {
				int length = (start + end) / 2;
				for (int start1 = 0; start1 + length * 2 <= N; start1++) {
					string sample = S.substr(start1, length);
					if (S.substr(start1 + length, N - start1 - length).find(sample) != string::npos) {
						start = length;
						break;
					}
					if (start1 + length * 2 == N) end = length;
				}
				if (start + 1 == end) {
					cout << start << flush;
					return;
				}
			}
		}
		cout << 0 << flush;
		return;
	}
	
}

int main(void) {

	//A_Weather_Prediction();
	//B_Tap_Dance();
	//C_Attack_Survival();
	//D_Powerful_Discount_Tickets();
	E_Who_Says_A_Pun();
	return 0;
}
