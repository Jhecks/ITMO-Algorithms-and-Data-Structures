#include <iostream>
#include <fstream>
#include <iomanip>
 
using namespace std;
 
int main()
{
    ifstream cin("garland.in");
    ofstream cout("garland.out");
    int n = 0;
    double Height = 0;
    cin >> n >> Height;
    double Lower = 0;
    double Top = Height;
    double Finish = -1;
    while ((Top - Lower) > 0.005 / (n - 1))
    {
        double Medium = (Top + Lower) / 2;
        double Previous = Height;
        double Current = Medium;
        bool CheckHeight = Current > 0;
        for (int i = 3; i <= n; i++)
        {
            double Next = 2 * Current - Previous + 2;
            CheckHeight &= Next > 0;
            Previous = Current;
            Current = Next;
        }
        if (CheckHeight)
        {
            Top = Medium;
            Finish = Current;
        }
        else
            Lower = Medium;
    }
    cout << fixed;
    cout << setprecision(2);
    cout << Finish << endl;
  
    cin.close();
    cout.close();
    return 0;
}
