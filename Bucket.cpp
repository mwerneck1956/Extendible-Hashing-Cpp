#include "./Bucket.h"
#include <algorithm>
#include <list>

Bucket::Bucket(int maxSize)
{
    this->maxSize = maxSize;
    this->usedSize = 0;
    this->local_depth = 0;
}

string Bucket::GetElement(int pos)
{
    return this->hashedValues[pos];
}

int Bucket::GetSize()
{
    return this->usedSize;
}

int Bucket::GetLocalDepth()
{
    return this->local_depth;
}

int Bucket::GetUsedSize()
{
    return this->usedSize;
}

void Bucket::SetLocalDepth(int new_local_depth)
{
    this->local_depth = new_local_depth;
}

/*int Bucket::GetDepth(int significantBits){
    int* auxDepth = new int[this->maxSize];
    string aux; 
    for(int i = 0 ; i < this->usedSize ; i++){
        string aux = this->hashedValues.
        for(int j = 0 ; this->usedSize ; j++){

        }
    }
}
 */

void Bucket::RecalculateLocalDepth(string value, int global_depth)
{

    string significant_bits = value.substr(0, global_depth);
    //Ocorrência dos bits significativos no meu vetor
    int valueOcorrence = 0;

    //Iterar nos elementos do meu balde, e pega os n bits significativos de todos
    for (int i = 0; i < this->GetUsedSize(); i++)
    {
        if (significant_bits == this->hashedValues[i].substr(0, global_depth))
            valueOcorrence++;
    }

    //Se a ocorrência do valor inserido for maior que a minha profundidade local, tenho que alterar a mesma
    if (valueOcorrence > this->GetLocalDepth())
        this->SetLocalDepth(valueOcorrence);
}

bool Bucket::Insert(string hashedValue, int global_depth)
{
    //Verifico se é possivel inserir o valor no balde
    if (this->usedSize < this->maxSize)
    {
        this->hashedValues.push_back(hashedValue);
        //Vai verificar se a profundidade precisa ser alterada
        this->RecalculateLocalDepth(hashedValue, global_depth);
        this->usedSize++;

        cout << "Profundidade nova " << this->GetLocalDepth() << endl;
        return true;
    }

    return false;
}

void Bucket::PrintBucket(){
    cout << "Balde " << endl;
    cout << "Valores : ";
    for(string value : this->hashedValues){
        cout << value +",";  
    }
    cout << endl;
}

void Bucket::ClearBucket()
{
    this->hashedValues.clear();
    this->SetLocalDepth(0);
}

bool Bucket::IsFull()
{
    return this->usedSize == this->maxSize;
}

int Bucket::Find(string value)
{
    cout << "Valor recebido brow " << value << endl;
    int index = 0;
    for (string currentValue : this->hashedValues)
    {
        if (value == currentValue)
            return index;

        index++;
    }
    //Se não achar o valor retorrna -1
    return -1;
}


void Bucket::Remove(string value, int global_depth)
{
    int position = this->Find(value);
    if (position != -1)
    {
        this->hashedValues.erase(this->hashedValues.begin() + position);
        int index = 0;
        //Recalcula a profundidade local do balde
        for (string value : this->hashedValues)
        {
            this->hashedValues.erase(this->hashedValues.begin() + index);
            RecalculateLocalDepth(value, local_depth);
            this->hashedValues.push_back(value);
        }

    }
}

void Bucket::Remove(int pos, int global_depth)
{
    this->hashedValues.erase(this->hashedValues.begin() + pos);

    int index = 0;
    //Conserta a profundidade local do balde
    for (string value : this->hashedValues)
    {
        //Apago o valor a ser comparado na recalculação , pois se ele existir no vetor ele vai comparar o elemento a si mesmo
        this->hashedValues.erase(this->hashedValues.begin() + index);
        RecalculateLocalDepth(value, local_depth);
        this->hashedValues.push_back(value);
        index++;
    }

    cout << "Nova profundidade :  " << this->local_depth << endl;
}

Bucket::~Bucket()
{
    this->hashedValues.~vector();
}
