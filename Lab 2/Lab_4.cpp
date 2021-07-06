#include<iostream>
#include<fstream>
#include<vector>
 
using namespace std;
 
int main()
{
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
 
    vector<int> arr;
    int len = 0;
 
    fin >> len;
    arr.resize(len);
 
    for (int i = 0; i < len; i++)
    {
        arr[i] = i + 1;
        swap(arr[i], arr[i/2]);
    }
 
    for (int i = 0; i < len; i++)
        fout << arr[i] << ' ';
 
    fin.close();
    fout.close();
    return 0;
}
