/*
ABC #149 (2020.03.15)
AÅ`DÇÕçáÇÌÇπÇƒ40ï™íˆìxÇ≈ê≥âÅB
EÇÕâê‡ÇÃà”ñ°Ç™Ç¢Ç‹Ç¢Çøï™Ç©ÇÁÇ»Ç¢ÅB
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
	return (memo[n].fact * (memo[k].fact_inv * memo[n - k].fact_inv) % m_module) % m_module;
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

void A_Strings(void) {

	string S, T;
	cin >> S >> T;
	cout << T << S << flush;
	return;
}

void B_Greedy_Takahashi(void) {

	long long A, B, K;
	cin >> A >> B >> K;

	if (K < A)			cout << A - K << " " << flush;
	else if (K < A + B) cout << "0 " << A + B - K << flush;
	else				cout << "0 0" << flush;
	return;
}

void C_Next_Prime(void) {
	
	int X;
	cin >> X;

	for (int sample = X; sample < INT_MAX; sample++) {
		for (int loop = 2; loop * loop < sample; loop++) {
			if (sample % loop == 0) goto nextSample;
		}
		cout << sample << flush;
		return;
	nextSample:
		continue;
	}
	return;
}

void D_Prediction_and_Restriction(void) {

	int N, K;
	int point[3];
	cin >> N >> K >> point[0] >> point[1] >> point[2];
	vector<int> T(N);
	for (int& it : T) {
		char C;
		cin >> C;
		switch (C) {
		case 'r':
			it = 2;
			break;
		case 's':
			it = 0;
			break;
		case 'p':
			it = 1;
			break;
		}
	}

	int sum = 0;
	for (int rem = 0; rem < K; rem++) {
		for (int loop = K + rem; loop < N; loop += K) {
			if (T[loop - K] == T[loop]) T[loop] = -1;
			else						sum += T[loop];
		}
	}
	
	cout << sum << flush;
	return;
}

void E_Handshake(void) {

	int N;
	long long M;
	cin >> N >> M;

	vector<int> A(N);
	for (int& it : A)cin >> it;
	sort(A.begin(), A.end(), greater<int>());

	vector<long long> num(A[0] * 2 + 1);

	for (int loop1 = 0; loop1 < N; loop1++) {
		for (int loop2 = loop1; loop2 < N; loop2++) {
			if (loop1 == loop2) num[A[loop1] + A[loop2]]++;
			else				num[A[loop1] + A[loop2]] += 2;
		}
	}

	long long index = 0;
	long long sum = 0;
	for (int loop = A[0] * 2; loop >= 0; loop--) {

		if (num[loop] >= M - index) {
			sum += loop * (M - index);
			break;
		}
		else {
			sum += loop * num[loop];
			index += num[loop];
		}
	}

	/*
	long long flag = 0;
	vector<int> point((long long)N * (long long)N);
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			point[flag] = A[x] + A[y];
			flag++;
		}
	}
	sort(point.begin(), point.end(), greater<int>());
	*/
	/*
	int x = 0;
	int y = 0;
	long long flag = 0;
	long long sum = 0;
	while (flag < M) {

		if (x < y && flag < M - 1) {
			sum += (A[x] + A[y]) * 2;
			flag += 2;
		}
		else {
			sum += A[x] + A[y];
			flag++;
		}

		if (x > 0 && y < N - 1 && A[x - 1] + A[y + 1] > A[x + 1] + A[y]) {
			x--;
			y++;
		}
		else if (y < N - 1 && (A[x] + A[y + 1] > A[x + 1] + A[y] || x == y)) {
			y++;
		}
		else if (x < N - 1) {
			x++;
		}
	}
	*/
	cout << sum << flush;
	return;
}

int main(void) {

	//A_Strings();
	//B_Greedy_Takahashi();
	//C_Next_Prime();
	//D_Prediction_and_Restriction();
	E_Handshake();
	return 0;
}
