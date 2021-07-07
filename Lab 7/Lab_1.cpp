#include <vector>
#include <fstream>
#include <algorithm>
 
using namespace std;
 
struct TreeItem
{
    long value;
    int left;
    int right;
    int balance;
    int hight;
};
 
 
class Tree
{
    vector<TreeItem> tree;
 
public:
    explicit Tree(int size)
    {
        tree.resize(size);
    }
    TreeItem& Item(int i)
    {
        return tree[i];
    }
    TreeItem& Root()
    {
        return tree[0];
    }
    TreeItem& Left(TreeItem& parent)
    {
        return tree[parent.left-1];
    }
    TreeItem& right(TreeItem& parent)
    {
        return tree[parent.right-1];
    }
};
 
int BranchLen(Tree& tree, TreeItem& item)
{
    int lh = 0, rh = 0;
    if (item.left)
        lh = BranchLen(tree, tree.Left(item));
    if (item.right)
        rh = BranchLen(tree, tree.right(item));
    item.hight = max(lh, rh) + 1;
    item.balance = rh - lh;
 
    return item.hight;
}
 
 
void CountLen(Tree& tree)
{
    BranchLen(tree, tree.Root());
}
 
int main()
{
    ifstream cin("balance.in");
    ofstream cout("balance.out");
    int len = 0;
    cin >> len;
    Tree tree(len);
 
    for (int i = 0; i < len; i++)
    {
        TreeItem& item = tree.Item(i);
        cin >> item.value >> item.left >> item.right;
    }
 
    CountLen(tree);
 
    for (int i = 0; i < len; i++)
        cout << tree.Item(i).balance << endl;
 
    cin.close();
    cout.close();
 
    return 0;
}
