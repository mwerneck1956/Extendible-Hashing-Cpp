#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED
#include "./Bucket.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <math.h>
#include <string>

using namespace std;

class Directory
{
private:
    int global_depth;
    int bucket_max_size;
    int number_of_bits;
    vector<Bucket *> buckets;

public:
    Directory(int depth, int bucket_size);
    ~Directory();
    string hash(long long int n , int number_of_bits);
    void Insert(long long int value);
    long int binary_to_decimal(long int n);
    void PrintInfo();
};

#endif