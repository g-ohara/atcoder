// Copyright

#include <bits/stdc++.h>

void A_Leftrightarrow(void) {
  std::string S;
  std::cin >> S;
  if (S[0] == '<' && S[S.size() - 1] == '>') {
    for (int i = 1; i < static_cast<int>(S.size()) - 1; ++i) {
      if (S[i] != '=') {
        std::cout << "No" << std::endl;
        return;
      }
    }
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

void B_Integer_Division_Returns(void) {
  int64_t X;
  std::cin >> X;
  int mod = (10 - X % 10) % 10;
  std::cout << (X + mod) / 10 << std::endl;
}

void C_One_Time_Swap(void) {
  std::string S;
  std::cin >> S;

  std::array<int, 26> count = {0};
  for (auto c : S) {
    ++count[c - 'a'];
  }

  int64_t ans = 0;
  for (int i = 0; i < 26; ++i) {
    for (int j = i + 1; j < 26; ++j) {
      ans += count[i] * count[j];
    }
  }

  for (int i = 0; i < 26; ++i) {
    if (count[i] > 1) {
      ++ans;
      break;
    }
  }

  std::cout << ans << std::endl;
}


typedef std::vector<std::vector<bool>> Grid;
typedef std::pair<int, int> Tile;
typedef std::vector<Tile> Tiles;

bool grids_are_full(
  const Grid &placed, int H, int W
) {
  for (const std::vector<bool> &row : placed) {
    if (std::any_of(row.begin(), row.end(), [](bool x) { return !x; })) {
      return false;
    }
  }
  return true;
}


bool grids_are_empty(
  const Grid &placed, int i, int j, int A, int B, int H, int W
) {
  for (int k = 0; k < A; ++k) {
    for (int l = 0; l < B; ++l) {
      if (placed[i + k][j + l]) {
        return false;
      }
    }
  }
  return true;
}


bool tile_can_be_placed(
  const Tiles &tiles,
  const Grid &placed,
  int tile_idx, int N, int H, int W
) {
  // std::cout << tile_idx << std::endl;
  // for (int i = 0; i < H; ++i) {
  //   for (int j = 0; j < W; ++j) {
  //     if (placed[i][j]) {
  //       std::cout << "o";
  //     } else {
  //       std::cout << ".";
  //     }
  //   }
  //   std::cout << std::endl;
  // }

  if (tile_idx == N) {
    // O(H * W)
    return grids_are_full(placed, H, W);
  }

  if (tile_can_be_placed(tiles, placed, tile_idx + 1, N, H, W)) {
    return true;
  }

  int A = tiles[tile_idx].first;
  int B = tiles[tile_idx].second;
  for (int rot = 0; rot < 2; ++rot) {
    if (rot) {
      std::swap(A, B);
    }
    // O(H * W * A * B)
    for (int i = 0; i <= H - A; ++i) {
      for (int j = 0; j <= W - B; ++j) {
        // O(A * B)
        if (grids_are_empty(placed, i, j, A, B, H, W)) {
          Grid tmp_placed = placed;
          // O(A * B)
          for (int k = i; k < i + A; ++k) {
            for (int l = j; l < j + B; ++l) {
              tmp_placed[k][l] = true;
            }
          }
          if (tile_can_be_placed(tiles, tmp_placed, tile_idx + 1, N, H, W)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}


void D_Tiling(void) {
  int N, H, W;
  std::cin >> N >> H >> W;

  Tiles tiles(N);
  for (auto &t : tiles) {
    std::cin >> t.first >> t.second;
  }

  Grid placed(H, std::vector<bool>(W, false));
  // O(N * H * W * A * B)
  if (tile_can_be_placed(tiles, placed, 0, N, H, W)) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}


int main() {
  // A_Leftrightarrow();
  // B_Integer_Division_Returns();
  // C_One_Time_Swap();
  D_Tiling();
  return 0;
}
