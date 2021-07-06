#include <iostream>
#include <fstream>
#include <string>
#include <stack>
 
using namespace std;
 
bool CheckBracket(string str)
{
    stack<char> temp;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(' || str[i] == '[')
            temp.push(str[i]);
        else
        if (str[i] == ')')
            if (temp.size() != 0)
                if (temp.top() == '(')
                    temp.pop();
                else
                    return false;
            else
                return false;
        else
        if (str[i] == ']')
            if (temp.size() != 0)
                if (temp.top() == '[')
                    temp.pop();
                else
                    return false;
            else
                return false;
    }
    if (temp.size() != 0)
        return false;
}
 
int main()
{
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");
     
    string input;
 
    for (int i = 0; i < 500; i++)
    {
        getline(fin, input);
        if (!input.empty())
            CheckBracket(input) ? fout << "YES" << endl : fout << "NO" << endl;
        else
            return 0;
    }
     
    fin.close();
    fout.close();
    return 0;
}
