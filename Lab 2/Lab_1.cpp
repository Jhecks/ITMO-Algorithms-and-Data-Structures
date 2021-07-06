#include<vector> 
#include<fstream>
 
using namespace std;
 
void merge(vector<int> &arr, int left, int mid, int right)
{
    int firstP = mid - left + 1;
    int secondP = right - mid;
 
    vector<int> firstArr;
    vector<int> secondArr;
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
        if (firstArr[i] <= secondArr[j])
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
 
void mergeSort(vector<int> &arr, int left, int right)
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
    ifstream fin("sort.in");
    ofstream fout("sort.out");
 
    int len = 0;
    fin >> len;
    vector<int> arr;
    arr.resize(len);
 
    for (int i = 0; i < len; i++)
        fin >> arr[i];
 
    mergeSort(arr, 0, len - 1);
 
    for (int i = 0; i < len; i++)
        fout << arr[i] << ' ';
 
    fin.close();
    fout.close();
 
    return 0;
}
