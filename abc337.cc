#include <bits/stdc++.h>

void A_ScoreBoard(void) {
  int N;
  std::cin >> N;

  int sum_X = 0;
  int sum_Y = 0;
  for (int i = 0; i < N; ++i) {
    int X, Y;
    std::cin >> X >> Y;
    sum_X += X;
    sum_Y += Y;
  }

  if (sum_X > sum_Y) {
    std::cout << "Takahashi" << std::endl;
  } else if (sum_X < sum_Y) {
    std::cout << "Aoki" << std::endl;
  } else {
    std::cout << "Draw" << std::endl;
  }
}

void B_Extended_ABC(void) {

  std::string S;
  std::cin >> S;

  int flag = 0;
  char chars[3] = {'A', 'B', 'C'};
  for (char c : chars) {
    for (; flag < S.size(); ++flag) {
      if (S[flag] != c) {
        break;
      }
    }
  }
  if (flag == S.size()) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

void C_Lining_Up_2(void) {
  int N;
  std::cin >> N;

  std::vector<int> idx(N + 1);
  for (int i = 1; i <= N; ++i) {
    int A;
    std::cin >> A;
    idx.at(A == -1 ? 0 : A) = i;
  }

  int flag = 0;
  for (int i = 0; i < N; ++i) {
    std::cout << idx[flag] << " ";
    flag = idx[flag];
  }
}

int get_min_count(std::string s, int K, int min_count) {

  int start = 0;
  int count = -1;
  while (start + K <= s.size()) {
    if (count == -1) {
      count = 0;
      for (int i = start; i < start + K; ++i) {
        if (s[i] == '.') {
          ++count;
        } else if (s[i] == 'x') {
          count = -1;
          start = i + 1;
          break;
        }
      }
    } else {
      if (s[start - 1] == '.') {
        --count;
      }
      if (s[start + K - 1] == '.') {
        ++count;
      } else if (s[start + K - 1] == 'x') {
        count = -1;
        start += K;
      }
    }
    if (count != -1) {
      min_count = min_count == -1 ? count : std::min(min_count, count);
      ++start;
    }
  }
  return min_count;
  //for (int i = 0; i < s.size(); ++i) {
  //  if ((s[i] == 'o' || s[i] == '.') && i + K <= s.size()) {
  //    int count = 0;
  //    for (int j = 0; j < K; ++j) {
  //      if (s[i + j] == '.') {
  //        ++count;
  //      } else if (s[i + j] == 'x') {
  //        count = -1;
  //        break;
  //      }
  //    }
  //    if (count != -1) {
  //      min_count = min_count == -1 ? count : std::min(min_count, count);
  //    }
  //  }
  //}
}

void D_Cheating_Gomoku_Narabe(void) {

  int H, W, K;
  std::cin >> H >> W >> K;

  std::vector<std::string> S(H);
  for (std::string &s : S) {
    std::cin >> s;
  }

  int min_count = -1;
  for (std::string s : S) {
    min_count = get_min_count(s, K, min_count);
  }
  for (int i = 0; i < W; ++i) {
    std::string s = "";
    for (const std::string &row : S) {
      s += row[i];
    }
    min_count = get_min_count(s, K, min_count);
  }

  std::cout << min_count << std::endl;
}

int main() {
  // A_ScoreBoard();
  // B_Extended_ABC();
  // C_Lining_Up_2();
  D_Cheating_Gomoku_Narabe();
  return 0;
}
