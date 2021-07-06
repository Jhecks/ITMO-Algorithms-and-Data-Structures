#include <iostream>
#include <fstream>
 
int main()
{
    std::ifstream fin ("aplusbb.in");
    std::ofstream fout ("aplusbb.out");
 
    long long first = 0;
    long long second = 0;
 
    fin >> first >> second;
    fout << first + (second * second);
 
    fin.close();
    fout.close();
    return 0;
}
