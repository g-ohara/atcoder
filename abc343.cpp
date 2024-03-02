// Copyright

#include <bits/stdc++.h>

void A_Wrong_Answer(void) {
  int A, B;
  std::cin >> A >> B;
  if (A + B == 0) {
    std::cout << 1 << std::endl;
  } else {
    std::cout << 0 << std::endl;
  }
}

void B_Adjascency_Matrix(void) {
  int N;
  std::cin >> N;
  std::vector<std::vector<int>> A(N, std::vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cin >> A[i][j];
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i][j] == 1) {
        std::cout << j + 1 << " ";
      }
    }
    std::cout << std::endl;
  }
}

void C_343(void) {
  int64_t N;
  std::cin >> N;

  for (int64_t i = 1000000; i > 0; --i) {
    int64_t trg = i * i * i;
    if (trg > N) {
      continue;
    }
    std::vector<int> digits(0);
    for (int j = 0; trg > 0; ++j) {
      digits.push_back(trg % 10);
      trg /= 10;
    }

    bool is_palindrome = true;
    for (int j = 0; j < static_cast<int>(digits.size()) / 2; ++j) {
      if (digits[j] != digits[digits.size() - j - 1]) {
        is_palindrome = false;
        break;
      }
    }
    if (is_palindrome) {
      std::cout << i *i *i << std::endl;
      return;
    }
  }
}

void D_Diversity_of_Scores(void) {
  int N, T;
  std::cin >> N >> T;
  std::vector<int> A(T, 0);
  std::vector<int> B(T, 0);
  for (int i = 0; i < T; ++i) {
    std::cin >> A[i] >> B[i];
    --A[i];
  }

  std::vector<int64_t> scores(N, 0);
  std::map<int64_t, int> count;
  count[0] = N;
  int diversity = 1;

  for (int i = 0; i < T; ++i) {
    if (count[scores[A[i]]] == 1) {
      --diversity;
    }
    --count[scores[A[i]]];
    scores[A[i]] += B[i];
    if (count[scores[A[i]]] == 0) {
      ++diversity;
    }
    ++count[scores[A[i]]];
    std::cout << diversity << std::endl;
  }
}

int max(int a, int b, int c) {
  return std::max(std::max(a, b), c);
}

int min(int a, int b, int c) {
  return std::min(std::min(a, b), c);
}

int calc3(
  int a1, int b1, int c1, int a2, int b2, int c2, int a3, int b3, int c3
) {
  int xa = std::max(0, min(a1, a2, a3) + 7 - max(a1, a2, a3));
  int xb = std::max(0, min(b1, b2, b3) + 7 - max(b1, b2, b3));
  int xc = std::max(0, min(c1, c2, c3) + 7 - max(c1, c2, c3));
  return xa * xb * xc;
}

int _calc2(int a1, int b1, int c1, int a2, int b2, int c2) {
  int xa = std::max(0, 7 - std::abs(a1 - a2));
  int xb = std::max(0, 7 - std::abs(b1 - b2));
  int xc = std::max(0, 7 - std::abs(c1 - c2));
  return xa * xb * xc;
}

int calc2(
  int a1, int b1, int c1, int a2, int b2, int c2, int a3, int b3, int c3
) {
  int r1 = _calc2(a1, b1, c1, a2, b2, c2);
  int r2 = _calc2(a1, b1, c1, a3, b3, c3);
  int r3 = _calc2(a2, b2, c2, a3, b3, c3);
  return r1 + r2 + r3;
}

void E_7x7x7(void) {
  int V1, V2, V3;
  std::cin >> V1 >> V2 >> V3;

  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  for (int a2 = -7; a2 <= 7; ++a2) {
    for (int b2 = -7; b2 <= 7; ++b2) {
      for (int c2 = -7; c2 <= 7; ++c2) {
        for (int a3 = -14; a3 <= 14; ++a3) {
          for (int b3 = -14; b3 <= 14; ++b3) {
            for (int c3 = -14; c3 <= 14; ++c3) {
              int v3 = calc3(a1, b1, c1, a2, b2, c2, a3, b3, c3);
              if (v3 != V3) {
                continue;
              }

              int v2 = calc2(a1, b1, c1, a2, b2, c2, a3, b3, c3) - v3 * 3;
              if (v2 != V2) {
                continue;
              }

              int v1 = 7 * 7 * 7 * 3 - v2 * 2 - v3 * 3;
              if (v1 != V1) {
                continue;
              }

              std::cout << "Yes" << std::endl;
              std::cout << a1 << " " << b1 << " " << c1 << " ";
              std::cout << a2 << " " << b2 << " " << c2 << " ";
              std::cout << a3 << " " << b3 << " " << c3 << std::endl;
              return;
            }
          }
        }
      }
    }
  }
  std::cout << "No" << std::endl;
}

int main() {
  // A_Wrong_Answer();
  // B_Adjascency_Matrix();
  // C_343();
  // D_Diversity_of_Scores();
  E_7x7x7();
  return 0;
}
