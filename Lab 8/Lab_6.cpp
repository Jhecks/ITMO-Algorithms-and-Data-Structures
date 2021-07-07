#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
 
void buildGraph()
{
 
}
 
void BFS(vector<vector<int>>& g, vector<bool>& used, vector<int>& ways, queue<int>& top, vector<int>& pred) {
    int here = top.front();
    top.pop();
    for (size_t i = 0; i < g[here].size(); i++)
    {
        if (used[g[here][i]] == 0)
        {
            used[g[here][i]] = 1;
            ways[g[here][i]] = ways[here] + 1;
            pred[g[here][i]] = here;
            top.push(g[here][i]);
        }
    }
}
 
void pathDefine(vector <bool> &used, int finish, vector <int> pred, int columns, ofstream &fout)
{
    if (!used[finish])
        fout << -1;
    else {
        vector<int> path;
        for (int i = finish; i != -1; i = pred[i])
            path.push_back(i);
        fout<< path.size() - 1 << endl;
        int size = path.size() - 1;
        int last = path[size];
        int diff;
        for (int i = size; i >= 0; i--) {
            diff = path[i] - last;
            if (diff == 1)fout << 'R';
            else if (diff == -1)fout << 'L';
            else if (diff == (columns + 1))fout << 'D';
            else if (diff == -(columns + 1))fout << 'U';
            last = path[i];
        }
    }
}
 
int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int strings, clumns;
    char symbol;
    fin >> strings >> clumns;
    if (strings * clumns < 2)
    {
        fout << -1;
        return 0;
    }
    vector <vector <bool>> arr(strings, vector <bool>(clumns, 0));
    int Sx, Sy, Fx, Fy;
    for (size_t i = 0; i < strings; i++) {
        for (size_t j = 0; j < clumns; j++) {
            fin >> symbol;
            if (symbol == '.') {
                arr[i][j] = 1;
            }
            else if (symbol == '#') {
                arr[i][j] = 0;
            }
            else if (symbol == 'S') {
                Sx = i;
                Sy = j;
                arr[i][j] = 1;
            }
            else if (symbol == 'T') {
                Fx = i;
                Fy = j;
                arr[i][j] = 1;
            }
        }
    }
 
    int N = strings * (clumns + 1);
    vector < vector <int> > g(N);
    vector <int> ways(N);
    vector <int> pred(N);
    queue <int> top;
    vector <bool> used(N, 0);
    for (int i = 0; i < strings; i++) {
        for (int j = 0; j < clumns; j++) {
            if (arr[i][j]) {
                if (i > 0 && arr[i - 1][j]) {
                    g[i * (clumns + 1) + j].push_back((i - 1) * (clumns + 1) + j);
                }
                if (j > 0 && arr[i][j - 1]) {
                    g[i * (clumns + 1) + j].push_back(i * (clumns + 1) + (j - 1));
                }
                if (i < (strings - 1) && arr[i + 1][j]) {
                    g[i * (clumns + 1) + j].push_back((i + 1) * (clumns + 1) + j);
                }
                if (j < (clumns - 1) && arr[i][j + 1]) {
                    g[i * (clumns + 1) + j].push_back(i * (clumns + 1) + (j + 1));
                }
            }
        }
    }
    arr.clear();
 
    int start = Sx * (clumns + 1) + Sy;
    int finish = Fx * (clumns + 1) + Fy;
    used[start] = 1;
    ways[start] = 0;
    pred[start] = -1;
    for (size_t i = 0; i < g[start].size(); i++) {
        if (used[g[start][i]] == 0) {
            used[g[start][i]] = 1;
            ways[g[start][i]] = ways[start] + 1;
            pred[g[start][i]] = start;
            top.push(g[start][i]);
        }
    }
    while (top.size() > 0 && !used[finish]) {
        BFS(g, used, ways, top, pred);
    }
 
    pathDefine(used, finish, pred, clumns, fout);
 
    return 0;
}
