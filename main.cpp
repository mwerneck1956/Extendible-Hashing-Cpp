#include<iostream>
#include<list>
#include<vector>
#include"./Directory.h"

using namespace std;

int main(){
    int number_of_bits,bucket_size;
    cout << "Digite o tamanho  máximo de bits e tamanho do balde" << endl;
    cin >> number_of_bits >> bucket_size;
    Directory* directory = new Directory(number_of_bits,bucket_size);
    long long int toHash=10;
    while(toHash!=0){
        cout << "Digite um valor" << endl;
        cin >> toHash;
        cout << "Hash : " << directory->hash(toHash) << endl;
    }


}