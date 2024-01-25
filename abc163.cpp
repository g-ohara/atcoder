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

template<typename Type>
int binary_search(std::vector<Type> vec, Type key)
{
	int left = 0;
	int right = (int)vec.size() - 1;
	while (right >= left)
	{
		int mid = (left + right) / 2;
		if (a[mid] == key)		return mid;
		else if (a[mid] > key)	right = mid - 1;
		else if (a[mid] < key)	left = mid + 1;
	}
	return vec.size();
}

void A_Circle_Pond(void) {

	double R; cin >> R;

	cout << R * 2.0 * 3.141592 << endl;
	return;
}

void B_Homework(void) {

	int N, M; cin >> N >> M;
	int counter = 0;
	rep(i, M) {
		int A; cin >> A;
		counter += A;
	}

	if (counter <= N)	cout << N - counter << endl;
	else				cout << -1 << endl;
	return;
}

void C_management(void) {

	int N; cin >> N;
	vector<int> employee(N);
	rep(i, N - 1) {
		int A; cin >> A;
		employee[A - 1]++;
	}

	for (int he : employee) cout << he << endl;
	return;
}

void D_Sum_of_Large_Numbers(void) {

	long long N, K; cin >> N >> K;

	long long counter = 0;
	for (long long i = K; i <= N + 1; i++) counter = (counter + i * (N + 1 - i) + 1) % 1000000007;
	
	cout << counter << endl;
	return;
}

void E_Active_Infants(void) {

	int N; cin >> N;
	vector<int> A(N); for (int& it : A) cin >> it;

	int left = 0;
	int right = N - 1;
	long long counter = 0LL;
	rep(loop, N) {
		int maxIndex = 0;
		long long maxValue = 0LL;
		rep(index, N) {
			long long value = (long long)A[index] * (long long)max(index - left, right - index);
			if (value > maxValue || value == maxValue && A[index] > A[maxIndex]) {
				maxIndex = index;
				maxValue = value;
			}
		}
		counter += maxValue;
		A[maxIndex] = 0;
		if (maxIndex - left > right - maxIndex) left++;
		else									right--;
	}

	cout << counter << endl;
	return;
}

int main(void) {

	//A_Circle_Pond();
	//B_Homework();
	//C_management();
	//D_Sum_of_Large_Numbers();
	E_Active_Infants();
	return 0;
}
