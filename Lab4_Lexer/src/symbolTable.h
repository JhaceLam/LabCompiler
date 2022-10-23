#ifndef SYMBOLTALBE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef string TypeOfProperty;
typedef map<string, TypeOfProperty> MAP_STR_PROP;
typedef pair<string, TypeOfProperty> STR_PROP;

class SymbolTable {
private:
    MAP_STR_PROP table;

public:
    MAP_STR_PROP::iterator insert(string s, TypeOfProperty t);
    MAP_STR_PROP::iterator lookup(string s);
    MAP_STR_PROP::iterator end();
    void print();
};

#endif