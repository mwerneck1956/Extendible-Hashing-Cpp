#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "./Directory.h"

using namespace std;

vector<string> testeVetor()
{
    vector<string> teste;
    teste.push_back("00100");
    teste.push_back("00111");
    teste.push_back("00011");
    teste.push_back("01101");
    teste.push_back("10100");
    teste.push_back("10000");
    teste.push_back("11000");
    teste.push_back("11110");
    teste.push_back("00000");


    return teste;
}

int main()
{
    int number_of_bits, bucket_size;
    vector<string> teste = testeVetor();

    cout << "Digite o tamanho  máximo de bits e tamanho do balde" << endl;
    cin >> number_of_bits >> bucket_size;
    Directory *directory = new Directory(number_of_bits, bucket_size);
    int i =0;
    while(i < teste.size())
    {
        directory->Insert(directory->binary_to_decimal(stoi(teste.at(i))));
        i++;
    }

    directory->PrintInfo();
}