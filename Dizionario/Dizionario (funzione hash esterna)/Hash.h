#ifndef _HASH_H
#define _HASH_H

#include <stddef.h>
#include <iostream>
#include <string>
 
using namespace std;

template<typename T>
class Hash {
public:
    unsigned int H(const T& chiave, int dim);
};


//Specializzazione classe Hash di tipo String---------------------------
template<>
class Hash<string> {
public:
    unsigned int H(const string& chiave, unsigned int dim);
private:
    unsigned int hash(string str);
};


unsigned int Hash<string>::H(const string& chiave, unsigned int dim) {
    return (hash(chiave) % dim);
}

unsigned int Hash<string>::hash(string str) {
    unsigned int hash = 5381;
    int l = str.length();
    for (int i = 0; i < l; i++)
        hash = hash * 33 + str[i];
    return hash;
}

#endif