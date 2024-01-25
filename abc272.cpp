#include <bits/stdc++.h>

#define rep(i, start, end) for (int i = start; i < end; ++i)
using namespace std;

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
    int N;
    cin >> N;

    int sum = 0;
    rep(i, 0, N)
    {
        int A;
        cin >> A;
        sum += A;
    }

    cout << sum << endl;
}

void B(void)
{
    int N, M;
    cin >> N >> M;

    vector<int> x(N);
    vector<vector<bool>> comb(N, vector<bool>(N, false));
    rep(i, 0, M)
    {
        int k;
        cin >> k;
        rep(j, 0, k)
        {
            cin >> x[j];
            --x[j];
        }

        rep(j, 0, k)
            rep(m, j, k)
            {
                comb[x[j]][x[m]] = true;
                comb[x[m]][x[j]] = true;
            }
    }

    rep(i, 0, N)
        rep(j, 0, N)
            if(!comb[i][j])
            {
                cout << "No" << endl;
                return;
            }
    
    cout << "Yes" << endl;
}

void C(void)
{
    int N;
    cin >> N;

    vector<int> even;
    vector<int> odd;

    rep(i, 0, N)
    {
        int A;
        cin >> A;
        if (A % 2)
            odd.push_back(A);
        else
            even.push_back(A);
    }

    sort(odd.begin(), odd.end(), std::greater<int>());
    sort(even.begin(), even.end(), std::greater<int>());

    int sum_odd = odd.size() >= 2 ? odd[0] + odd[1] : -1;
    int sum_even = even.size() >= 2 ? even[0] + even[1] : -1;

    cout << max(sum_odd, sum_even) << endl;
}

struct Move
{
    int x;
    int y;
    bool is_valid(int N)
    {
        return 0 <= x && x < N && 0 <= y && y < N;
    }
};

Move operator+(const Move& l, const Move& r)
{
    return Move{l.x + r.x, l.y + r.y};
}

void D(void)
{
    int N, M;
    cin >> N >> M;

    vector<Move> move;
    rep(i, 0, (int)sqrt(M / 2) + 1)
    {
        if (fmod(sqrt(M - i * i), 1.0) == 0.0)
        {
            int j = sqrt(M - i * i);
            move.push_back(Move{i, j});
            move.push_back(Move{i, -j});
            move.push_back(Move{j, i});
            move.push_back(Move{j, -i});
        }
    }

    Graph graph(N * N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            Move now = {i, j};
            for (auto next_move : move)
            {
                Move next = now + next_move;
                if (next.is_valid(N))
                {
                    graph.at(i * N + j).push_back(next.x * N + next.y);
                    graph[next.x * N + next.y].push_back(i * N + j);
                }
            }
        }

    vector<int> depth(N * N, -1);
    graph.BFS(depth, 0);

    rep(i, 0, N)
    {
        rep(j, 0, N)
            cout << depth[i * N + j] << " ";
        cout << endl;
    }
}

void E(void)
{

}

int main(void)
{
    // A();
    // B();
    // C();
    D();
    // E();
    return 0;
}