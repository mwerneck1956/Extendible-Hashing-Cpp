#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <iomanip> //setprecision
#include <fstream>
#include "./Classes/Directory/Directory.h"

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

//Código feito para testes manuais de inserção
/*
vector<string> testeVetor()
{
    vector<string> teste;
    teste.push_back("00100");
    teste.push_back("00111");
    teste.push_back("00011");
    teste.push_back("00000");

    teste.push_back("01101");
    teste.push_back("01100");

    teste.push_back("10100");
    teste.push_back("10000");
    teste.push_back("11000");
    teste.push_back("11110");
    teste.push_back("11111");
    teste.push_back("00001");

    return teste;
}
   vector<string> teste = testeVetor();
    int i = 0;
    while (i < teste.size())
    {
        directory->Insert(directory->binary_to_decimal(stoull(teste.at(i))));
        i++;
    }

    directory->PrintInfo();

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
        while (i < randomNums.size())
        {
            directory->Insert(randomNums.at(i));
            progress++;
            //Para melhor feedback da inserção quando o N é muito grande
            if (progress == 100000)
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
            //Para melhor feedback da inserção quando o N é muito grande
            if (progress == 100000)
            {
                cout << "Na iteração  " << i << "...." << endl;
                progress = 0;
            }
            i++;
        }
    }

    double loadFactor = (float(directory->GetNumberOfKeys()) / (directory->GetNumberOfBuckets() * bucket_size));

    //ofstream arq("saidaTestes.txt",ios::app);
    string optionSelected = option == 1 ? "Totalmente Aleatório" : "Aleatório com mesmo padrão de bits";

    cout << "--------------------------------------RESULTADOS--------------------------------------" << endl;
    cout << "Geração de números :  " << optionSelected << endl;
    cout << "Número de bits escolhido : " << number_of_bits << endl;
    cout << "Tamanho M do balde escolhido : " <<  bucket_size << endl;
    cout << "Número de chaves inseridas : " << directory->GetNumberOfKeys() << endl;
    cout << "Número de baldes : " << directory->GetNumberOfBuckets() << endl;
    cout << "Fator de carga : " << setprecision(4) << float(loadFactor * 100) << "%" << endl;
    cout << "Ocupação da memória : " <<  double(directory->GetMemoryOcupation()/0.000125) << " Kilobytes" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}