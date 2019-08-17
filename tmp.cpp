#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 101;
int Tree[N];
int find_root (int x)
{
    if (Tree[x] == -1) return x;
    else 
    {
        int root = find_root(Tree[x]);
        Tree[x] = root;
        return root;
    }
}

struct Edge
{
    int a, b;
    int weight;
    bool operator < (const Edge& B) const
    {
        return weight < B.weight;
    }
};

int main ()
{
    int n;
    while (scanf("%d", &n) != EOF && n) 
    {
        vector<Edge> edges;         // notice vector start from 0, so use i-1, i base from 1
        for (int i = 1; i <= n*(n-1)/2; i++) 
        {
            Edge edge;
            scanf("%d%d%d", &edge.a, &edge.b, &edge.weight);
            edges.push_back(edge);
        }
        sort(edges.begin(), edges.end());
        for (int i = 1; i <= N; i++) Tree[i] = -1;

        int res = 0;
        for (int i = 1; i <= n*(n-1)/2; i++) 
        {
            int a = find_root(edges[i-1].a);
            int b = find_root(edges[i-1].b);
            if (a != b)
            {
                Tree[a] = b;
                res += edges[i-1].weight;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}