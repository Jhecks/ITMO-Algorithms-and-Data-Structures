#include <iostream>
#include <vector>
#include <fstream>
 
#define MOD 100000
 
using namespace std;
 
struct Node
{
    string key;
    Node* children[2]{};
    explicit Node(string key) : key(move(key))
    {
        children[0] = children[1] = nullptr;
    }
 
    ~Node()
    {
        delete children[0];
        delete children[1];
    }
};
 
struct Tree
{
    Node* root = nullptr;
    int size = 0;
    Node* search(Node* node, string &key)
    {
        if (node == nullptr || node->key == key)
        {
            return node;
        }
        return search(node->children[((key < node->key) ? 0 : 1)], key);
    }
 
    Node* insert(Node* node, string &key)
    {
        if (node == nullptr)
        {
            return new Node(key);
        }
        node->children[((key < node->key) ? 0 : 1)] =
                insert(node->children[((key < node->key) ? 0 : 1)], key);
        return node;
    }
 
    static int children_count(Node* node)
    {
        int count = 0;
        for (auto & i : node->children)
        {
            if (i != nullptr)
            {
                count++;
            }
        }
        return count;
    }
 
    Node* remove(Node* node, string &key)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (node->key != key)
        {
            node->children[((key < node->key) ? 0 : 1)] =
                    remove(node->children[((key < node->key) ? 0 : 1)], key);
        }
        else
        {
            int count = children_count(node);
            if (count < 2)
            {
                node = node->children[((node->children[0] != nullptr) ? 0 : 1)];
            }
            else
            {
                Node* min_from_right_subtree = minimum(node->children[1]);
                node->key = min_from_right_subtree->key;
                node->children[1] = remove(node->children[1], node->key);
            }
        }
        return node;
    }
 
    Node* minimum(Node* node)
    {
        if (node->children[0] == nullptr)
        {
            return node;
        }
        return minimum(node->children[0]);
    }
 
    vector<string> trav;
 
    void make_trav(Node * v)
    {
        if (v == nullptr)
        {
            return;
        }
        make_trav(v->children[0]);
        trav.push_back(v->key);
        make_trav(v->children[1]);
    }
 
    void insert(string &key)
    {
        if (!exists(key))
        {
            root = insert(root, key);
            size++;
        }
    }
 
    bool exists(string &key)
    {
        return search(root, key) != nullptr;
    }
 
    void remove(string &key)
    {
        if (exists(key))
        {
            root = remove(root, key);
            size--;
        }
    }
 
    int get_size() const
    {
        return size;
    }
 
    vector<string> traversal()
    {
        trav.resize(0);
        make_trav(root);
        return trav;
    }
 
    ~Tree()
    {
        delete root;
    }
};
 
struct Value
{
    const string key;
    Tree * tree;
    Value * next;
    explicit Value(string key, string value) : next(nullptr), key(std::move(key))
    {
        tree = new Tree();
        tree->insert(value);
    }
};
 
struct myMap
{
    vector<Value *> table;
    myMap()
    {
        table.resize(MOD);
    }
 
    static int hash(const string& s)
    {
        int multiplier = 265;
        int prime = 1000000000;
        unsigned long long hash = 0;
        for (int i = s.size() - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return static_cast<int> (hash);
    }
 
    void put(const string &key, string &value)
    {
        Value * x = getValue(key);
        if (x != nullptr)
        {
            x->tree->insert(value);
            return;
        }
        int h = hash(key);
        auto * node = new Value(key, value);
        node->next = table[h % MOD];
        table[h % MOD] = node;
    }
 
    Value * getValue(const string &key)
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
 
    vector<string> get(const string &key)
    {
        Value * node = getValue(key);
        if (node == nullptr)
        {
            return vector<string>();
        }
        return node->tree->traversal();
    }
 
    void Delete(const string &key, string &value)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->tree->remove(value);
                if (node->tree->get_size() == 0)
                {
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
            }
            prev_node = node;
            node = node->next;
        }
    }
 
    void DeleteAll(const string &key)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                if (prev_node == nullptr)
                    table[h % MOD] = node->next;
                else
                {
                    prev_node->next = node->next;
                    delete node->tree;
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
    ifstream cin("multimap.in");
    ofstream cout("multimap.out");
    myMap map;
    string func;
    while (cin >> func)
    {
        string value;
        string key;
        if (func == "put")
        {
            cin >> key >> value;
            map.put(key, value);
        }
        if (func == "delete")
        {
            cin >> key >> value;
            map.Delete(key, value);
        }
        if (func == "deleteall")
        {
            cin >> key;
            map.DeleteAll(key);
        }
        if (func == "get")
        {
            cin >> key;
            vector<string> vector = map.get(key);
            cout << vector.size();
            for (const string& s : vector)
            {
                cout << " " << s;
            }
            cout << endl;
        }
    }
    cin.close();
    cout.close();
    return 0;
}
