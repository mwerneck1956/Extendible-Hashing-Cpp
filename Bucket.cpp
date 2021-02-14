#include"./Bucket.h"
#include<algorithm>
#include<list>

Bucket::Bucket(int maxSize){
    this->maxSize = maxSize;
    this->usedSize =0;
    this->local_depth =0;
}

string Bucket::GetElement(int pos){
    return this->hashedValues[pos];
}

int Bucket::GetSize(){
    return this->usedSize;
}

int Bucket::GetLocalDepth(){
    return this->local_depth;
}

int Bucket::GetUsedSize(){
    return this->usedSize;
}

void Bucket::SetLocalDepth(int new_local_depth){
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

void Bucket::VerifyLocalDepth(string value , int global_depth){

    string significant_bits = value.substr(0,global_depth);
    //Ocorrência dos bits significativos no meu vetor 
    int valueOcorrence = 0;

 
    //Iterar nos elementos do meu balde, e pega os n bits significativos de todos
    for(int i = 0 ; i < this->GetUsedSize() ; i++){
        if(significant_bits == this->hashedValues[i].substr(0,global_depth))
            valueOcorrence++;
    }


    //Se a ocorrência do valor inserido for maior que a minha profundidade local, tenho que alterar a mesma
    if(valueOcorrence > this->GetLocalDepth())
        this->SetLocalDepth(valueOcorrence);
    
}
 

bool Bucket::Insert(string hashedValue , int global_depth){
    //Verifico se é possivel inserir o valor no balde
    if(this->usedSize < this->maxSize){
        this->hashedValues.push_back(hashedValue);
        //Vai verificar se a profundidade precisa ser alterada
        this->VerifyLocalDepth(hashedValue,global_depth);
        this->usedSize++;

        cout << "Profundidade nova " << this->GetLocalDepth() << endl;
        return true;
    }


    cout << "balde chei" << endl;
    return false;
}

void Bucket::ClearBucket(){
    this->hashedValues.clear();
    this->SetLocalDepth(0);
}

void Bucket::Remove(string value){
    //Busco o indíce do proucurado
    //list<string>::iterator findIter = find(this->hashedValues.begin(), this->hashedValues.end(), 1);
    //Deleto o valor do achado
    //this->hashedValues.erase(findIter);
}

Bucket::~Bucket(){
    this->hashedValues.~vector();
}
