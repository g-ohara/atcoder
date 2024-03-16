// Copyright

#include <bits/stdc++.h>

void A_Yay(void) {
  std::string S;
  std::cin >> S;

  char trg = S[0];
  for (int i = 1; i < static_cast<int>(S.size()); ++i) {
    if (S[i] != trg) {
      if (i == 1 && S[i] == S[i + 1]) {
        std::cout << 1 << std::endl;
      } else {
        std::cout << i + 1 << std::endl;
      }
      break;
    }
  }
}

void B_Which_is_ahead(void) {
  int N;
  std::cin >> N;

  std::vector<int> my_order(N);
  for (int i = 0; i < N; ++i) {
    int P;
    std::cin >> P;
    my_order[P - 1] = i;
  }

  int Q;
  std::cin >> Q;
  for (int i = 0; i < Q; ++i) {
    int A, B;
    std::cin >> A >> B;
    if (my_order[A - 1] < my_order[B - 1]) {
      std::cout << A << std::endl;
    } else {
      std::cout << B << std::endl;
    }
  }
}

void C(void) {
  int N;
  std::cin >> N;

  std::string S;
  std::cin >> S;

  int Q;
  std::cin >> Q;

  std::array<int, 26> replaced_to;
  for (int i = 0; i < 26; ++i) {
    replaced_to[i] = i;
  }

  for (int i = 0; i < Q; ++i) {
    char c, d;
    std::cin >> c >> d;
    c -= 'a';
    d -= 'a';
    std::replace_if(replaced_to.begin(), replaced_to.end(),
    [c](int x) { return x == c; }, d);
  }

  std::transform(S.begin(), S.end(), S.begin(),
  [&replaced_to](char c) { return 'a' + replaced_to[c - 'a']; });

  std::cout << S << std::endl;
}

void D(void) {
  int N;
  std::cin >> N;
  std::vector<int> A(N);
  for (int &a : A) {
    std::cin >> a;
  }

  for (int i = 2; i < 500; ++i) {
    for (int &a : A) {
      while (a > 0 && a % (i * i) == 0) {
        a /= i * i;
      }
    }
  }

  std::array<int, 200000> count = {0};
  for (int a : A) {
    ++count[a];
  }

  uint64_t ans = 0;
  std::accumulate(count.begin(), count.end(), 0,
  [&ans](int c) { ans += (uint64_t) c * ((uint64_t) c - 1) / 2; });
  ans += count[0] * (N - count[0]);
  std::cout << ans << std::endl;
}

int main() {
  D();
  return 0;
}
