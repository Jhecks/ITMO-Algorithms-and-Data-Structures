#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
struct TreeItem
{
    int  Key;
    int LeftChild;
    int RightChild;
};
 
int TempHight = 0;
int Hight = 0;
 
void HightCounter(vector<TreeItem> &Tree, int Num)
{
    TempHight++;
    if (Tree[Num].RightChild != 0)
    {
        HightCounter(Tree, Tree[Num].RightChild);
    }
    if (Tree[Num].LeftChild != 0)
    {
        HightCounter(Tree, Tree[Num].LeftChild);
    }
    (TempHight > Hight) ? Hight = TempHight : Hight = Hight;
    TempHight--;
}
 
int main()
{
    ifstream cin("height.in");
    ofstream cout("height.out");
 
    int count = 0;
    cin >> count;
 
    vector<TreeItem> Tree;
    Tree.resize(count + 1);
 
    const int first = 1;
    if (count == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    else
    {
        for (int i = 1; i <= count; i++)
        {
            cin >> Tree[i].Key >> Tree[i].LeftChild >> Tree[i].RightChild;
        }
    }
 
    HightCounter(Tree, first);
    cout << Hight << endl;
 
    cin.close();
    cout.close();
    return 0;
}
