#include <iostream>
#include <fstream>
#include <list>
 
using namespace std;
 
int main()
{
    ifstream cin("queue.in");
    ofstream cout("queue.out");
    list <int> Queue;
    int count = 0;
    cin >> count;
    char oper;
    int value;
    for (int i = 0; i < count; i++)
    {
        cin >> oper;
        if (oper == '-')
        {
            cout << Queue.front() << endl;
            Queue.pop_front();
        }
        else
        {
            cin >> value;
            Queue.push_back(value);
        }
    }
 
    cin.close();
    cout.close();
    return 0;
}
