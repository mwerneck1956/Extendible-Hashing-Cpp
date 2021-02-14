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
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<long long int> distribution(0, pow(2, max_bits) - 1);
    vector<long long int> randomNumbers;
    randomNumbers.reserve(size);
    for (int i = 0; i < size; i++)
    {
        randomNumbers.push_back(distribution(generator));
    }

    return randomNumbers;
}

vector<long long int> generateRandomValuesWithSamePattern(int size , int max_bits)
{
    std::uniform_int_distribution<long long int> distribution(0,1);


    vector<long long int> a;
    return a;
}

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

int main()
{
    int number_of_bits, bucket_size, random_size;

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
    vector<long long int> teste = generateRandomNumbers(number_of_bits, random_size);

    Directory *directory = new Directory(number_of_bits, bucket_size);
    int i = 0, progress = 0;
    while (i < teste.size())
    {
        directory->Insert(teste.at(i));
        progress++;
        if (progress == 100)
        {
            cout << "Na iteração  " << i << "...." << endl;
            progress = 0;
        }
        i++;
    }
    double loadFactor = (float(teste.size()) / (directory->getNumberOfBuckets() * bucket_size));

    cout << "--------------------------------------RESULTADOS--------------------------------------" << endl;
    cout << "Número de chaves : " << teste.size() << endl;
    cout << "Número de baldes : " << directory->getNumberOfBuckets() << endl;
    cout << "Fator de carga : " << loadFactor << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    ;

}