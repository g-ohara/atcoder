/*
ABC #142 (2020.04.03 バーチャル参加)
全体的に非常によくできた。
Eの動的計画法もかなりスムーズに実装できた。
Dではあらかじめ用意していた素因数分解のアルゴリズムに不備があったが、今回無事に修復した。
Fは有向グラフなど意味の分からない用語が乱発されて歯が立たず。勉強不足。
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

void A_Odds_of_Oddness(void) {

	int N; cin >> N;
	
	cout << setprecision(20) << (double)((N + N % 2) / 2) / (double)N << flush;
	return;
}

void B_Roller_Coaster(void) {

	int N, K; cin >> N >> K;
	vector<int>h(N); for (int& it : h) cin >> it;

	sort(h.begin(), h.end());
	for (int index = 0; index < N; index++) {
		if (h[index] >= K) {
			cout << N - index << flush;
			return;
		}
	}
	cout << 0 << flush;
	return;
}

void C_Go_to_School(void) {

	int N; cin >> N;
	struct Student {
		int index;
		int A;
		bool operator<(const Student& right) { return (A < right.A); }
	};
	vector<Student>student(N); 
	for (int index = 0; index < N;index++) {
		student[index].index = index + 1;
		cin >> student[index].A;
	}

	sort(student.begin(), student.end());
	
	for (Student he : student) cout << he.index << " ";
	cout << flush;
	return;
}

void D_Disjoint_Set_of_Common_Divisors(void) {

	long long A, B; cin >> A >> B;
	
	map<long long, int>AMap, BMap;
	AMap = factorization(A);
	BMap = factorization(B);
	long long counter = 0;
	for (auto loop = AMap.begin(); loop != AMap.end(); loop++) {
		if (BMap[loop->first] > 0) counter++;
	}

	cout << counter + 1 << flush;
	return;
}

void E_Get_Everything(void) {
	
	int N, M; cin >> N >> M;
	struct Key { int price = 0; int canOpen = 0; };
	vector<Key> key(M);
	for (struct Key& it :key) {
		cin >> it.price;
		int b; cin >> b;
		for (int loop = 0; loop < b; loop++) {
			int c; cin >> c;
			it.canOpen += (int)pow(2, c - 1);
		}
	}

	vector<int> dp((int)pow(2, N));
	dp[0] = 0;
	for (int opened = 1; opened < (int)dp.size(); opened++) {
		if ((opened & key[0].canOpen) == opened)	dp[opened] = key[0].price;
		else										dp[opened] = -1;
	}
	for (int index = 1; index < M; index++) {
		for (int opened = (int)dp.size() - 1; opened > 0; opened--) {
			int target = (opened & ~key[index].canOpen);
			if (dp[target] != -1) {
				if (dp[opened] == -1)	dp[opened] = dp[target] + key[index].price;
				else					dp[opened] = min(dp[opened], dp[target] + key[index].price);
			}
		}
	}

	cout << dp[dp.size() - 1] << flush;
	return;
}

int main(void) {

	//A_Odds_of_Oddness();
	//B_Roller_Coaster();
	//C_Go_to_School();
	D_Disjoint_Set_of_Common_Divisors();
	//E_Get_Everything();
	return 0;
}
