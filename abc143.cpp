/*
ABC #143 (2020.04.02 バーチャル参加)
Bは、数学的な工夫で必要以上に計算量を抑えられた。
Dは、自力で二分探索を実装して制限時間に収められた。
Eはまるで歯が立たない。
木探索のデータ構造やアルゴリズムを勉強しなくてはならない。
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

void A_Curtain(void) {

	int A, B; cin >> A >> B;
	
	cout << max(A - B * 2, 0) << flush;
	return;
}

void B_TAKOYAKI_FESTIVAL(void) {

	int N; cin >> N;
	vector<int> d(N); for (int& it : d)cin >> it;

	int sum = (int)pow(accumulate(d.begin(), d.end(), 0), 2);
	for (int it : d) sum -= it * it;
	sum /= 2;

	cout << sum << flush;
	return;
}

void C_Slimes(void) {

	int N; cin >> N;
	string S; cin >> S;
	
	/*
	int counter = 1;
	for (int index = 1; index < N; index++) {
		if (S[index] != S[index - 1]) counter++;
	}

	cout << counter << flush;
	return;
	*/
	
	S.erase(unique(S.begin(), S.end()), S.end());
	
	cout << S.size() << flush;
	return;
}

void D_Triangles(void) {

	int N; cin >> N;
	vector<int> L(N); for (int& it : L)cin >> it;
	sort(L.begin(), L.end());

	/*
	int counter = 0;
	class Combination2 com(N, 3);
	do {
		if (L[com.sequence[0]] + L[com.sequence[1]] > L[com.sequence[2]]) counter++;
	} while (com.next_combination());
	*/

	long long counter = 0;
	for (int a = 0; a < N - 1; a++) {
		for (int b = a + 1; b < N - 1; b++) {
			int start = b, end = N;
			if (L[a] + L[b] > L[b + 1]) {
				while (1) {
					int c = (start + end) / 2;
					if (L[a] + L[b] > L[c]) start = c;
					else					end = c;
					if (start + 1 == end) break;
				}
				counter += (start - b);
			}
		}
	}
	cout << counter << flush;
	return;
}

struct Next_town {
	int num;
	int distance;
	bool operator<(const struct Next_town right)const { return num < right.num; }
};
struct Town {
	int value;
	vector<struct Next_town> next_town;
};
vector<struct Town> town;
int calculate(int num, int goal, map<int, int>& visited) {
	int dstMin = -1;
	for (struct Next_town& here : town[num].next_town) {
		if (here.num == goal) {
			return 0;
		}
		else if (visited[here.num] == 0) {
			visited[here.num]++;
			dstMin = (dstMin == -1) ? calculate(here.num, goal, visited) : min(dstMin, calculate(here.num, goal, visited));
		}
	}
	return dstMin;
}
void E_Travel_by_Car(void) {

	int N, M, L; cin >> N >> M >> L;
	town.resize(N);
	for (int loop = 0; loop < M; loop++) {
		int A, B, C; cin >> A >> B >> C;
		town[A - 1].next_town.push_back({ B - 1,C });
		town[B - 1].next_town.push_back({ A - 1,C });
	}
	for (struct Town& it :town) sort(it.next_town.begin(), it.next_town.end());
	int Q; cin >> Q;
	vector<int>s(Q), t(Q); for (int index = 0; index < Q; index++)cin >> s[index] >> t[index];

	for (int loop = 0; loop < Q; loop++) {
		map<int, int> visited;
		cout << calculate(s[loop] - 1, t[loop] - 1, visited) << endl;
	}
	return;
}

int main(void) {

	//A_Curtain();
	//B_TAKOYAKI_FESTIVAL();
	//C_Slimes();
	//D_Triangles();
	E_Travel_by_Car();
	return 0;
}
