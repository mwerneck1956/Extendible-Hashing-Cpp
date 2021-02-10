#ifndef BUCKET_H_INCLUDED
#define BUCKET_H_INCLUDED
#include<iostream>
#include<list>

using namespace std;

class Bucket
{
  private:
        int local_depth;
        int maxSize;
        int usedSize;
        list<string> hashedValues;

  public:
       Bucket(int maxSize);
       ~Bucket();
       bool Insert(string hashedValue);
       void Remove(string Value);
       void GetLocalDepth();
       void GetUsedSize();

};

#endif