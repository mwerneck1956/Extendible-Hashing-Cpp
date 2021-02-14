#include <iostream>
#include <list>
#include <vector>
#include "./Directory.h"

using namespace std;

int main()
{
    int number_of_bits, bucket_size;
    cout << "Digite o tamanho  máximo de bits e tamanho do balde" << endl;
    cin >> number_of_bits >> bucket_size;
    Directory *directory = new Directory(number_of_bits, bucket_size);
    int value;
    while (value != 0)
    {
        cout << "Digite o valor a ser inserido no diretório" << endl;
        cin >> value;
        directory->Insert(value);
    }

    directory->PrintInfo();

}