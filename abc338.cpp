#include <bits/stdc++.h>
#include <iterator>

void A(void) {
  std::string S;
  std::cin >> S;

  if (S[0] < 'A' || S[0] > 'Z') {
    std::cout << "No" << std::endl;
  } else {
    for (int i = 1; i < S.size(); i++) {
      if (S[i] < 'a' || S[i] > 'z') {
        std::cout << "No" << std::endl;
        return;
      }
    }
    std::cout << "Yes" << std::endl;
  }
}

void B(void) {
  std::string S;
  std::cin >> S;

  std::array<int, 26> dict = {0};
  for (char c : S) {
    ++dict[c - 'a'];
  }

  auto max_iter = std::max_element(dict.begin(), dict.end());
  int max_index = std::distance(dict.begin(), max_iter);

  std::cout << char('a' + max_index) << std::endl;
}

void C(void) {
  int N;
  std::cin >> N;

  std::vector<int> Q(N), A(N), B(N);
  for (int i = 0; i < N; i++) {
    std::cin >> Q[i];
  }
  for (int i = 0; i < N; i++) {
    std::cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    std::cin >> B[i];
  }

  int max = 0;
  for (int a = 0; ; a++) {
    int b = INT_MAX;
    for (int i = 0; i < N; i++) {
      if (B[i] == 0) {
        continue;
      }
      int n = Q[i] / B[i];
      b = std::min(n, b);
    }

    max = std::max(max, a + b);
    for (int i = 0; i < N; i++) {
      Q[i] -= A[i];
      if (Q[i] < 0) {
        std::cout << max << std::endl;
        return;
      }
    }
  }
}


void D(void) {
  int N, M;
  std::cin >> N >> M;

  std::vector<int> island(N);
  int prev;
  std::cin >> prev;
  --prev;
  int sum_distance = 0;
  for (int i = 1; i < M; ++i) {
    int next;
    std::cin >> next;
    --next;

    int start = std::min(prev, next);
    int end = std::max(prev, next);
    int distance = end - start;

    if (distance * 2 < N) {
      island[start] += N - distance * 2;
    } else {
      distance = N - distance;
      island[end] += N - distance * 2;
    }
    sum_distance += distance;
    prev = next;
  }

  int cost = 0;
  for (int i = 0; i < (N - 1) / 2; ++i) {
    cost += island[i];
  }

  int min_cost = cost;
  for (int i = 1; i < N; ++i) {
    cost = cost - island[i - 1] + island[(i + (N - 1) / 2 - 1) % N];
    min_cost = std::min(min_cost, cost);
  }

  std::cout << sum_distance + min_cost << std::endl;
}

// void D(void) {
//   int N, M;
//   std::cin >> N >> M;
//
//   std::vector<int> bridge(N, 0);
//   int prev;
//   std::cin >> prev;
//   --prev;
//   int sum_distance = 0;
//   for (int i = 1; i < M; ++i) {
//     int next;
//     std::cin >> next;
//     --next;
//
//     int start = std::min(prev, next);
//     int end = std::max(prev, next);
//     int distance = end - start;
//
//     if (distance * 2 < N) {
//       for (int i = start; i < end; ++i) {
//         bridge[i] += N - distance * 2;
//       }
//     } else {
//       distance = N - distance;
//       for (int i = 0; i < start; ++i) {
//         bridge[i] += N - distance * 2;
//       }
//       for (int i = end; i < N; ++i) {
//         bridge[i] += N - distance * 2;
//       }
//     }
//     sum_distance += distance;
//     prev = next;
//   }
//   int min_cost = *std::min_element(bridge.begin(), bridge.end());
//   std::cout << sum_distance + min_cost << std::endl;
// }


int main() {
  // A();
  // B();
  // C();
  D();
  return 0;
}
