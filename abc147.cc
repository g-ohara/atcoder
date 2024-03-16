/*
ABC #147 (2020.03.18 バーチャル参加)

ほかの回に比べて難易度が高いように思われる。
A,Bは合わせて10分程度で正解したが、Cに苦戦した。
組合せを列挙するクラスを何とか完成させたが、制限時間中にはできなかった。
これは今後使用する場面も多そうだから、大切にとっておくことにしよう。
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

void A_Black_Jack(void) {
	
	int A1, A2, A3;
	cin >> A1 >> A2 >> A3;
	
	cout << ((A1 + A2 + A3 >= 22) ? "bust" : "win") << flush;
	return;
}

void B_Palindrome_philia(void) {

	string S;
	cin >> S;

	int hug = 0;
	for (int loop = 0; (loop + 1) * 2 <= (int)S.size(); loop++) {
		if (S[loop] != S[S.size() - 1 - loop]) hug++;
	}

	cout << hug << flush;
	return;
}

void C_HonestOrUnkind2(void) {

	int N;
	cin >> N;
	struct Evidence {
		int x;
		bool y;
	};
	struct Person {
		bool honesty = false;
		vector<struct Evidence> evidence;
	};
	vector<struct Person> person(N);
	for (struct Person& he :person) {
		int A;
		cin >> A;
		for (int loop = 0; loop < A; loop++) {
			struct Evidence buff;
			int x, y;
			cin >> x >> y;
			buff.x = x - 1;
			buff.y = (bool)y;
			he.evidence.push_back(buff);
		}
	}

	for (int re = N; re > 0; re--) {
		class Combination2 comb(N, re);
		do {
			for (struct Person& he :person) he.honesty = false;
			for (int index : comb.sequence) person[index].honesty = true;
			for (struct Person witness :person) {
				for (struct Evidence fact :witness.evidence) {
					if (witness.honesty && person[fact.x].honesty != fact.y) goto nextComb;
				}
			}
			cout << re << flush;
			return;
		nextComb:
			continue;
		} while (comb.next_combination());
	}
	cout << 0 << flush;
	return;
}

int main(void) {

	//A_Black_Jack();
	//B_Palindrome_philia();
	C_HonestOrUnkind2();
	return 0;
}
