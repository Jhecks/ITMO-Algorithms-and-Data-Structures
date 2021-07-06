#include <iostream>
#include <fstream>
 
int main()
{
    std::ifstream fin ("aplusb.in");
    std::ofstream fout ("aplusb.out");
 
    long long first = 0;
    long long second = 0;
 
    fin >> first >> second;
    fout << first + second;
 
    fin.close();
    fout.close();
    return 0;
}
