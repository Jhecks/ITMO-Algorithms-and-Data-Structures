#include <iostream>
#include <fstream>
#include <stack>
#include <string>
 
using namespace std;
 
int OneResult(const string & left, char oper, const  string & right)
{
    int a = stoi(left);
    int b = stoi(right);
 
    if (oper == '*')
        return a * b;
    if (oper == '/')
        return a / b;
    if (oper == '+')
        return a + b;
    if (oper == '-')
        return a - b;
}
 
int Result(const string postfix)
{
    stack<string> temp;
    for (char cur : postfix)
    {
        if (isdigit(cur))
            temp.push(string(1, cur));
 
        else
            if (cur == '*' || cur == '/' || cur == '+' || cur == '-')
            {
                string right = temp.top();
                temp.pop();
                string left = temp.top();
                temp.pop();
                int res = OneResult(left, cur, right);
                temp.push(to_string(res));
            }
    }
    return  stoi(temp.top());
}
 
int main()
{
    ifstream cin("postfix.in");
    ofstream cout("postfix.out");
     
    string input;
    getline(cin, input, '\n');
    cout << Result(input) << endl;
 
    cin.close();
    cout.close();
 
}
