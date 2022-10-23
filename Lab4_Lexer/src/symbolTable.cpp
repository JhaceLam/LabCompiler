#include "symbolTable.h"

MAP_STR_PROP::iterator SymbolTable::insert(string s, TypeOfProperty t) {
    pair<MAP_STR_PROP::iterator, bool> ret = table.insert(STR_PROP(s, t));
    if (ret.second) {
        // cout << "Insert identifier \"" << s << "\" with property: " << t << endl; 
    } else {
        table[s] = t;
        // cout << "Update identifier \"" << s << "\" with property: " << t << endl; 
    }
    return ret.first;
}

MAP_STR_PROP::iterator SymbolTable::lookup(string s) {
    return table.find(s);
}

MAP_STR_PROP::iterator SymbolTable::end() {
    return table.end();
}

void SymbolTable::print() {
    for (MAP_STR_PROP::iterator it = table.begin(); it != table.end(); it++) {
        cout << it->first << " = " << it->second << endl;
    }
}