/*
ABC #145 (2020.03.31 バーチャル参加)
AからDはサクサクと解けた。
特にDは、あらかじめ用意していた二項係数計算のアルゴリズムを初めて使うことができて嬉しい。
Eでも、初めて自力で動的計画法を実装することができた。
成長を感じる。
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

void A_Circle(void) {

	int r; cin >> r;
	cout << r * r << flush;
	return;
}

void B_Echo(void) {

	int N; string S; cin >> N >> S;

	cout << ((N % 2 == 0 && S.substr(0, N / 2) == S.substr(N / 2, N / 2)) ? "Yes" : "No") << flush;
	return;
}

void C_Average_Length(void) {

	int N; cin >> N;
	struct Town { int x, y; };
	vector<struct Town> town(N);
	for (struct Town& here :town) cin >> here.x >> here.y;

	vector<int> perm(N);
	double length = 0;
	int counter = 0;
	for (int loop = 0; loop < N; loop++) perm[loop] = loop;
	do {
		for (int loop = 1; loop < N; loop++) {
			length += pow(pow(town[perm[loop]].x - town[perm[loop - 1]].x, 2) + pow(town[perm[loop]].y - town[perm[loop - 1]].y, 2), 0.50);
		}
		counter++;
	} while (next_permutation(perm.begin(), perm.end()));
	cout << setprecision(20) << length / counter << flush;
	return;
}

void D_Knight(void) {

	int X, Y; cin >> X >> Y;
	if ((X + Y) % 3 == 0 && X <= Y * 2 && X * 2 >= Y) {
		class Combination1 com((X + Y) / 3);
		cout << com.calculate((X + Y) / 3, X - (X + Y) / 3) << flush;
	}
	else {
		cout << 0 << flush;
	}
	return;
}

void E_All_you_can_eat(void) {

	int N, T; cin >> N >> T;
	struct Dish { int cost, taste; };
	vector<struct Dish> dish(N);
	for (struct Dish& it :dish) cin >> it.cost >> it.taste;

	struct DP {
		int value = 0;
		vector<bool> eaten;
	};
	vector<struct DP> dp(T);
	for (int time = 0; time < T; time++) {
		for (int loop = 0; loop < N; loop++) dp[time].eaten.push_back(false);
		if (dish[0].cost <= time) {
			dp[time].value = dish[0].taste;
			dp[time].eaten[0] = true;
		}
	}
	for (int index = 1; index < N; index++) {
		for (int time = T - 1; time > 0; time--) {
			if (dish[index].cost <= time) {
				if (dp[time].value <= dp[time - dish[index].cost].value + dish[index].taste) {
					dp[time].value = dp[time - dish[index].cost].value + dish[index].taste;
					dp[time].eaten = dp[time - dish[index].cost].eaten;
					dp[time].eaten[index] = true;
				}
			}
		}
	}

	int lastDish = 0;
	for (int index = 0; index < N;index++) {
		if (!dp[T - 1].eaten[index]) lastDish = max(lastDish, dish[index].taste);
	}
	cout << dp[T - 1].value + lastDish << flush;
	return;
}

int main(void) {
	
	//A_Circle();
	//B_Echo();
	//C_Average_Length();
	//D_Knight();
	E_All_you_can_eat();
	return 0;
}
