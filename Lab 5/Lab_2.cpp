#include <iostream>
#include <vector>
 
using namespace std;
 
struct item
{
    int k = 0;
    item* l = nullptr;
    item* r = nullptr;
};
 
item* findroot(item* node, vector<item*> v)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i]->l == node || v[i]->r == node)
            return findroot(v[i], v);
    return node;
}
 
void check(item* root, int low, int high, bool &flag)
{
    if (root == nullptr || !flag)
        return;
 
    if (high != INT_MAX && root->k >= high)
    {
        flag = false;
        return;
    }
 
    if (low != INT_MAX && root->k <= low)
    {
        flag = false;
        return;
    }
    check(root->r, root->k, high, flag);
    check(root->l, low, root->k, flag);
}
 
int main()
{
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
 
    bool flag = true;
    int n;
    cin >> n;
    int left, right;
    vector<item*> v(n);
    for (int i = 0; i < n; i++)
        v[i] = new item();
 
    for (int i = 0; i < n; i++)
    {
        cin >> v[i]->k >> left >> right;
        if (left) v[i]->l = v[left - 1];
        if (right) v[i]->r = v[right - 1];
    }
    if (n)
    {
        item* root = findroot(v[0], v);
        check(root, INT_MAX, INT_MAX, flag);
        if (v.empty() || v.size() == 1 || flag)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
    else
        cout << "YES" << '\n';
    return 0;
}
