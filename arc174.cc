// Copyright

#include <bits/stdc++.h>

int64_t max(int64_t a, int64_t b) {
  return a > b ? a : b;
}

int64_t min(int64_t a, int64_t b) {
  return a < b ? a : b;
}

void A_A_Multiply(void) {
  int N, C;
  std::cin >> N >> C;
  std::vector<int> A(N);

  int64_t sum = 0;
  for (int &a : A) {
    std::cin >> a;
    sum += a;
  }

  int64_t subsum = 0;
  int64_t ans = 0;

  if (C > 1) {
    for (int a : A) {
      subsum = max(a, subsum + a);
      ans = max(ans, subsum);
    }
    std::cout << sum + (C - 1) * ans << std::endl;
  } else {
    for (int a : A) {
      subsum = min(a, subsum + a);
      ans = min(ans, subsum);
    }
    std::cout << sum + (C - 1) * ans << std::endl;
  }
}

void B_Bought_Review(void) {
  int T;
  std::cin >> T;
  std::vector<int64_t> ans(T);
  for (int t = 0; t < T; ++t) {
    int64_t S = 0;
    for (int i = 1; i <= 5; ++i) {
      int a;
      std::cin >> a;
      S += (3 - i) * a;
    }
    std::array<int, 5> P;
    for (int &p : P) {
      std::cin >> p;
    }
    int P4 = P[3];
    int P5 = P[4];

    if (S <= 0) {
      ans[t] = 0;
    } else {
      if (P5 - 2 * P4 < 0) {
        int k4 = 0;
        int64_t k5 = S / 2;
        if (S - 2 * k5 > 0) {
          if (P4 < P5) {
            ++k4;
          } else {
            ++k5;
          }
        }
        ans[t] = k4 * P4 + k5 * P5;
      } else {
        ans[t] = S * P4;
      }
    }
  }
  for (int64_t a : ans) {
    std::cout << a << std::endl;
  }
}

void C_Catastrophic_Roulette(void) {
  int N;
  std::cin >> N;
}

int main() {
  // A_A_Multiply();
  // B_Bought_Review();
  C_Catastrophic_Roulette();
  return 0;
}
