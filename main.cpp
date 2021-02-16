#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <random>
#include <functional>
#include "./Directory.h"

using namespace std;

vector<long long int> generateRandomNumbers(int max_bits, int size)
{
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<long long int> distribution(0, pow(2, max_bits) - 1);
    vector<long long int> randomNumbers;
    randomNumbers.reserve(size);
    for (int i = 0; i < size; i++)
    {
        long int value = distribution(generator);
        randomNumbers.push_back(value);
    }

    return randomNumbers;
}

vector<string> generateRandomValuesWithSamePattern(int size, int max_bits)
{
    //O padrão é sempre começar com 1;

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<char> distribution('0', '1');
    vector<string> binaryValues;
    binaryValues.reserve(size);
    string aux = "";
    int i = 0;
    while (i < size)
    {
        aux.push_back('1');
        for (int j = 1; j < max_bits; j++)
        {
            aux.push_back(distribution(generator));
        }
        binaryValues.push_back(aux);
        aux = "";
        i++;
    }

    return binaryValues;
}
/*
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
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");
    teste.push_back("00000");

    return teste;
}
*/
int main()
{

    int number_of_bits, bucket_size, random_size, option;

    cout << "-------------------Hashing Extensível---------------------" << endl;
    cout << "Aluno: Matheus Gomes Luz Werneck (201835037) " << endl
         << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Digite o tamanho máximo de bits B" << endl;
    cin >> number_of_bits;
    cout << "Digite o tamanho máximo de valores por balde M" << endl;
    cin >> bucket_size;
    cout << "Digite o número de registros aleatórios" << endl;
    cin >> random_size;
    cout << "Digite [1] para pseudo-chaves totalmente aleatórios" << endl;
    cout << "Digite [2] para  pseudo-chaves iniciadas com um mesmo padrão de bits" << endl;
    cin >> option;
    Directory *directory = new Directory(number_of_bits, bucket_size);

    if (option == 1)
    {
        vector<long long int> randomNums = generateRandomNumbers(number_of_bits, random_size);
        int i = 0, progress = 0;
        while (i < randomNums.size() - 1)
        {
            directory->Insert(randomNums.at(i));
            progress++;
            if (progress == 1000)
            {
                cout << "Na iteração  " << i << "...." << endl;
                progress = 0;
            }
            i++;
        }
    }
    else
    {
        vector<string> randomNums = generateRandomValuesWithSamePattern(random_size, number_of_bits);
        int i = 0, progress = 0;
        while (i < randomNums.size())
        {
            directory->Insert(directory->binary_to_decimal(stoull(randomNums.at(i))));
            progress++;
            if (progress == 1000)
            {
                cout << "Na iteração  " << i << "...." << endl;
                progress = 0;
            }
            i++;
        }
    }

    double loadFactor = (float(directory->GetNumberOfKeys()) / (directory->GetNumberOfBuckets() * bucket_size));

    cout << "--------------------------------------RESULTADOS--------------------------------------" << endl;
    cout << "Número de chaves inseridas : " << directory->GetNumberOfKeys()  << endl;
    cout << "Número de baldes : " << directory->GetNumberOfBuckets() << endl;
    cout << "Fator de carga : " << loadFactor << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;

    //directory->PrintInfo();

    //delete &directory;
}