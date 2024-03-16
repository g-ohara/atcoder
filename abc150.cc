/*
ABC #150 (2020.03.14)
A,B,C,Dはよし。
Eについては、二項係数の計算がボトルネックになる。
二項係数の計算のプログラムをあらかじめ作っておきたい。
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Memo {
	int fact = 0;
	int fact_inv = 0;
	int inv = 0;
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
	return (memo[n].fact * memo[k].fact_inv * memo[n - k].fact_inv) % m_module;
}
Combination::Combination(int memo_max, int module = 1000000007) {
	m_module = module;
	memo.push_back({ 1,1,0 });
	memo.push_back({ 1,1,1 });
	for (int loop = 2; loop <= memo_max; loop++) {
		struct Memo temp;
		temp.fact = (memo[loop - 1].fact * loop) % m_module;
		temp.inv = m_module - memo[m_module % loop].inv * int(m_module / loop) % m_module;
		temp.fact_inv = (memo[loop - 1].fact_inv * temp.inv) % m_module;
		memo.push_back(temp);
	}
}

void A_500_Yen_Coins(void) {

	int K, X;
	cin >> K >> X;
	cout << ((500 * K >= X) ? "Yes" : "No") << flush;
	return;
}

void B_Count_ABC(void) {

	int N;
	string S;
	cin >> N >> S;

	int counter = 0;
	for (int loop = 0; loop < N - 2; loop++) {
		if (S[loop] == 'A' && S[loop + 1] == 'B' && S[loop + 2] == 'C') counter++;
	}
		
	cout << counter << flush;
	return;
}

void C_Count_Order(void) {

	int N;
	cin >> N;
	vector<int> P(N);
	for (int& it : P) cin >> it;
	vector<int> Q(N);
	for (int& it : Q) cin >> it;

	vector<int> sample(N);
	int index = 0;
	int a = 0;
	int b = 0;
	for (int loop = 0; loop < N; loop++) sample[loop] = loop + 1;
	do {
		if (P == sample) a = index;
		if (Q == sample) b = index;
		index++;
	} while (next_permutation(sample.begin(), sample.end()));

	cout << abs(a - b) << flush;
	return;
}

void D_Semi_Common_Multiple(void) {

	int N, M;
	cin >> N >> M;
	vector<int> a(N);
	for (int& it : a) {
		cin >> it;
		it /= 2;
	}
	sort(a.begin(), a.end());
	
	int Xmin = 0;
	for (int X = a[N - 1]; X <= M; X += a[N - 1]) {
		for (int& it : a) {
			if (!(X % it == 0 && X / it % 2 == 1)) goto nextSample;
		}
		Xmin = X;
		break;
	nextSample:
		continue;
	}

	cout << ((Xmin == 0) ? 0 : int((M + Xmin) / (Xmin * 2))) << flush;
	return;
}

void E_Chenge_a_Little_Bit(void) {

	int N;
	cin >> N;
	vector<int> C(N);
	for (int& it : C) cin >> it;
	sort(C.begin(), C.end());

	class Combination com(N);

	long long re = 0;
	for (int k = 1; k <= N; k++) {
		long long sum = 0;
		for (int loop = 1; loop <= k; loop++) {
			sum = (sum + (k - loop + 1) * C[loop - 1]) % 1000000007;
		}
		re = (re + com.calculate(N, k) * sum) % 1000000007;
	}
	for (int loop = 0; loop < N; loop++) re = (re * 2) % 1000000007;

	cout << re << flush;
	return;
}

int main(void) {

	//A_500_Yen_Coins();
	//B_Count_ABC();
	//C_Count_Order();
	//D_Semi_Common_Multiple();
	E_Chenge_a_Little_Bit();
	return 0;
}
