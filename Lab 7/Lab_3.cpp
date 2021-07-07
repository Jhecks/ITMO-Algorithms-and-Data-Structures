#include <vector>
#include <queue>
#include <iostream>
 
enum Side {right=0, left=1};
 
using namespace std;
 
struct TreeItemInput
{
    int key;
    int children[2]{};
 
    TreeItemInput(int key, int left, int right) : key(key)
    {
        children[0] = left;
        children[1] = right;
    }
};
 
struct TreeItem
{
    int key;
    int height;
    int inp_num;
    TreeItem* children[2]{};
 
    TreeItem(int key, TreeItem * left, TreeItem * right, int num) : key(key), height(1), inp_num(num)
    {
        children[0] = left;
        children[1] = right;
    }
 
    TreeItem(TreeItemInput * node, int num) : height(1), key(node->key), inp_num(num)
    {
        children[0] = children[1] = nullptr;
    }
};
 
struct AVL_Tree
{
    vector<TreeItemInput *> input_tree;
    vector<TreeItemInput *> output_tree;
    TreeItem * root = nullptr;
 
    void TreeMake()
    {
        root = new TreeItem(input_tree[0], 0);
        MakeDfs(root);
    }
 
    void MakeDfs(TreeItem * v)
    {
        for (int i = 0; i < 2; i++)
        {
            if (input_tree[v->inp_num]->children[i] == -1)
                v->children[i] = nullptr;
            else
            {
                v->children[i] =
                        new TreeItem(input_tree[input_tree[v->inp_num]->children[i]], input_tree[v->inp_num]->children[i]);
                MakeDfs(v->children[i]);
            }
        }
    }
 
    static int BalanceCount(TreeItem * v)
    {
        return (v->children[1] != nullptr ? v->children[1]->height : 0) - (v->children[0] != nullptr ? v->children[0]->height : 0);
    }
 
    void HeightCount()
    {
        if (input_tree.empty())
            return;
        dfs(root);
    }
 
    static void fix_height(TreeItem * v)
    {
        v->height = max(LeftHeight(v), RightHeight(v)) + 1;
    }
 
    static int RightHeight(TreeItem * v)
    {
        return v->children[1] == nullptr ? 0 : v->children[1]->height;
    }
 
    static int LeftHeight(TreeItem * v)
    {
        return v->children[0] == nullptr ? 0 : v->children[0]->height;
    }
 
    void dfs(TreeItem * v)
    {
        for (auto child : v->children)
            if (child != nullptr)
                dfs(child);
        fix_height(v);
    }
 
    TreeItem *rotate(TreeItem *v, int side)
    {
        TreeItem * u = v->children[side == Side::left ? 1 : 0];
        v->children[side == Side::left ? 1 : 0] = u->children[side == Side::left ? 0 : 1];
        u->children[side == Side::left ? 0 : 1] = v;
        fix_height(v);
        fix_height(u);
        return u;
    }
 
    TreeItem *balance(TreeItem *v)
    {
        fix_height(v);
        if (BalanceCount(v) > 1)
        {
            if (BalanceCount(v->children[1]) < 0)
                v->children[1] = rotate(v->children[1], Side::right);
            return rotate(v, Side::left);
        }
        if (BalanceCount(v) < -1)
        {
            if (BalanceCount(v->children[0]) > 0)
                v->children[0] = rotate(v->children[0], Side::left);
            return rotate(v, Side::right);
        }
        return v;
    }
 
    void TreeOutput()
    {
        queue<TreeItem *> queue;
        queue.push(root);
        int num = 1;
        while (!queue.empty())
        {
            TreeItem * v = queue.front();
            queue.pop();
            int children_num[2] = {0, 0};
            for (int i = 0; i < 2; i++)
            {
                if (v->children[i] != nullptr)
                {
                    queue.push(v->children[i]);
                    children_num[i] = ++num;
                }
            }
            output_tree.push_back(new TreeItemInput(v->key, children_num[0], children_num[1]));
        }
    }
 
    TreeItem * insert(TreeItem * root, int key)
    {
        if (root == nullptr)
            return new TreeItem(key, nullptr, nullptr, static_cast<int>(input_tree.size()+1));
        root->children[key < root->key ? 0 : 1] = insert(root->children[key < root->key ? 0 : 1], key);
        return balance(root);
    }
};
 
int main()
{
    freopen("addition.in", "r", stdin);
    freopen("addition.out", "w", stdout);
 
    size_t n;
    cin >> n;
    auto avl = new AVL_Tree();
 
    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        cin >> key >> left >> right;
        avl->input_tree.push_back(new TreeItemInput(key, left-1, right-1));
    }
 
    int key;
    cin >> key;
 
    if (n == 0)
    {
        cout << 1 << "\n" << key << " " << 0 << " " << 0 << endl;
        return 0;
    }
 
    avl->TreeMake();
    avl->HeightCount();
    avl->root = avl->insert(avl->root, key);
    avl->TreeOutput();
 
    cout << n + 1 << endl;
    for (auto v : avl->output_tree)
        cout << v->key << " " << v->children[0] << " " << v->children[1] << endl;
}
