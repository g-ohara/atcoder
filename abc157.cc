#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void A_Duplex_Printing(void) {

	int N;
	cin >> N;
	cout << int((N + 1) / 2);
	return;
}

void B_Bingo(void) {

	struct Num {
		int a = 0;
		bool state = false;
	};

	struct Num num[3][3];
	
	for (int loop1 = 0; loop1 < 3; loop1++) {
		for (int loop2 = 0; loop2 < 3; loop2++) {
			cin >> num[loop1][loop2].a;
		}
	}

	int N;
	cin >> N;

	int b;
	for (int loop = 0; loop < N; loop++) {
		cin >> b;
		for (int loop1 = 0; loop1 < 3; loop1++) {
			for (int loop2 = 0; loop2 < 3; loop2++) {
				if (num[loop1][loop2].a == b) {
					num[loop1][loop2].state = true;
					goto label1;
				}
			}
		}
	label1:
		continue;
	}

	for (int loop = 0; loop < 3; loop++) {
		if (num[loop][0].state && num[loop][1].state && num[loop][2].state
			|| num[0][loop].state&& num[1][loop].state&& num[2][loop].state) {
			cout << "Yes" << flush;
			return;
		}
	}
	if (num[0][0].state && num[1][1].state && num[2][2].state
		|| num[0][2].state&& num[1][1].state&& num[2][0].state) {
		cout << "Yes" << flush;
		return;
	}

	cout << "No" << flush;
	return;
}

void C_Guess_The_Number(void) {

	int N, M;
	cin >> N >> M;

	int num[3] = { -1, -1, -1 };
	int s, c;
	for (int loop = 0; loop < M; loop++) {
		cin >> s >> c;
		if (num[s - 1] == -1 || num[s - 1] == c) {
			num[s - 1] = c;
		}
		else {
			cout << -1 << flush;
			return;
		}
	}

	if (N > 1 && num[0] == 0) {
		cout << -1 << flush;
		return;
	}
	if (N > 1 && num[0] == -1) num[0] = 1;
	for (int loop = 0; loop < N; loop++) {
		cout << ((num[loop] == -1) ? 0 : num[loop]) << flush;
	}
	return;
}

struct Human {
	vector<int> Friend;
	vector<int> Relation;

	int suggestionNum = 0;
	vector<int> memory;
};
vector<struct Human> human;
void search(int start, int target) {
	
	for (int loop = 0; loop < human[target].Friend.size(); loop++) {

		if (find(human[start].memory.begin(), human[start].memory.end(), human[target].Friend[loop]) 
			== human[start].memory.end()) {

			if (find(human[start].Relation.begin(), human[start].Relation.end(), human[target].Friend[loop])
				== human[start].Relation.end()) {

				human[start].suggestionNum++;
			}

			human[start].memory.push_back(loop);
			search(loop, start);
		}
	}
}
void D_Friend_Suggestion(void) {

	int N, M, K;
	cin >> N >> M >> K;

	for (int loop = 0; loop < N; loop++) {
		human.push_back({});
	}

	int A, B;
	for (int loop = 0; loop < M; loop++) {
		cin >> A >> B;
		human[A - 1].Friend.push_back(B - 1);
		human[A - 1].Relation.push_back(B - 1);
		human[B - 1].Friend.push_back(A - 1);
		human[B - 1].Relation.push_back(A - 1);
	}
	int C, D;
	for (int loop = 0; loop < K; loop++) {
		cin >> C >> D;
		human[C - 1].Relation.push_back(D - 1);
		human[D - 1].Relation.push_back(C - 1);
	}

	for (int loop1 = 0; loop1 < N; loop1++) {
		for (int loop2 = 0; loop2 < N; loop2++) {

			search(loop1, human[loop1].Friend[loop2]);
		}
		cout << human[loop1].suggestionNum << " ";
	}

	return;
}

int main(void) {

	//A_Duplex_Printing();
	//B_Bingo();
	//C_Guess_The_Number();
	D_Friend_Suggestion();
	return 0;
}
