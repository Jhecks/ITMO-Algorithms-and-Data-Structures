#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
 
using namespace std;
 
struct Edge {
    int from;
    int to;
    long long weight;
 
    Edge(int from_, int to_, long long weight_) : from(from_), to(to_), weight(weight_) {
 
    }
};
 
vector < Edge > Graph;
vector < long long > MinDistance;
int VertexNum, EdgeNum, StartVertex;
const long long INF = 5 * pow(10, 18) + 931;
 
void BuildGraph() {
    cin >> VertexNum >> EdgeNum >> StartVertex;
    StartVertex--;
 
    MinDistance.resize(VertexNum, LLONG_MAX);
    MinDistance[StartVertex] = 0;
 
    for (int i = 0; i < EdgeNum; i++) {
        int v1, v2;
        long long w;
        cin >> v1 >> v2 >> w;
        v1--; v2--;
        Graph.push_back(Edge(v1, v2, w));
    }
}
 
void BellmanFord() {
    for (int i = 0; i < VertexNum - 1; i++) {
        for (int j = 0; j < EdgeNum; j++) {
            if (MinDistance[Graph[j].from] != LLONG_MAX) {
                MinDistance[Graph[j].to] = min(MinDistance[Graph[j].to], MinDistance[Graph[j].from] + Graph[j].weight);
            }
        }
    }
}
 
void BellmanFordCycleCheck() {
    for (int i = 0; i < VertexNum - 1; i++) {
        for (int j = 0; j < EdgeNum; j++) {
            if (MinDistance[Graph[j].from] != LLONG_MAX) {
                if (MinDistance[Graph[j].to] > MinDistance[Graph[j].from] + Graph[j].weight) {
                    MinDistance[Graph[j].to] = -INF;
                }
            }
        }
    }
}
 
void PrintResult() {
    for (long long i : MinDistance) {
        if (i <= -INF) {
            cout << '-' << '\n';
        }
        else if (i == LLONG_MAX) {
            cout << '*' << '\n';
        }
        else {
            cout << i << '\n';
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
 
    BuildGraph();
    BellmanFord();
    BellmanFordCycleCheck();
    PrintResult();
 
    return 0;
}
