#include"./Bucket.h"
#include<algorithm>
#include<list>

Bucket::Bucket(int maxSize){
    this->maxSize = maxSize;
    this->usedSize =0;
    this->local_depth =0;
}

bool Bucket::Insert(string hashedValue , int value){
    //Verifico se é possivel inserir o valor no balde
    if(this->usedSize < this->maxSize){
        this->hashedValues.insert(make_pair(hashedValue,value));
        this->usedSize++;
        return true;
    }

    return false;
}

int Bucket::getElement(string key){
    return this->hashedValues.at(key);
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

void Bucket::Remove(string value){
    //Busco o indíce do proucurado
    //list<string>::iterator findIter = find(this->hashedValues.begin(), this->hashedValues.end(), 1);
    //Deleto o valor do achado
    //this->hashedValues.erase(findIter);
}

Bucket::~Bucket(){
    this->hashedValues.~map();
}
