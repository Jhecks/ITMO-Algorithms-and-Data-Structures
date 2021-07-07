#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
 
enum Side {right=0, left=1};
 
using namespace std;
 
struct TreeItem
{
    int key;
    int height;
    TreeItem* children[2]{};
 
    TreeItem(int key, TreeItem * left, TreeItem * right) : key(key), height(1)
    {
        children[0] = left;
        children[1] = right;
    }
};
 
struct Tree
{
    TreeItem * root = nullptr;
 
    static int count_balance(TreeItem * v)
    {
        if (v == nullptr)
            return 0;
        return (v->children[1] != nullptr ? v->children[1]->height : 0) - (v->children[0] != nullptr ? v->children[0]->height : 0);
    }
 
    static void fix_height(TreeItem * v)
    {
        v->height = max(height_left(v), height_right(v)) + 1;
    }
 
    static int height_right(TreeItem * v)
    {
        return v->children[1] == nullptr ? 0 : v->children[1]->height;
    }
 
    static int height_left(TreeItem * v)
    {
        return v->children[0] == nullptr ? 0 : v->children[0]->height;
    }
 
    TreeItem *rotate(TreeItem * v, int side)
    {
        TreeItem * u = v->children[side == Side::left ? 1 : 0];
        v->children[side == Side::left ? 1 : 0] = u->children[side == Side::left ? 0 : 1];
        u->children[side == Side::left ? 0 : 1] = v;
        fix_height(v);
        fix_height(u);
        return u;
    }
 
    TreeItem *balance(TreeItem * v)
    {
        fix_height(v);
        if (count_balance(v) > 1)
        {
 
            if (count_balance(v->children[1]) < 0)
            {
                v->children[1] = rotate(v->children[1], Side::right);
            }
            return rotate(v, Side::left);
        }
        if (count_balance(v) < -1)
        {
            if (count_balance(v->children[0]) > 0)
            {
                v->children[0] = rotate(v->children[0], Side::left);
            }
            return rotate(v, Side::right);
        }
        return v;
    }
 
    TreeItem *insert(TreeItem *root, int key)
    {
        if (root == nullptr)
            return new TreeItem(key, nullptr, nullptr);
        root->children[key < root->key ? 0 : 1] = insert(root->children[key < root->key ? 0 : 1], key);
        return balance(root);
    }
 
    TreeItem *MaxFind(TreeItem *root)
    {
        return root->children[1] == nullptr ? root : MaxFind(root->children[1]);
    }
 
    TreeItem *remove(TreeItem * root, int key)
    {
        if (root == nullptr)
            return nullptr;
        if (key != root->key)
            root->children[key < root->key ? 0 : 1] = remove(root->children[key < root->key ? 0 : 1], key);
        else
        {
            if (root->children[0] == nullptr && root->children[1] == nullptr)
                return nullptr;
            if (root->children[0] == nullptr)
            {
                root = root->children[1];
                return balance(root);
            }
            TreeItem * r = MaxFind(root->children[0]);
            root->key = r->key;
            root->children[0] = remove(root->children[0],r->key);
        }
        return balance(root);
    }
 
    TreeItem *search(TreeItem * root, int key)
    {
        if (root == nullptr || key == root->key)
            return root;
        return search(root->children[key < root->key ? 0 : 1], key);
    }
};
 
int main()
{
    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);
 
    size_t n;
    cin >> n;
    auto avl = new Tree();
 
    for (int i = 0; i < n; i++)
    {
        char cmd;
        int key;
        cin >> cmd >> key;
        switch (cmd)
        {
            case 'A':
            {
                if (avl->search(avl->root, key) == nullptr)
                {
                    avl->root = avl->insert(avl->root, key);
                }
                cout << avl->count_balance(avl->root) << endl;
                break;
            }
            case 'D':
            {
                if (avl->search(avl->root, key) != nullptr)
                {
                    avl->root = avl->remove(avl->root, key);
                }
                cout << avl->count_balance(avl->root) << endl;
                break;
            }
            case 'C':
                cout << ((avl->search(avl->root, key) != nullptr) ? "Y" : "N") << endl;
                break;
            default:
                break;
        }
    }
}
