#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
vector <unsigned long long> Power;
vector <unsigned long long> PrefixHash;
vector <int> InIndex;
string Substring, String;
unsigned long long SubstringHash = 0;
int PrimeNumber = 101;
 
void InputStrings()
{
    cin >> Substring >> String;
    if (String.size() < Substring.size())
    {
        cout << 0;
        exit(0);
    }
}
 
void PrefixHashCalculation()
{
    Power.resize(String.size());
    PrefixHash.resize(String.size());
    Power[0] = 1;
    PrefixHash[0] = String[0] - 'A' + 1;
 
    for (int i = 1; i < String.size(); i++)
    {
        Power[i] = Power[i - 1] * PrimeNumber;
        PrefixHash[i] = (String[i] - 'A' + 1) * Power[i];
        PrefixHash[i] += PrefixHash[i - 1];
    }
 
}
 
void SubstringHashCalculation()
{
    for (int i = 0; i < Substring.size(); i++)
        SubstringHash += (Substring[i] - 'A' + 1) * Power[i];
}
 
void SubStringComparison()
{
    for (int i = 0; i <= String.size() - Substring.size(); i++)
    {
        unsigned long long tmp_pref_hash = PrefixHash[i + Substring.size() - 1];
        if (i)
            tmp_pref_hash -= PrefixHash[i - 1];
        if (tmp_pref_hash == SubstringHash * Power[i])
            InIndex.push_back(i + 1);
    }
}
 
void RabinKarp()
{
    PrefixHashCalculation();
    SubstringHashCalculation();
    SubStringComparison();
}
 
void Output()
{
    cout << InIndex.size() << '\n';
    if (InIndex.size())
        for (auto i : InIndex)
            cout << i << ' ';
}
 
int main()
{
    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);
    InputStrings();
    RabinKarp();
    Output();
    return 0;
}
