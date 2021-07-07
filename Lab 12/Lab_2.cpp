#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 
#define MAX INT_MAX
 
using namespace std;
 
vector <int> arr;
vector <int> indexes;
vector <int> temp;
vector <int> pos;
vector <int> result;
 
void input()
{
    int num;
    cin >> num;
 
    arr.resize(num);
    indexes.assign(num + 1, MAX);
    temp.assign(num, 0);
    pos.assign(num + 1, 0);
 
    for (int i = 0; i < num; i++)
        cin >> arr[i];
}
 
void counter()
{
    indexes[0] = -MAX;
    pos[0] = -1;
    int length = indexes[0];
 
    for (int i = 0; i < arr.size(); i++)
    {
        int j = int(upper_bound(indexes.begin(), indexes.end(), arr[i]) - indexes.begin());
        if ((indexes[j - 1] < arr[i]) && (arr[i] < indexes[j]))
        {
            indexes[j] = arr[i];
            temp[i] = pos[j - 1];
            pos[j] = i;
            length = max(length, j);
        }
    }
 
    int newP = pos[length];
 
    while (newP != -1)
    {
        result.push_back(arr[newP]);
        newP = temp[newP];
    }
    reverse(result.begin(), result.end());
}
 
void print()
{
    cout << result.size() << "\n";
    for (auto i : result)
        cout << i << " ";
}
 
int main()
{
    input();
    counter();
    print();
}
