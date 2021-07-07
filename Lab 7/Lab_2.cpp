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
 
    TreeItem(int key, TreeItem * left, TreeItem * right, int num) : key(key), height(0), inp_num(num)
    {
        children[0] = left;
        children[1] = right;
    }
 
    TreeItem(TreeItemInput * node, int num) : height(0), key(node->key), inp_num(num)
    {
        children[0] = children[1] = nullptr;
    }
};
 
struct Tree
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
            {
                v->children[i] = nullptr;
            }
            else
            {
                v->children[i] = new TreeItem(input_tree[input_tree[v->inp_num]->children[i]], input_tree[v->inp_num]->children[i]);
                MakeDfs(v->children[i]);
            }
        }
    }
 
    static int BalanceCount(TreeItem * v)
    {
        return (v->children[1] != nullptr ? v->children[1]->height : 0) -
               (v->children[0] != nullptr ? v->children[0]->height : 0);
    }
 
    void HeightCount()
    {
        if (input_tree.empty())
        {
            return ;
        }
 
        dfs(root);
    }
 
    static void HeightFix(TreeItem * v)
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
        {
            if (child != nullptr)
            {
                dfs(child);
            }
        }
        HeightFix(v);
    }
 
    static TreeItem *rotate(TreeItem *v, int side)
    {
        TreeItem * u = v->children[side == Side::left ? 1 : 0];
        v->children[side == Side::left ? 1 : 0] = u->children[side == Side::left ? 0 : 1];
        u->children[side == Side::left ? 0 : 1] = v;
        HeightFix(v);
        HeightFix(u);
        return u;
    }
 
    static TreeItem *balance(TreeItem* v)
    {
        if (BalanceCount(v->children[1]) < 0)
            v->children[1] = rotate(v->children[1], Side::right);
        return rotate(v, Side::left);
    }
 
    void TreeOutput()
    {
        queue<TreeItem *> queue;
        queue.push(root);
        int num = 1;
        while (!queue.empty())
        {
            TreeItem *v = queue.front();
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
};
 
int main()
{
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);
 
    size_t n;
    cin >> n;
    auto avl = new Tree();
 
    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        cin >> key >> left >> right;
        avl->input_tree.push_back(new TreeItemInput(key, left-1, right-1));
    }
 
    avl->TreeMake();
 
    avl->HeightCount();
    avl->root = Tree::balance(avl->root);
 
    avl->TreeOutput();
 
    cout << n << endl;
    for (auto v : avl->output_tree)
        cout << v->key << " " << v->children[0] << " " << v->children[1] << endl;
}
