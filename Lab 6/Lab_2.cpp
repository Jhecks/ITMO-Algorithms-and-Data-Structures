#include <iostream>
#include <fstream>
#include <vector>
#include <list>
 
using namespace std;
 
int Hash(const string& s)
{
    int multiplier = 265;
    int prime = 1000000000;
    unsigned long long hash = 0;
    for (int i = s.size() - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return (int)hash;
}
 
struct Tuple
{
    string key;
    string value;
};
 
struct myMap
{
    vector<list<Tuple>> m_map;
    myMap(int size) :m_map(size) {}
    void put(const Tuple & t)
    {
        string key = t.key;
        long long h = Hash(key);
        unsigned long long idx = h % m_map.size();
        list<Tuple>& tl = m_map[idx];
        auto i = tl.begin();
        for (; i != tl.end(); i++)
            if (i->key == key)
            {
                *i = t;
                break;
            }
        if (i == tl.end())
            tl.push_back(t);
    }
    void put(const string & key, string & value)
    {
        Tuple t;
        t.key = key;
        t.value = value;
        put(t);
    }
    void Delete(const string& key)
    {
        int h = Hash(key);
        int idx = h % m_map.size();
        list<Tuple>& tl = m_map[idx];
        for (auto i = tl.begin(); i != tl.end(); i++)
            if (i->key == key)
            {
                tl.erase(i);
                break;
            }
    }
    string get(const string& key)
    {
        int h = Hash(key);
        int idx = h % m_map.size();
        list<Tuple>& tl = m_map[idx];
        for (auto & i : tl)
            if (i.key == key)
                return i.value;
        return "none";
    }
};
 
int main()
{
    ifstream cin("map.in");
    ofstream cout("map.out");
    myMap map(10000);
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
    }
    cin.close();
    cout.close();
    return 0;
}
