#include <iostream>
#include <fstream>
#include <vector>
 
int main()
{
    std::ifstream fin ("smallsort.in");
    std::ofstream fout ("smallsort.out");
    std::vector <long long> arr;
 
    long long size = 0;
 
    fin >> size;
 
    arr.resize(size);
 
    for (int i = 0; i < size; i++)
        fin >> arr[i];
 
 
    for (int i = 0; i < size; i++)
        for(int j = i; j < size; j++)
            if (arr[i] > arr[j])
                std::swap(arr[i], arr[j]);
 
    for (int i = 0; i < size; i++)
        fout << arr[i] << ' ';
 
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
 
 
    fin.close();
    fout.close();
    return 0;
}
