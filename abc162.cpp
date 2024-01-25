#include "bits/stdc++.h"

using namespace std;

#define rep(loop, N) for (int loop = 0; loop < N; loop++)

struct Node {
	Node* parent = NULL;
	vector<Node*> child;
	long long value = 0;
};
struct Edge {
	int parent = 0;
	int child = 0;
	bool operator <(const Edge& right) const { return parent < right.parent; }
};
struct Tree {
	vector<Node> node;
	Tree(int, vector<Edge>);
};
Tree::Tree(int nodeNum, vector<Edge> edge) {
	node.resize(nodeNum);
	for (Edge& it : edge) {
		node[it.child].parent = &node[it.parent];
		node[it.parent].child.push_back(&node[it.child]);
	}
}

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
long long gcd(long long num1, long long num2) {
	return num2 == 0 ? num1 : gcd(num2, num1 % num2);
}

struct Memo {
	long long fact = 0;
	long long fact_inv = 0;
	long long inv = 0;
};
class Combination1 {
private:
	long long m_module = 1000000007;
	vector<struct Memo> memo;
public:
	long long calculate(int, int);
	Combination1(int, long long);
};
long long Combination1::calculate(int n, int k) {
	return ((memo[n].fact * memo[k].fact_inv) % m_module * memo[n - k].fact_inv) % m_module;
}
Combination1::Combination1(int memo_max, long long module = 1000000007) {
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

void A_Lucky_7(void) {

	string N; cin >> N;

	rep(index, 3) {
		if (N[index] == '7') {
			cout << "Yes" << endl;
			return;
		}
	}
	cout << "No" << endl;
	return;
}

void B_FizzBuzz_Sum(void) {

	int N; cin >> N;

	long long sum = 0;
	for (int num = 1; num <= N; num++) {
		if (num % 3 != 0 && num % 5 != 0) sum += num;
	}

	cout << sum << endl;
	return;
}

void C_Sum_of_gcd_of_Tuples_Easy(void) {

	int K; cin >> K;

	int sum = 0;
	for (int a = 1; a <= K; a++) {
		for (int b = 1; b <= K; b++) {
			int gcd1 = (int)gcd((long long)a, (long long)b);
			for (int c = 1; c <= K; c++) {
				int gcd2 = (int)gcd((long long)gcd1, (long long)c);
				sum += gcd2;
			}
		}
	}

	cout << sum << endl;
	return;
}

void D_RGB_Triplets(void) {

	int N; cin >> N;
	string S; cin >> S;

	long long counter = 0LL;
	rep(j, N) {
		char c1, c2;
		switch (S[j]) {
		case 'R':
			c1 = 'G'; c2 = 'B'; break;
		case 'G':
			c1 = 'R'; c2 = 'B'; break;
		case 'B':
			c1 = 'R'; c2 = 'G'; break;
		}
		int num1 = 0, num2 = 0;
		rep(i, j) {
			if (S[i] == c1)			num1++;
			else if (S[i] == c2)	num2++;
		}
		for (int k = j + 1; k < N; k++) {
			if (S[k] == c1) {
				if (j * 2 - k >= 0 && S[j * 2 - k] == c2)	counter +=((long long)num2 - 1LL);
				else										counter += num2;
			}
			else if (S[k] == c2) {
				if (j * 2 - k >= 0 && S[j * 2 - k] == c1)	counter += ((long long)num1 - 1LL);
				else										counter += num1;
			}
		}
	}

	cout << counter << endl;
	return;
}

int main(void) {

	cout << fixed << setprecision(15);

	//A_Lucky_7();
	//B_FizzBuzz_Sum();
	//C_Sum_of_gcd_of_Tuples_Easy();
	D_RGB_Triplets();
	return 0;
}
