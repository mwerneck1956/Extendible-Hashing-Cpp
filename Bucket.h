#ifndef BUCKET_H_INCLUDED
#define BUCKET_H_INCLUDED
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Bucket
{
  private:
        int local_depth;
        int maxSize;
        int usedSize;
        vector<string> hashedValues;

  public:
       Bucket(int maxSize);
       ~Bucket();
       int GetDepth(int significantBits);
       int GetUsedSize();
       int GetSize();
       string GetElement (int pos);
       int GetElement(string key);
       int GetLocalDepth();
       void SetLocalDepth(int new_local_depth);
       bool Insert(string hashedValue , int global_depth);
       void RecalculateLocalDepth(string value , int global_depth);
       int Find(string value);
       int Search(string hashedKey);
       void ClearBucket();
       void Remove(string Value, int global_depth);
       void Remove(int pos , int global_depth);
       bool IsFull();

       //@Todo fazer remoção

};

#endif