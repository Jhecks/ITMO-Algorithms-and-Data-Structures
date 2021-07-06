#include <iostream>
#include <fstream>
#include <vector>
 
int main()
{
    std::ifstream fin ("sortland.in");
    std::ofstream fout ("sortland.out");
 
    std::vector <std::vector <double>> arr;
    long long size = 0;
 
    fin >> size;
 
    arr.resize(2);
 
    arr[0].resize(size);
    arr[1].resize(size);
    for (int i = 0; i < size; i++)
    {
        arr[0][i] = i+1;
        fin >> arr[1][i];
    }
 
    for (int i = 0; i < size; i++)
        for(int j = i; j < size; j++)
            if (arr[1][i] > arr[1][j])
            {
                std::swap(arr[1][i], arr[1][j]);
                std::swap(arr[0][i], arr[0][j]);
            }
 
    fout << arr[0][0] << ' ' << arr[0][size/2] << ' ' << arr[0][size-1];
 
    fin.close();
    fout.close();
    return 0;
}
