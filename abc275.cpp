#include <bits/stdc++.h>

#define rep(i, start, end) for (int i = start; i < end; ++i)
using namespace std;

int pow_result[19] = {0};

/*
    calculates (n ^ k) % mod (繰り返し二乗法)
    ex. n^19 = n^1 * n^2 * n^16
*/
uint64_t power_mod(uint64_t n, uint64_t k, uint64_t mod) 
{
    uint64_t result = 1;
    // k を右シフトしつつ n を 2 乗していく
    for (; k > 0; k >>= 1)
    {
        // k の最下位ビットが 1 なら、n を答えに掛ける
        if (k & 1) 
            result = (result * n) % mod;

        n = (n * n) % mod;
    }
    return result;
}

/**
 * @brief mod逆元の計算 
 * @param P prime number
 * @return uint64_t nx = 1 (mod P)を満足するx(=n^(p-2)%P)
 */
uint64_t mod_inv(uint64_t n, uint64_t P)
{
    return power_mod(n, P - 2, P);
}

typedef int Node;
class Graph : public vector<vector<Node>>
{
public:
    void BFS(vector<int>& depth, Node start);
    Graph(size_t size) : vector<vector<Node>>(size){}
};

void Graph::BFS(vector<int>& depth, Node start)
{
    vector<bool> visited(size(), false);

    queue<Node> node;
    node.push(start);
    depth.at(start) = 0;

    while(!node.empty()) 
    {
        visited.at(node.front()) = true;
        for (const Node& next_node : at(node.front()))
            if (!visited.at(next_node))
            {
                visited.at(next_node) = true;
                node.push(next_node);
                depth.at(next_node) = depth.at(node.front()) + 1;
            }
        node.pop();
    }
}

void A(void)
{
    int max_height = 0;
    int max_index = 0;
    int N;
    cin >> N;
    rep(i, 0, N)
    {
        int H;
        cin >> H;
        if (H > max_height)
        {
            max_height = H;
            max_index = i + 1;
        } 
    }
    cout << max_index << endl;
}


void B(void)
{
    uint64_t A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;

    const uint64_t mod = 998244353;
    uint64_t ret = ((((A % mod) * (B % mod)) % mod) * (C % mod)) % mod;
    ret -= ((((D % mod) * (E % mod)) % mod) * (F % mod)) % mod;
    ret = (ret + mod) % mod;
    cout << ret << endl;
}

void C(void)
{
    bool pawn[9][9];
    rep(i, 0, 9)
    rep(j, 0, 9)
    {
        char c;
        cin >> c;
        pawn[i][j] = (c == '#');
    }
        

    int cnt = 0;

    rep(i, 0, 9)
    rep(j, 0, 9)
    {
        if (pawn[i][j])
        {
            rep(k, i + 1, 9)
            rep(m, j, 9)
            {
                if (pawn[k][m])
                {
                    int dx = m - j;
                    int dy = k - i;
                    if (0 <= i + dx && i + dx < 9 && 
                        0 <= k + dx && k + dx < 9 &&
                        0 <= j - dy && j - dy < 9 &&
                        0 <= m - dy && m - dy < 9)
                    {
                        if (pawn[i + dx][j - dy] && pawn[k + dx][m - dy])
                        {
                            ++cnt;
                            // cout << i << ' ' << j << " ";
                            // cout << k << ' ' << m << endl;
                        }
                    }
                }   
            }
        }
    }

    cout << cnt << endl;
}


map<int, uint64_t> result;

uint64_t f(uint64_t x)
{
    if (result.find(x) != result.end())
    {
        return result[x];
    }
    else
    {
        uint64_t ret = (x ? f(x/2) + f(x/3) : 1);
        result[x] = ret;
        return ret;
    }
}

void D(void)
{
    uint64_t N;
    cin >> N;
    cout << f(N) << endl;
}

uint64_t prob(int len, int depth, int M, int M_inv)
{
    const int mod = 998244353;
    if (len == 0)
    {
        return 1;
    }
    else if (depth == 0)
    {
        return 0;
    }
    else if (result.find(len) != result.end())
    {
        return result[len];
    }
    else
    {
        uint64_t ret = 0;
        rep(i, 1, M + 1)
        {
            int next_len = (len - i >= 0 ? len - i : i - len);
            ret += (M_inv * prob(next_len, depth - 1, M, M_inv)) % mod;
        }
        ret %= mod;
        result[len] = ret;
        return ret;
    }
}

void E(void)
{
    int N, M, K;
    cin >> N >> M >> K;
    cout << prob(N, K, M, mod_inv(M, 998244353)) << endl;
}

int main(void)
{
    E();
}
