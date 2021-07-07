#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
 
using namespace std;
 
class Queue
{
    const int MODULO = 65536;
 
    queue<size_t> queue;
 
public:
    size_t get()
    {
        auto result = queue.front();
        queue.pop();
        return result;
    }
 
    void put(size_t value)
    {
        queue.push((size_t)(value % MODULO));
    }
};
 
void scanLabels(vector<string> &commandList, unordered_map<string, int> &labels)
{
    for (int i = 0; i < commandList.size(); i++)
        if (commandList[i][0] == ':')
            labels[commandList[i].substr(1)] = i;
}
 
int main()
{
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);
 
    vector<string> commandList;
 
    string input;
    while (getline(cin, input))
    {
        commandList.push_back(input);
    }
 
    Queue queue;
    unordered_map<string, int> labels;
    vector<size_t> registers(26);
    scanLabels(commandList, labels);
 
    size_t x, y;
    for (int i = 0; i < commandList.size(); i++)
    {
        string command = commandList[i];
        switch (command[0])
        {
            case '+':
                x = queue.get();
                y = queue.get();
                queue.put(x + y);
                break;
            case '-':
                x = queue.get();
                y = queue.get();
                queue.put(x - y);
                break;
            case '*':
                x = queue.get();
                y = queue.get();
                queue.put(x * y);
                break;
            case '/':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x / y : 0);
                break;
            case '%':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x % y : 0);
                break;
            case '>':
                registers[command[1] - 'a'] = queue.get();
                break;
            case '<':
                queue.put(registers[command[1] - 'a']);
                break;
            case 'P':
                if (command.length() == 1)
                    cout << queue.get() << endl;
                else
                    cout << registers[command[1] - 'a'] << endl;
                break;
            case 'C':
                if (command.length() == 1)
                    cout << (unsigned char) queue.get();
                else
                    cout << (unsigned char) registers[command[1] - 'a'];
                break;
            case ':':
                break;
            case 'J':
                i = labels[command.substr(1)];
                break;
            case 'Z':
                if (registers[command[1] - 'a'] == 0)
                {
                    i = labels[command.substr(2)];
                }
                break;
            case 'E':
                if (registers[command[1] - 'a'] == registers[command[2] - 'a'])
                {
                    i = labels[command.substr(3)];
                }
                break;
            case 'G':
                if (registers[command[1] - 'a'] > registers[command[2] - 'a'])
                {
                    i = labels[command.substr(3)];
                }
                break;
            case 'Q':
                i = commandList.size();
                break;
            default:
                queue.put(atoll(command.c_str()));
                break;
        }
    }
    return 0;
}
