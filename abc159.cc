/*
ABC #159 (2020.03.23 参加)

AからDまでは50分で正解できた。
Eは横方向へのすべての割り方について、貪欲法で探索すればよい。
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

void A_The_Number_of_Even_Pairs(void) {

	int N, M; cin >> N >> M;
	cout << (N * (N - 1) + M * (M - 1)) / 2 << flush;
	return;
}

void B_String_Palindrome(void) {

	string S; cin >> S;
	int N = S.size();

	for (int loop = 0; loop < N; loop++) {
		if (S[loop] != S[N - loop - 1]) {
			cout << "No" << flush;
			return;
		}
	}
	for (int loop = 0; loop * 2 <= N - 3; loop++) {
		if (S[loop] != S[(N - 3) / 2 - loop]) {
			cout << "No" << flush;
			return;
		}
	}
	for (int loop = (N + 1) / 2; loop < N; loop++) {
		if (S[loop] != S[N - 1 + (N + 1) / 2 - loop]) {
			cout << "No" << flush;
			return;
		}
	}
	cout << "Yes" << flush;
	return;
}

void C_Maximum_Volume(void) {

	int L; cin >> L;
	cout << setprecision(20) << (double)L * L * L / 27.0 << flush;
	return;
}

void D_Banned_K(void) {

	int N; cin >> N;
	vector<int> A(N);
	map<int, int> num;
	for (int& it : A) {
		cin >> it;
		num[it]++;
	}

	long long re0 = 0;
	for (auto loop = num.begin(); loop != num.end(); loop++) {
		re0 += (long long)loop->second * ((long long)loop->second - 1) / 2;
	}
	for (int k = 1; k <= N; k++) {
		if (num[A[k - 1]] == 1) cout << re0 << endl;
		else					cout << re0 - num[A[k - 1]] + 1 << endl;	
	}
	return;
}

void E_Dividing_Chocolate(void) {

	int H, W, K; cin >> H >> W >> K;
	vector<vector<bool>> white(H, vector<bool>(W));
	vector<vector<int>> num(H, vector<int>(W));
	for (int row = 0; row < H;row++) {
		for (int column = 0; column < W;column++) {
			char S; cin >> S;
			white[row][column] = (S == '1');
			num[row][column] = (white[row][column]) ? 1 : 0;
			if (row > 0)				num[row][column] += num[row - 1][column];
			if (column > 0)				num[row][column] += num[row][column - 1];
			if (row > 0 && column > 0)	num[row][column] -= num[row - 1][column - 1];
		}
	}

	return;
}

int main(void) {

	//A_The_Number_of_Even_Pairs();
	//B_String_Palindrome();
	//C_Maximum_Volume();
	//D_Banned_K();
	E_Dividing_Chocolate();
	return 0;
}
