/*
ABC #144 (2020.04.01 バーチャル参加)
少し難易度が高かったようだ。
Dは紙とペンでの数学的な考察が作業のほとんどを占めた。
Eは所要時間が最大のメンバーを逐一探索するのでは時間がかかりすぎる。
解説によれば、「最大所要時間がx以下である」として計算し、xの値を二分探索するのが良いようだ。
このように処理時間が鍵となる問題では、二分探索は有効に働きそうだ。
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

void A_9x9(void) {

	int A, B; cin >> A >> B;
	
	if (A > 9 || B > 9) cout << -1 << flush;
	else				cout << A * B << flush;
	return;
}

void B_81(void) {

	int N; cin >> N;

	for (int loop = 9; loop > 0; loop--) {
		if (N % loop == 0) {
			N /= loop;
			break;
		}
	}
	cout << ((N <= 9) ? "Yes" : "No") << flush;
	return;
}

void C_Walk_on_Multiplication_Table(void) {

	long long N; cin >> N;
	int center = (int)pow(N, 0.5);

	for (int loop = center; loop > 0; loop--) {
		if (N % loop == 0) {
			cout << loop + N / loop - 2 << flush;
			return;
		}
	}
	for (int loop = center; loop <= N; loop++) {
		if (N % loop == 0) {
			cout << loop + N / loop - 2 << flush;
			return;
		}
	}
	return;
}

void D_Water_Bottle(void) {

	double a, b, x; cin >> a >> b >> x;

	const double PI = 3.14159265358979;
	if (x > a * a * b / 2)	cout << setprecision(20) << atan(2 * (a * a * b - x) / (a * a * a)) * 180 / PI << flush;
	else					cout << setprecision(20) << atan(a * b * b / (x * 2)) * 180 / PI << flush;
	return;
}

void E_Gluttony(void) {

	int N; long long K; cin >> N >> K;
	vector<int> A(N), F(N);
	for (int& it : A) cin >> it;
	for (int& it : F) cin >> it;

	sort(A.begin(), A.end());
	sort(F.begin(), F.end(), greater<int>());
	vector<long long> time(N);
	for (int index = 0; index < N; index++) time[index] = (long long)A[index] * (long long)F[index];
	/*
	for (long long loop = 0; loop < K; loop++) {
		int maxIndex = distance(time.begin(), max_element(time.begin(), time.end()));
		if (A[maxIndex] == 0)	break;
		else					time[maxIndex] -= (long long)F[maxIndex];
	}
	*/
	if (accumulate(A.begin(), A.end(), 0LL) > K) {
		long long start = 0;
		long long end = *max_element(time.begin(), time.end()) + 1;
		while (1) {
			long long x = (start + end) / 2;
			long long counter = 0;
			for (int index = 0; index < N; index++) {
				if (time[index] > x) counter += (long long)ceil(double(time[index] - x) / (double)F[index]);
			}
			if (counter > K)	start = x;
			else				end = x;
			if (start + 1 == end) break;
		}
		cout << end << flush;
	}
	else {
		cout << 0 << flush;
	}
	return;
}

int main(void) {

	//A_9x9();
	//B_81();
	//C_Walk_on_Multiplication_Table();
	//D_Water_Bottle();
	E_Gluttony();
	return 0;
}
