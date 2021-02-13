#include"./Directory.h"

Directory::Directory(int number_of_bits,int bucket_max_size){
    this->number_of_bits = number_of_bits;
    this->bucket_max_size = bucket_max_size;

    //Por conveniência inicializo o global_depth com 2
    this->global_depth = 2;

    //Adiciono o primeiro balde
    Bucket* firstBucket = new Bucket(bucket_max_size);

    //Faz todas posições do meu balde apontarem para o mesmo Bucket
    for (int i = 0; i < pow(2,this->global_depth); i++)
    {
        this->buckets.push_back(firstBucket);
    }
}
//Transforma um valor inteiro em binário(bitwize)
string Directory::hash(long long int value){
    string hashedValue; 
    for (int i = this->number_of_bits ; i >= 0; i--)
    {
        long long int k = value >> i;
        if (k & 1)
            hashedValue.push_back('1'); 
        else
            hashedValue.push_back('0'); 

    }
    return hashedValue;
}

long int Directory::binary_to_decimal(long int n)
{
    int decimal = 0, i = 0, remainder;
    while (n != 0)
    {
        remainder = n;
        n /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }
    return decimal;
}

void Directory::Insert(long long int value){
    string hashedValue = this->hash(value);
    //Pego as posições significativas da chave que serão relativas ao global_depth
    string significantBits = hashedValue.substr(0,this->global_depth);
    this->buckets[this->binary_to_decimal(stoi(significantBits))]->Insert(hashedValue, value);
}