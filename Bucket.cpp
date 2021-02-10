#include "./Bucket.h"
#include <algorithm>

Bucket::Bucket(int maxSize){
    this->maxSize = maxSize;
    this->usedSize =0;
    this->local_depth =0;
}

bool Bucket::Insert(string hashedValue){
    //Verifico se é possivel inserir o valor no balde
    if(this->usedSize < this->maxSize){
        this->hashedValues.push_back(hashedValue);
        return true;
    }

    return false;
}

void Bucket::Remove(string value){
    //Busco o indíce do proucurado
    list<string>::iterator findIter = find(this->hashedValues.begin(), this->hashedValues.end(), 1);
    //Deleto o valor do achado
    this->hashedValues.erase(findIter);
}

Bucket::~Bucket(){
    this->hashedValues.~list();
}
