#include <fstream>
  
using namespace std;
  
int main()
{
    ifstream cin("stack.in");
    ofstream cout("stack.out");
    long long a[100000];
    int TempInd = -1;
    int Count = 0;
    char Sign;
  
    cin >> Count;
  
    for (int i = 0; i < Count; i++)
    {
        cin >> Sign;
        if (Sign == '+')
        {
            cin >> a[++TempInd];
        }
        else
            cout << a[TempInd--] << endl;
    }
    cin.close();
    cout.close();
    return 0;
}
