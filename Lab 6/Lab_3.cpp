#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
struct Value
{
    const string key;
    string value;
 
    Value * next;
    Value * linked_next;
    Value * linked_prev;
 
    explicit Value(string key, string value, Value * prev, Value * next) :
            next(nullptr), key(move(key)), value(move(value)), linked_prev(prev), linked_next(next) {}
};
 
struct MyMap
{
    const unsigned int MOD = 1000000;
    vector<Value *> table;
    Value * header;
    Value * linked_prev;
    Value * linked_next;
 
    MyMap()
    {
        linked_next = nullptr;
        linked_prev = nullptr;
        header = new Value("none", "none", nullptr, nullptr);
        header->linked_prev = header;
        header->linked_next = header;
        table.resize(MOD);
    }
 
    int hash(const string& str)
    {
        int multiplier = 265;
        int prime = 1000000000;
        unsigned long long hash = 0;
        for (int i = str.size() - 1; i >= 0; --i)
            hash = (hash * multiplier + str[i]) % prime;
        return (int)hash;
    }
 
    void put(const string &key, const string &value)
    {
        Value * x = get_value(key);
        if (x != nullptr)
        {
            x->value = value;
            return;
        }
        int h = hash(key);
        auto * node = new Value(key, value, header->linked_prev, header);
        header->linked_prev->linked_next = node;
        node->next = table[h % MOD];
        table[h % MOD] = node;
        header->linked_prev = node;
    }
 
    string next(const string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "none" : node->linked_next->value;
    }
 
    string prev(const string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "none" : node->linked_prev->value;
    }
 
    Value * get_value(const string &key)
    {
        Value * node = table[hash(key) % MOD];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }
 
    string get(const string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "none" : node->value;
    }
 
    void Delete(const string &key)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->linked_next->linked_prev = node->linked_prev;
                node->linked_prev->linked_next = node->linked_next;
                if (prev_node == nullptr)
                {
                    table[h % MOD] = node->next;
                }
                else
                {
                    prev_node->next = node->next;
                    node->next = nullptr;
                }
                return;
            }
            prev_node = node;
            node = node->next;
        }
    }
};
 
int main()
{
    ifstream cin("linkedmap.in");
    ofstream cout("linkedmap.out");
    MyMap map;
    string func;
    while (cin >> func)
    {
        string key;
        string value;
        if (func == "put")
        {
            cin >> key >> value;
            map.put(key, value);
        }
        if (func == "get")
        {
            cin >> key;
            cout << map.get(key) << endl;
        }
        if (func == "delete")
        {
            cin >> key;
            map.Delete(key);
        }
        if (func == "prev")
        {
            cin >> key;
            cout << map.prev(key) << endl;
        }
        if (func == "next")
        {
            cin >> key;
            cout << map.next(key) << endl;
        }
    }
    cin.close();
    cout.close();
    return 0;
}
