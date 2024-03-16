/*
ABC #158 (2020.03.07)

初参加。初心者向けと高を括っていたが結果はAのみ正解と散々。
サンプルを用いた実行には成功しても提出すると不正解になってしまう。
焦らずに課題を一つずつ丁寧に解決していきたい。
Bは入力サイズが大きくなるに従って処理時間がネックになる問題であった。
時間短縮のために、文字列の処理にはvectorやdequeを用いたい。
その他にも柔軟なアルゴリズムの構築を。
*/

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

void A_Station_and_Bus(void) {

	string S;

	cin >> S;

	cout << ((S[0] == S[1] && S[0] == S[2]) ? "No" : "Yes") << flush;

	return;
}

void B_Count_Balls(void) {

	long n;
	//int a, b;
	long a, b;

	//long count = 0;

	cin >> n >> a >> b;

	//count = (n - (n % (a + b))) / (a + b);
	long count = long(n / (a + b));

	/*
	if (n % (a + b) <= a) {

		cout << n % (a + b) + count * a;
	}
	else {

		cout << a + count * a;
	}
	*/
	cout << ((n % (a + b) <= a) ? count * a + n % (a + b) : a * (count + 1));

	return;
}

void C_Tax_Increase(void) {

	int a, b;
	/*
	int pa[1000] = { -1 };
	int pb[1000] = { -1 };

	int flag = 0;
	int re = 0;
	*/
	cin >> a >> b;

	/*
	for (int loop = 1; loop < 1400; loop++) {

		if ((int)(loop * 0.08) == a && flag < 1000) {
			pa[flag] = loop;
			flag++;
		}
	}

	flag = 0;
	for (int loop = 1; loop < 1400; loop++) {

		if ((int)(loop * 0.1) == b && flag < 1000) {
			pb[flag] = loop;
			flag++;
		}
	}

	for (int xloop = 0; xloop < 1000; xloop++) {

		for (int yloop = 0; yloop < 1000; yloop++) {

			if (pa[xloop] != -1 && pa[xloop] == pb[yloop]) {

				re = pa[xloop];
			}
		}
	}

	for (int xloop = 0; xloop < 1000; xloop++) {

		for (int yloop = 0; yloop < 1000; yloop++) {

			if (pa[yloop] != -1 && pa[yloop] == pb[xloop]) {

				if (re > pa[yloop]) re = pa[yloop];
			}
		}
	}

	if (re > 0) {

		cout << re << flush;
	}
	else {

		cout << -1 << flush;
	}
	*/

	for (int loop = 0; loop < 1400; loop++) {

		if (int(loop * 0.08) == a && int(loop * 0.10) == b) {

			cout << loop << flush;
			return;
		}
	}

	cout << -1 << flush;
	return;
}

void D_String_Formation(void) {

	string S1;
	deque<char> S2;
	int Q;

	cin >> S1;
	cin >> Q;

	for (int loop = 0; loop < (int)S1.size(); loop++) {

		S2.push_back(S1[loop]);
	}

	int T;
	int F;
	char C;

	int max = 0;
	char sBuff;

	//
	bool order = true;

	int loop1 = 0;
	int loop2 = 0;

	for (loop1 = 0; loop1 < Q; loop1++) {

		cin >> T;

		if (T == 1) {
			/*
			max = (int)(S.size() * 0.5);

			for (loop2 = 0; loop2 < max; loop2++) {

				sBuff = S[loop2];
				S[loop2] = S[S.size() - loop2 - 1];
				S[S.size() - loop2 - 1] = sBuff;
			}
			*/
			order = !order;
		}
		else {

			cin >> F >> C;

			if (order && F == 1 || !order && F == 2) {

				//S = C + S;
				S2.push_front(C);
			}
			else {

				//S = S + C;
				S2.push_back(C);
			}
		}
	}

	if (!order) {

		max = (int)(S2.size() * 0.5);

		for (loop2 = 0; loop2 < max; loop2++) {

			sBuff = S2[loop2];
			S2[loop2] = S2[S2.size() - loop2 - 1];
			S2[S2.size() - loop2 - 1] = sBuff;
		}
	}

	S1 = "";

	for (int loop = 0; loop < (int)S2.size(); loop++) {

		S1 += S2[loop];
	}

	cout << S1;

	return;
}

void E_Divisible_String(void) {

	int N, P;
	cin >> N >> P;

	string S1;
	cin >> S1;

	vector<int>S2(N);
	for (int loop = 0; loop < N; loop++) {
		S2[loop] = (int)S1[loop] - (int)'0';
	}

	int counter = 0;
	int num = 0;

	for (int start = 0; start < N; start++) {
		for (int end = start; end < N; end++) {

			num = 0;
			for (int loop = start; loop <= end; loop++) {
				num = (num * 10 + S2[loop]) % P;
			}
			if (num == 0) counter++;
		}
	}

	cout << counter << flush;
	return;
}

int counter = 0;
struct Robot {
	int X;
	int D;
	bool existance = true;
};
class Memory {
public:
	vector<bool> survival;
	Memory(int N);
};
Memory::Memory(int N) {
	for (int loop = 0; loop < N; loop++) {
		survival.push_back(true);
	}
}
class Line {
public:
	int N;
	vector<struct Robot> robot;
	vector<class Memory> memory;
	void movement(int index);
	void counting(void);
	Line(int n);
};
void Line::movement(int index) {

	robot[index].existance = false;

	for (int loop = 0; loop < N; loop++) {
		if (robot[loop].existance
			&& robot[loop].X >= robot[index].X
			&& robot[loop].X < robot[index].X + robot[index].D) {
			movement(loop);
		}
	}
	return;
}
void Line::counting(void) {
	for (int loop1 = 0; loop1 < (int)memory.size(); loop1++) {
		for (int loop2 = 0; loop2 < N; loop2++) {
			if (robot[loop2].existance != memory[loop1].survival[loop2]) {
				goto lavel1;
			}
		}
		return;
	lavel1:
		continue;
	}
	class Memory temp(N);
	for (int loop = 0; loop < N; loop++) {
		temp.survival[loop] = robot[loop].existance;
	}
	memory.push_back(temp);
	counter++;
	if (counter >= 998244353) counter -= 998244353;
	return;
}
Line::Line(int n) {
	N = n;
	for (int loop = 0; loop < N; loop++) {
		robot.push_back({ 0,0,true });
	}
}
void recursion(class Line line) {

	for (int index = 0; index < line.N; index++) {

		if (line.robot[index].existance) {

			line.movement(index);
			line.counting();
			recursion(line);
		}
	}
}
void F_Removing_Robots(void) {

	int N;
	cin >> N;

	class Line line(N);

	for (int loop = 0; loop < N; loop++) {
		cin >> line.robot[loop].X >> line.robot[loop].D;
	}

	recursion(line);

	cout << counter << flush;
	return;
}

int main(void) {

	//A_Station_and_Bus();
	//B_Count_Balls();
	//C_Tax_Increase();
	//D_String_Formation();
	//E_Divisible_String();
	F_Removing_Robots();
	return 0;
}
