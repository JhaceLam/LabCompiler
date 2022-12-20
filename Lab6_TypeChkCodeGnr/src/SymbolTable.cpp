#include "SymbolTable.h"
#include "Type.h"
#include <iostream>
#include <sstream>

std::string SymbolEntry::getHexString(double val) {
    std::ostringstream ss;
    double val_valid = static_cast<float>(val);
    uint64_t hexVal = reinterpret_cast<uint64_t&>(val_valid);
    ss << "0x" << std::hex << std::uppercase << hexVal;
    return ss.str();
}

SymbolEntry::SymbolEntry(Type *type, int kind) 
{
    this->type = type;
    this->kind = kind;
    value.numValue = 0;
    nextFuncSe = nullptr;
}

bool SymbolEntry::setNextFuncSe(SymbolEntry *se)
{
    if (!se->getType()->isFunc()) {
        return false;
    }

    SymbolEntry *currentSe = this;
    while (currentSe) {
        if (currentSe->getType()->sameType(se->getType())) {
            return false;
        }
        if (currentSe->getNextFuncSe()) {
            currentSe = currentSe->getNextFuncSe();
        } else {
            break;
        }
    }
    currentSe->nextFuncSe = se;
    return true;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, double value) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->value.numValue = value;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, double *arrayValue) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->value.arrayValue = arrayValue;
}

std::string ConstantSymbolEntry::toStr()
{
    std::ostringstream buffer;
    if (type->isInt()) buffer << (int)value.numValue;
    else if (type->isFloat()) buffer << value.numValue;
    else buffer << value.arrayValue;
    return buffer.str();
}

IdentifierSymbolEntry::IdentifierSymbolEntry(Type *type, std::string name, int scope, int paramNo) 
    : SymbolEntry(type, SymbolEntry::VARIABLE), name(name)
{
    this->scope = scope;
    this->paramNo = paramNo;
    this->label = -1;
    addr = nullptr;
    fromSysYLib = false;
    useZeroinitializer = false;
    givenInitValNum = 0;
}

std::string IdentifierSymbolEntry::toStr()
{
    std::ostringstream buffer;
    if (label < 0) {
        if (type->isFunc()) {
            buffer << '@';
        }
        buffer << name;
    } else {
        buffer << "%t" << label;
    }
    return buffer.str();
}

TemporarySymbolEntry::TemporarySymbolEntry(Type *type, int label) : SymbolEntry(type, SymbolEntry::TEMPORARY)
{
    this->label = label;
}

std::string TemporarySymbolEntry::toStr()
{
    std::ostringstream buffer;
    buffer << "%t" << label;
    return buffer.str();
}

SymbolTable::SymbolTable()
{
    prev = nullptr;
    level = 0;
}

SymbolTable::SymbolTable(SymbolTable *prev)
{
    this->prev = prev;
    this->level = prev->level + 1;
}

/*
    Description: lookup the symbol entry of an identifier in the symbol table
    Parameters: 
        name: identifier name
    Return: pointer to the symbol entry of the identifier

    hint:
    1. The symbol table is a stack. The top of the stack contains symbol entries in the current scope.
    2. Search the entry in the current symbol table at first.
    3. If it's not in the current table, search it in previous ones(along the 'prev' link).
    4. If you find the entry, return it.
    5. If you can't find it in all symbol tables, return nullptr.
*/
SymbolEntry* SymbolTable::lookup(std::string name)
{
    // Todo
    std::map<std::string, SymbolEntry*>::iterator findResult;
    SymbolTable *current = this;
    while ((findResult = current->symbolTable.find(name)) == current->symbolTable.end()) {
        current = current->prev;
        if (current == nullptr) {
            break;
        }
    }

    if (current == nullptr) {
        return nullptr;
    } else {
        return findResult->second;
    }
}

// install the entry into current symbol table.
bool SymbolTable::install(std::string name, SymbolEntry* entry)
{
    if (symbolTable.find(name) != symbolTable.end()) {
        SymbolEntry *se = symbolTable[name];
        if (se->getType()->isFunc() && entry->getType()->isFunc()) {
            return se->setNextFuncSe(entry); // Function overload
        } else {
            return false;
        }
    } 
    symbolTable[name] = entry;
    return true;
}

int SymbolTable::counter = 0;
static SymbolTable t;
SymbolTable *identifiers = &t;
SymbolTable *globals = &t;

void Marker(int val) {
    fprintf(stderr, "Marker: %d\n", val);
}

void Marker(std::string s) {
    fprintf(stderr, "Marker: %s\n", s.c_str());
}