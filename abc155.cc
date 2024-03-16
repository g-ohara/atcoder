/*
ABC #155　(2020.03.05)
A,B,Cは40分程度で完成した。
ここ最近はA,B,Cは簡単に解けるようになってきたが、Dで躓く。
また、Cにおいては連想配列なるもの（知らなかった）を用いることもできるようだ。
このような辞書問題（特に入力が重複するもの）では検討の価値がありそう。
Dにおいても方針は解説と概ね同じだったが、実装が難しい。
こればかりは慣れる外無い。
*/

#include <algorithm>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void A_Poor(void) {

	int num[3];
	cin >> num[0] >> num[1] >> num[2];
	
	int counter = 0;
	for (int loop1 = 0; loop1 < 3; loop1++) {
		for (int loop2 = loop1 + 1; loop2 < 3; loop2++) {

			if (num[loop1] == num[loop2]) counter++;
		}
	}

	cout << ((counter == 1) ? "Yes" : "No") << flush;
	return;
}

void B_Papers_Please(void) {

	int N;
	cin >> N;

	int A;
	for (int loop = 0; loop < N; loop++) {
		cin >> A;
		if (A % 2 == 0 && A % 3 > 0 && A % 5 > 0) {
			cout << "DENIED";
			return;
		}
	}

	cout << "APPROVED";
	return;
}

void C_Poll(void) {

	int N;
	cin >> N;

	map<string, int> dict;
	string S = "";
	int maxNum = 0;
	for (int loop = 0; loop < N; loop++) {
		cin >> S;
		dict[S] += 1;
		maxNum = max(maxNum, dict[S]);
	}

	for (auto loop : dict) {
		if (loop.second == maxNum)	cout << loop.first << endl;
	}
	return;

	/*
	vector<string> S(N);
	for (int loop = 0; loop < N; loop++) {
		cin >> S[loop];
	}
	sort(S.begin(), S.end());
	
	int maxNum = 0;
	int counter = 0;
	for (int loop = 0; loop < N; loop++) {

		if (loop == 0 || S[loop].compare(S[loop - 1]) == 0) {

			counter++;
		}
		else {

			counter = 1;
		}

		maxNum = max(counter, maxNum);
	}

	counter = 0;
	for (int loop = 0; loop < N; loop++) {

		if (loop == 0 || S[loop].compare(S[loop - 1]) == 0) {

			counter++;
		}
		else {

			counter = 1;
		}

		if (counter == maxNum) cout << S[loop] << endl;
	}
	return;
	*/
}

void D_Pairs(void) {

	int N, K;
	cin >> N >> K;

	vector<int> A(N);
	for (int& loop : A)	cin >> loop;
	sort(A.begin(), A.end());

	int pos = 0;
	int neg = 0;
	int zero = 0;
	for (int loop : A) {
		if (loop < 0)		neg++;
		else if(loop == 0)	zero++;
		else				pos++;
	}

	long pro1;
	long pro2;

	if (K <= neg * pos) {

		int loop1 = 0;
		int loop2 = N - 1;

		for (int flag = 0;; flag++) {

			pro1 = A[loop1 + 1] * A[loop2];
			pro2 = A[loop1] * A[loop2 - 1];

			if (pro1 < pro2)	loop1++;
			else				loop2--;

			if (flag == K - 2) {
				cout << min(pro1, pro2) << flush;
				return;
			}
		}
	}
	else {

		for (int& loop : A) {
			if (loop < 0)	loop = -loop;
			else			break;
		}
		sort(A.begin(), A.end());

		int loop1 = 0;
		int loop2 = 1;
		for (int flag = neg * pos; loop1 < loop2 && loop2 < N; flag++) {

			if (flag == K - 1) {
				cout << A[loop1] * A[loop2] << flush;
				return;
			}

			pro1 = A[loop1 + 1] * A[loop2];
			pro2 = A[loop1] * A[(loop2 < N - 1) ? loop2 + 1 : loop2];

			if (loop1 + 1 == loop2) {

				loop2++;
			}
			else {

				if (pro1 < pro2)	loop1++;
				else				loop2++;
			}
		}
	}
}

void E_Payment(void) {

	string N;
	cin >> N;
}

int main(void) {

	//A_Poor();
	//B_Papers_Please();
	//C_Poll();
	D_Pairs();
	return 0;
}
