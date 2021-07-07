#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
struct item
{
    int k = 0;
    item* l = nullptr;
    item* r = nullptr;
};
 
void treeInsert(vector<item*>& v, item** _top, item* k)
{
    item* here = (*_top);
    if (k->k < here->k)
    {
        here = here->l;
        if (here)
            treeInsert(v, &((*_top)->l), k);
        else
        {
            (*_top)->l = k;
            v.push_back(k);
            return;
        }
    }
    else
        if (k->k > here->k)
        {
            here = here->r;
            if (here)
                treeInsert(v, &((*_top)->r), k);
            else
            {
                (*_top)->r = k;
                v.push_back(k);
                return;
            }
        }
        else
            (*_top)->k = k->k;
}
 
void treeDelete(vector<item*>& v, item** _top, item** last, int k, item** invariant)
{
    item* here = (*_top);
    if (k == here->k)
    {
        if (last != nullptr && (*last)->l && (*last)->l->k == k) (*last)->l = nullptr;
        if (last != nullptr && (*last)->r && (*last)->r->k == k) (*last)->r = nullptr;
        if (last == nullptr)
        {
            if ((*invariant)->r)
            {
                if ((*invariant)->l) treeInsert(v, &((*invariant)->r), (*invariant)->l);
                *invariant = (*invariant)->r;
            }
            else
            {
                *invariant = (*invariant)->l;
                return;
            }
        }
        else
        {
            if (here->r) treeInsert(v, invariant, here->r);
            if (here->l) treeInsert(v, invariant, here->l);
        }
        return;
    }
    else
        if (k < here->k)
        {
            if (here->l)
                treeDelete(v, &((*_top)->l), _top, k, invariant);
            return;
        }
        else
            if (k > here->k)
            {
                if (here->r)
                    treeDelete(v, &((*_top)->r), _top,  k, invariant);
                return;
            }
}
 
bool treeExists(vector<item*>& v, item** _top, int k)
{
    item* here = (*_top);
    if (here)
    {
        if (here->k == k)
            return true;
        else
            if (k < here->k)
            {
                if (here->l)
                    return treeExists(v, &((*_top)->l), k);
                return false;
            }
            else
                if (k > here->k)
                {
                    if (here->r)
                        return treeExists(v, &((*_top)->r), k);
                    return false;
                }
    }
    return false;
}
 
void treePrev(item* top, int k, int best)
{
    if (top->k >= k)
    {
        if (top->l)
        {
            treePrev(top->l, k, best);
            return;
        }
        else
        {
            if (best > INT_MIN) cout << best << '\n';
            else cout << "none" << '\n';
        }
    }
    else
    {
        if (best < top->k) best = top->k;
        if (top->r && (best > INT_MIN && k - best > 1))
        {
            treePrev(top->r, k, best);
            return;
        }
        else
        {
            if (best > INT_MIN) cout << best << '\n';
            else cout << "none" << '\n';
        }
    }
}
 
void treeNext(item* top, int k, int best)
{
    if (top->k <= k)
    {
        if (top->r)
        {
            treeNext(top->r, k, best);
            return;
        }
        else
        {
            if (best < INT_MAX) cout << best << '\n';
            else cout << "none" << '\n';
        }
    }
    else
    {
        if (best > top->k) best = top->k;
        if (top->l && (best < INT_MAX && best - k > 1))
        {
            treeNext(top->l, k, best);
            return;
        }
        else
        {
            if (best < INT_MAX) cout << best << '\n';
            else cout << "none" << '\n';
        }
    }
}
 
void show(const vector<item*>& v, item* top)
{
    cout << "top: " << top->k << endl << endl;
    for (auto & i : v)
    {
        cout << "k: " << i->k << endl;
        if (i->l)
            cout << " l: " << i->l->k;
        else
            cout << " NO";
        if (i->r)
            cout << " r: " << i->r->k << endl;
        else
            cout << " NO" << endl;
    }
}
 
int main()
{
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);
    item* top = nullptr;
    vector<item*> v;
    string command;
    int k;
 
    while (cin >> command)
    {
        cin >> k;
        switch (command[0])
        {
            case 'i':
            {
                if (top)
                {
                    item* new_item = new item();
                    new_item->k = k;
                    treeInsert(v, &top, new_item);
                }
                else
                {
                    top = new item();
                    top->k = k;
                    v.push_back(top);
                }
                break;
            }
            case 'd':
            {
                if (top)
                    treeDelete(v, &top, nullptr, k, &top);
                break;
            }
            case 'e':
            {
                if (top)
                {
                    if (treeExists(v, &top, k)) cout << "true" << '\n';
                    else cout << "false" << '\n';
                }
                else cout << "false" << '\n';
                break;
            }
            case 'p':
            {
                if (top) treePrev(top, k, INT_MIN);
                else cout << "none" << '\n';
                break;
            }
            case 'n':
            {
                if (top) treeNext(top, k, INT_MAX);
                else cout << "none" << '\n';
                break;
            }
            case 's':
                show(v, top);
        }
    }
    return 0;
}
