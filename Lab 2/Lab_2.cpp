#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
 
using namespace std;
 
void merge(vector<pair<string, string>> &arr, int left, int mid, int right)
{
    int firstP = mid - left + 1;
    int secondP = right - mid;
 
    vector<pair<string, string>> firstArr;
    vector<pair<string, string>> secondArr;
    firstArr.resize(firstP);
    secondArr.resize(secondP);
 
    for (int i = 0; i < firstP; i++)
        firstArr[i] = arr[left + i];
    for (int j = 0; j < secondP; j++)
        secondArr[j] = arr[mid + 1 + j];
 
    int i = 0;
    int j = 0;
    int k = left;
    while (i < firstP && j < secondP)
    {
        if (firstArr[i].first <= secondArr[j].first)
        {
            arr[k] = firstArr[i];
            i++;
        }
        else
        {
            arr[k] = secondArr[j];
            j++;
        }
        k++;
    }
 
    while (i < firstP)
    {
        arr[k] = firstArr[i];
        i++;
        k++;
    }
 
    while (j < secondP)
    {
        arr[k] = secondArr[j];
        j++;
        k++;
    }
}
 
void mergeSort(vector<pair<string, string>> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
 
 
int main()
{
 
    ifstream fin("race.in");
    ofstream fout("race.out");
 
    vector<pair<string, string>> inputPairs;
 
    string first, second;
    int len;
 
    fin >> len;
 
    for (int i = 0; i < len; i++)
    {
        fin >> first >> second;
        inputPairs.emplace_back(first, second);
    }
 
    mergeSort(inputPairs, 0, len-1);
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        fout << "=== " << inputPairs[i].first << " ===" << endl;
        for (j = i; j < len && inputPairs[j].first == inputPairs[i].first; j++)
            fout << inputPairs[j].second << endl;
        i = j-1;
    }
    fin.close();
    fout.close();
    return 0;
}
