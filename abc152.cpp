/*
ABC #152 (2020.03.11)
A,B,C,Dは合わせて1時間弱で正解した。
Eは解説の通りの方針であったが、どうも処理時間が長くなってしまう。
素因数分解に時間がかかっているかもしれない。
素因数分解のライブラリを作っておいてもよいだろう。
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void A_AC_or_WA(void) {

	int N, M;
	cin >> N >> M;

	cout << ((N == M) ? "Yes" : "No") << flush;
	return;
}

void B_Comparing_Strings(void) {

	int a, b;
	cin >> a >> b;

	for (int loop = 0; loop < max(a, b); loop++) cout << min(a, b);
	cout << flush;
	return;
}

void C_Low_Elements(void) {

	int N;
	cin >> N;

	vector<int> P(N);
	for (int& it : P) cin >> it;

	int PMin = P[0];
	int counter = 0;
	for (int it : P) {
		if (it <= PMin) {
			counter++;
			PMin = it;
		}
	}

	cout << counter << flush;
	return;
}

void D_Handstand2(void) {

	int N;
	cin >> N;

	int num[10][10] = { 0 };
	int length = 0;
	for (int loop = 1; loop <= N; loop++) {

		if (loop == (int)pow(10, length)) length++;
		num[int(loop / pow(10, length - 1))][loop % 10]++;
	}
	
	int counter = 0;
	for (int loop1 = 1; loop1 <= 9; loop1++) {
		for (int loop2 = 1; loop2 <= 9; loop2++) {
			counter += num[loop1][loop2] * num[loop2][loop1];
		}
	}

	cout << counter << flush;
	return;
}

void E_Flatten(void) {

	int N;
	cin >> N;

	struct Num {
		int A = 0;
		map<int, int> factor;
	};
	vector<struct Num> A(N);
	for (struct Num& it : A) {
		cin >> it.A;
		int num = it.A;
		for (int loop = 2; num > 1 && loop <= (int)pow(it.A, 0.5); loop++) {
			if (num % loop == 0) {
				num /= loop;
				it.factor[loop]++;
				loop--;
			}
		}
		if (num == it.A) it.factor[it.A] = 1;
	}

	map<int, int> ABfact;
	for (struct Num& it1 :A) {
		for (auto loop = it1.factor.begin(); loop != it1.factor.end(); loop++) {
			ABfact[loop->first] = max(loop->second, ABfact[loop->first]);
		}
	}

	long long sum = 0;
	for (struct Num& it : A) {
		long long B = 1;
		for (auto loop = ABfact.begin(); loop != ABfact.end(); loop++) {
			if (loop->second > it.factor[loop->first]) {
				B = (B * (int)pow(loop->first, loop->second - it.factor[loop->first])) % 1000000007;
			}
		}
		sum = (sum + B) % 1000000007;
	}

	cout << sum << flush;
	return;
}

int main(void) {

	//A_AC_or_WA();
	//B_Comparing_Strings();
	//C_Low_Elements();
	//D_Handstand2();
	E_Flatten();
	return 0;
}
