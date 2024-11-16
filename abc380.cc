#include <bits/stdc++.h>

void A(void) {
  std::string N;
  std::cin >> N;

  int ones = 0;
  int twos = 0;
  int threes = 0;
  for (char c : N) {
    if (c == '1') {
      ++ones;
    } else if (c == '2') {
      ++twos;
    } else if (c == '3') {
      ++threes;
    }
  }

  if (ones == 1 && twos == 2 && threes == 3) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

void B(void) {
  std::string S;
  std::cin >> S;

  int count = 0;
  for (char c : S) {
    if (c == '|') {
      if (count) {
        std::cout << count << " ";
        count = 0;
      }
    } else {
      ++count;
    }
  }
  std::cout << std::endl;
}

void C(void) {
  int N;
  int K;
  std::cin >> N >> K;
  std::string S;
  std::cin >> S;

  bool one_appeared = false;
  std::string buf = "";
  int count = 0;
  for (char c : S) {
    if (c == '0') {
      if (one_appeared) {
        ++count;
        one_appeared = false;
      }
      if (count == K - 1) {
        buf += c;
      } else if (count == K) {
        std::cout << buf << c;
        ++count;
        buf = "";
      } else {
        std::cout << c;
      }
    } else if (c == '1') {
      one_appeared = true;
      std::cout << c;
    }
  }
  std::cout << buf << std::endl;
}

int get_count(long long int w) {
  int count = 0;
  while (w > 0) {
    // int n = static_cast<int>(log2(w));
    int n = 0;
    long long int _w = w;
    while (_w > 1) {
      _w /= 2;
      ++n;
    }
    long long int pow = 1;
    for (int i = 0; i < n; ++i) {
      pow *= 2LL;
    }
    w -= pow;
    ++count;
  }
  return count;
}

void D(void) {
  std::string S;
  std::cin >> S;
  int Q;
  std::cin >> Q;
  std::vector<long long int> K(Q);
  for (long long int& k : K) {
    std::cin >> k;
    --k;
  }

  for (long long int k : K) {
    int char_i = k % S.size();
    long long int w = k / S.size();

    // std::cout << "k = " << k << std::endl;
    int count = get_count(w);
    // std::cout << count << std::endl;
    if (count % 2 == 0) {
      std::cout << S[char_i];
    } else {
      if (islower(S[char_i])) {
        std::cout << static_cast<char>(toupper(S[char_i]));
      } else {
        std::cout << static_cast<char>(tolower(S[char_i]));
      }
    }
    std::cout << " ";
  }
  std::cout << std::endl;
}

int main(void) {
  D();
  return 0;
}
