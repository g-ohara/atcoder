/*
ABC #154
A,B,Cは正解。
A,Bは合わせて10分程度で完成したが、C,Dで詰まった。
Cでは、出力する文字列の大文字小文字を間違えていた。
こういう凡ミスは本質的ではないが気を付けたい。
Dは、解説を一読しただけではミスの在処が判然としない。
入力の桁数が大きいときに不正解になるようだが、原因は不明。
*/

#include <algorithm>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void A_Remaining_Balls(void) {

	/*
	string S, T;
	cin >> S >> T;

	int A, B;
	cin >> A >> B;

	string U;
	cin >> U;
	*/

	string S, T, U;
	int A, B;
	cin >> S >> T >> A >> B >> U;

	if (S.compare(U) == 0)	A--;
	else					B--;

	cout << A << " " << B << flush;
	return;
}

void B_I_Miss_You(void) {

	string S;
	cin >> S;

	/*
	for (int loop = 0; loop < S.size(); loop++) cout << "x";
	cout << flush;
	*/
	cout << 'x' * S.size() << flush;
	return;
}

void C_Distinct_or_Not(void) {

	int N;
	cin >> N;

	vector<int> A(N);
	for (int& loop : A) cin >> loop;
	sort(A.begin(), A.end());

	for (int loop1 = 0; loop1 < N - 1; loop1++) {
		if (A[loop1] == A[loop1 + (int)1]) {
			cout << "NO" << flush;
			return;
		}
	}
	cout << "YES" << flush;
	return;
}

void D_Dice_in_Line(void) {

	int N, K;
	cin >> N >> K;

	vector<int> p(N);
	for (int& it : p) cin >> it;

	int sum = 0;
	for (int loop = 0; loop < K; loop++) sum += p[loop];

	int sumMax = sum;
	for (int loop = 0; loop < N - K; loop++) {
		sum -= p[loop];
		sum += p[(loop + K)];
		sumMax = max(sum, sumMax);
	}
	double re = ((double)sumMax + (double)K) * 0.50;
	cout << re << flush;
	return;
}

void E_Almost_Everywhere_Zero(void) {

	string N;
	cin >> N;
	int K;
	cin >> K;

	int re = 0;
	int length = (int)N.size();
	if (length > K) {

		switch (K) {
		case 1:
			re = length - 1;
			break;
		case 2:
			re = (length - 1) * (length - 2) / 2;
			break;
		case 3:
			re = length * (length - 1) * (length - 2);
			break;
		}
	}
	else {

		cout << 0 << flush;
		return;
	}
}

int main(void) {

	//A_Remaining_Balls();
	//B_I_Miss_You();
	//C_Distinct_or_Not();
	D_Dice_in_Line();
	return 0;
}
