#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "./Directory.h"

using namespace std;

int main()
{
    int number_of_bits, bucket_size;
    cout << "Digite o tamanho  máximo de bits e tamanho do balde" << endl;
    cin >> number_of_bits >> bucket_size;
    Directory *directory = new Directory(number_of_bits, bucket_size);
    string value;
    cout << "Digite o valor a ser inserido no diretório" << endl;
    cin >> value;
   // cout << "decimal " << directory->binary_to_decimal(stoi("01"));
    
    while (value != "a")
    {
        directory->Insert(directory->binary_to_decimal(stoi(value)));
        cout << "Digite o valor a ser inserido no diretório" << endl;
        cin >> value;
    }
    /*
    cout << "Digite o valor a ser buscado " << endl;
    cin >> value;
    if(directory->Find(value))
        cout << "Valor achado" << endl;
    else
        cout << "Valor n achado" << endl;
    */
   directory->DuplicateDirectory();
   directory->PrintInfo();
}