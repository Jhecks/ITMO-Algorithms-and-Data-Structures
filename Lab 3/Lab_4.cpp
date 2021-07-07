#include <fstream>
#include <vector>
using namespace std;
 
long n = 0;
vector<pair <long, long>> inData;
 
void siftDown(int i)
{
    int help = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && inData[left].first < inData[i].first)
        help = left;
    if (right < n && inData[right].first < inData[help].first)
        help = right;
    if (help != i)
    {
        swap(inData[i], inData[help]);
        siftDown(help);
    }
}
 
void siftUp(int i)
{
    if (i != 0)
    {
        if (inData[i].first < inData[(i - 1) / 2].first)
        {
            swap(inData[i], inData[(i - 1) / 2]);
            siftUp((i - 1) / 2);
        }
    }
}
 
int Find(int X)
{
    for (int i = 0; i < n; i++)
        if (inData[i].second == X)
            return i;
    return 0;
}
 
int main()
{
    inData.resize(1000000);
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");
 
    string Com;
    int i = 0;
    while (fin >> Com)
    {
        i++;
        if (Com.length() == 0)
            break;
        if (Com == "push")
        {
            long val;
            fin >> val;
            n++;
            inData[n - 1].first = val;
            inData[n - 1].second = i;
            siftUp(n - 1);
 
        } else
            if (Com == "extract-min")
            {
 
            if (n == 0)
                fout << "*" << endl;
            else
                {
                    fout << inData[0].first << endl;
                    swap(inData[0], inData[n - 1]);
                    n--;
                    siftDown(0);
                }
 
        } else
            if (Com == "decrease-key")
            {
                long x, y;
                fin >> x >> y;
                int j = Find(x);
                inData[j].first = y;
                if (j != 0 && inData[j].first < inData[(j - 1) / 2].first)
                    siftUp(j);
                else
                    siftDown(j);
            }
            else
                break;
    }
    return 0;
}
