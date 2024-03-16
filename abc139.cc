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

void A_Tenki(void) {

	string S, T; cin >> S >> T;

	int counter = 0;
	rep(index, 3) if (S[index] == T[index]) counter++;
	
	cout << counter << flush;
	return;
}

void B_Power_Socket(void) {
	
	int A, B; cin >> A >> B;
	
	cout << ceil(((double)B - 1.0) / ((double)A - 1.0)) << flush;
	return;
}

void C_Lower(void) {

	int N; cin >> N;
	vector<int> H(N); for (int& it : H)cin >> it;

	int counter = 0;
	int maxCount = 0;
	rep(index, N - 1) {
		if (H[index] >= H[index + 1]) {
			counter++;
		}
		else {
			maxCount = max(maxCount, counter);
			counter = 0;
		}
	}
	maxCount = max(maxCount, counter);
	
	cout << maxCount << flush;
	return;
}

void D_ModSum(void) {

	int N; cin >> N;

	cout << (long long)N * ((long long)N - 1) / 2 << flush;
	return;
}

void E_League(void) {

	int N; cin >> N;
	struct Player { int index = 0; vector<int> enemy; };
	vector<Player> player(N);
	for (Player& he : player) {
		rep(loop, N - 1) {
			int A; cin >> A;
			he.enemy.push_back(A - 1);
		}
	}

	int counter = 0;
	int NUM = N * (N - 1) / 2;
	vector<bool> played(N);
	for (int day = 1; day <= NUM; day++) {
		fill(played.begin(), played.end(), false);
		bool counter2 = false;
		rep(loop, N) {
			if (played[loop] == false && player[loop].index < N - 1) {
				int enemy = player[loop].enemy[player[loop].index];
				if (played[enemy] == false && player[enemy].enemy[player[enemy].index] == loop) {
					player[loop].index++;
					player[enemy].index++;
					played[loop] = true;
					played[enemy] = true;
					counter++;
					counter2 = true;
				}
			}
		}
		if (counter == NUM) {
			cout << day << flush;
			return;
		}
		else if (counter2 == false) {
			cout << -1 << flush;
			return;
		}
	}
	return;
}

int main(void) {

	//A_Tenki();
	//B_Power_Socket();
	//C_Lower();
	//D_ModSum();
	E_League();
	return 0;
}
