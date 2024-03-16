/*
ABC #148 (2020.03.15)

Cでは何度も不正解が出た。
冷静になれば非常に短くコーディングできるはずが、素因数分解を用いて非常に冗長になった。
入力の大きさが莫大になれば素因数分解を用いたほうが計算量は少ないが、今回の場合は必要なし。
今回のようにミスが連発しないよう、素因数分解の関数をあらかじめ作っておこう。
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

map<long long, int> factorization(long long N) {
	map<long long, int> re;
	for (int loop = 2; loop * loop <= N; loop++) {
		if (N % loop == 0) {
			N /= loop;
			re[loop]++;
			loop--;
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

void A_Round_One(void) {

	int A, B;
	cin >> A >> B;

	/*
	if		(A != 1 && B != 1)	cout << 1 << flush;
	else if (A != 2 && B != 2)	cout << 2 << flush;
	else						cout << 3 << flush;
	*/
	cout << 6 - A - B << flush;
	return;
}

void B_Strings_with_the_Same_Length(void) {

	int N;
	cin >> N;
	string S, T;
	cin >> S >> T;

	for (int loop = 0; loop < N; loop++) cout << S[loop] << T[loop] << flush;
	return;
}

void C_Snack(void) {

	int A, B;
	cin >> A >> B;

	/*
	if (A == 1 || B == 1) {
		cout << A * B << flush;
	}
	else {
		map<int, int> Afact;
		for (int loop = 2; loop * loop <= A; loop++) {
			if (A % loop == 0) {
				A /= loop;
				Afact[loop]++;
				loop--;
				if (A == 1) break;
			}
		}
		if (A > 1) Afact[A]++;
		map<int, int> Bfact;
		for (int loop = 2; loop * loop <= B; loop++) {
			if (B % loop == 0) {
				B /= loop;
				Bfact[loop]++;
				loop--;
				if (B == 1) break;
			}
		}
		if (B > 1) Bfact[B]++;

		map<int, int> LCMfact;
		for (auto it = Afact.begin(); it != Afact.end(); it++) LCMfact[it->first] = it->second;
		for (auto it = Bfact.begin(); it != Bfact.end(); it++) LCMfact[it->first] = max(LCMfact[it->first], it->second);
		
		long long LCM = 1;
		for (auto it = LCMfact.begin(); it != LCMfact.end(); it++) LCM *= (long long)pow(it->first, it->second);
		
		cout << LCM << flush;
	}
	*/

	if (A < B) swap(A, B);
	for (int loop = 1; loop <= B; loop++) {
		if ((A * loop) % B == 0) {
			cout << A * loop << flush;
			return;
		}
	}

	return;
}

void D_Brick_Break(void) {

	int N;
	cin >> N;
	vector<int> A(N);
	for (int& it : A) cin >> it;

	int flag = 0;
	int counter = 0;
	for (int loop = 1; flag < N; loop++) {
		if (A[flag] != loop) {
			loop--;
			counter++;
		}
		flag++;
	}
	cout << ((counter == N) ? -1 : counter) << flush;
	return;
}

void E_Double_Factorial(void) {

	long long N;
	cin >> N;

	if (N % 2 == 0) {
		long long re = 0;
		for (int loop = 0; 10 * (long long)pow(5, loop) <= N; loop++) {
			re += (long long)(N / (10 * (long long)pow(5, loop)));
		}
		cout << re << flush;
	}
	else {
		cout << 0 << flush;
	}
	return;
}

int main(void) {

	//A_Round_One();
	//B_Strings_with_the_Same_Length();
	//C_Snack();
	//D_Brick_Break();
	E_Double_Factorial();
	return 0;
}
