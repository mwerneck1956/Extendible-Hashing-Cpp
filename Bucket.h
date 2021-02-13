#ifndef BUCKET_H_INCLUDED
#define BUCKET_H_INCLUDED
#include<iostream>
#include<map>
#include<string>

using namespace std;

class Bucket
{
  private:
        int local_depth;
        int maxSize;
        int usedSize;
        map<string,int> hashedValues;

  public:
       Bucket(int maxSize);
       ~Bucket();
       bool Insert(string hashedValue , int value);
       void Remove(string Value);
       int GetDepth(int significantBits);
       void GetUsedSize();
       int getElement(string key);
       int Search(string hashedKey);
       //@Todo fazer remoção

};

#endif