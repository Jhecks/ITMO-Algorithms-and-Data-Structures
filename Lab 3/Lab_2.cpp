#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
vector<int> Heap;
 
void Colibration(int n, int i)
{
    int Largest = i;
    int l = 2 * i;
    int r = 2 * i + 1;
 
    if (l < n && Heap[l] > Heap[Largest])
        Largest = l;
 
    if (r < n && Heap[r] > Heap[Largest])
        Largest = r;
 
    if (Largest != i)
    {
        swap(Heap[i], Heap[Largest]);
        Colibration(n, Largest);
    }
}
 
void HeapSort(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Colibration(n, i);
 
    for (int i = n - 1; i >= 0; i--)
    {
        swap(Heap[0], Heap[i]);
        Colibration(i, 0);
    }
}
 
int main()
{
    ifstream cin("sort.in");
    ofstream cout("sort.out");
 
    int Size = 0;
    cin >> Size;
 
    Heap.resize(Size);
 
    for (int i = 0; i < Size; i++)
        cin >> Heap[i];
 
    HeapSort(Size);
 
    for (int i = 0; i < Size; ++i)
        cout << Heap[i] << " ";
    cout << endl;
 
    cin.close();
    cout.close();
    return 0;
}
