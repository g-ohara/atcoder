/*
A,B,Cは合わせて20分程度で正解。
Dは開発環境のほうではコンパイルを通ったが、提出するとコンパイルエラーが発生して手間取った。
インクルードファイルの表記をmath.hからcmathに変更すると解決した。
理由はよく分からないが、表記を右の形式に統一するほうがよさそうだ。
Eはナップザック問題に似た「NP困難」な問題であるようで、全幅探索するしかないらしい。
動的計画法をしっかりと勉強しておく必要がある。
*/
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void A_Serval_vs_Monster(void) {

	int H, A;
	cin >> H >> A;

	cout << ((H % A == 0) ? H / A : int(H / A) + 1);
	return;
}

void B_Common_Raccoon_vs_Monster(void) {

	int H, N;
	cin >> H >> N;

	//int sum = 0;
	
	int A;
	for (int loop = 0; loop < N; loop++) {
		cin >> A;
		//sum += A;
		H -= A;
	}

	//cout << ((sum >= H) ? "Yes" : "No") << flush;
	cout << ((H <= 0) ? "Yes" : "No");
	return;
}

void C_Fennec_vs_Monster(void) {

	int N, K;
	cin >> N >> K;

	vector<int> H(N);
	for (int& it : H) cin >> it;
	sort(H.begin(), H.end());

	long long sum = 0;
	for (int loop = 0; loop < N - K; loop++) sum += H[loop];

	cout << sum << flush;
	return;
}

void D_Caracal_vs_Monster(void) {

	long H;
	cin >> H;

	for (int loop = 0; loop < 50; loop++) {

		if (H == 1) {
			cout << long(std::pow(2, loop + 1) - 1);
			return;
		}

		H = long(H / 2);
	}
	return;
}

/*
struct Magic {
	int A = 0;
	int B = 0;
	double rate = 0;
};
bool comp(const struct Magic& a, const struct Magic& b) { 
	if (a.rate > b.rate) return true;
	else if (a.rate < b.rate) return false;
	else return (a.A < b.A);
}
void E_Crested_Ibis_vs_Monster(void) {

	int H, N;
	cin >> H >> N;

	vector<struct Magic> magic(N);
	for (struct Magic& it :magic) {
		cin >> it.A >> it.B;
		it.rate = (double)it.A / (double)it.B;
	}
	sort(magic.begin(), magic.end(), comp);

	int req = 0;
	for (int loop = 0; loop < N; loop++) {

		int num = int(H / magic[loop].A);
		if (num == 0) num = 1;
		H -= magic[loop].A * num;
		req += magic[loop].B * num;

		if (H <= 0) break;
	}

	cout << req;
	return;
}
*/
struct Magic {
	int A = 0;
	int B = 0;
};
bool comp(const struct Magic& a, const struct Magic& b) {
	return (a.A > b.A);
}
void E_Crested_Ibis_vs_Monster(void) {

	int H, N;
	cin >> H >> N;

	vector<struct Magic> magic(N);
	for (struct Magic& it :magic) {
		cin >> it.A >> it.B;
	}
	sort(magic.begin(), magic.end(), comp);

	vector<int> DP(H + magic[0].A);
	for (int i = 0; i < DP.size(); i++) {


	}
}

int main(void) {

	//A_Serval_vs_Monster();
	//B_Common_Raccoon_vs_Monster();
	//C_Fennec_vs_Monster();
	//D_Caracal_vs_Monster();
	E_Crested_Ibis_vs_Monster();
	return 0;
}
