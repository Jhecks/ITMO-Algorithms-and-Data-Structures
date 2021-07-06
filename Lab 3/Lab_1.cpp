#include <fstream>
#include <vector>
 
using namespace std;
 
int main()
{
    ifstream fin ("isheap.in");
    ofstream fout ("isheap.out");
 
    vector <long long> heap;
    int len = 0;
    fin >> len;
    heap.resize(len+1);
    for (int i = 1; i < len+1; i++)
        fin >> heap[i];
 
    for (int i = 1; i < len/2 - 1; i++)
        if (2 * i <= len)
            if(heap[i] > heap[2 * i])
                if (2 * i + 1 <= len)
                    if (heap[i] > heap[2 * i + 1])
                    {
                        fout << "NO";
                        fin.close();
                        fout.close();
                        return 0;
                    }
 
    fout << "YES";
 
    fin.close();
    fout.close();
    return 0;
}
