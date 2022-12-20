#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <map>
#include <iostream>

class Type;
class Operand;
class Function;

typedef union {
    double numValue;
    double *arrayValue;
} valueUnionType;

class SymbolEntry
{
private:
    int kind; // one of {CONSTANT, VARIABLE, TEMPORARY}
protected:
    enum {CONSTANT, VARIABLE, TEMPORARY};
    Type *type; // Date type
    int label;
    valueUnionType value;
    SymbolEntry *nextFuncSe; // For function overload

public:
    SymbolEntry(Type *type, int kind);
    virtual ~SymbolEntry() {};
    bool isConstant() const {return kind == CONSTANT;};
    bool isTemporary() const {return kind == TEMPORARY;};
    bool isVariable() const {return kind == VARIABLE;};
    Type* getType() {return type;};
    void setType(Type *type) {this->type = type;};
    virtual std::string toStr() = 0;
    int getLabel() const {return label; }
    void setValue(double val) {value.numValue = val; }
    double getValue() {return value.numValue; }
    void setArrayValue(double *val) {value.arrayValue = val; }
    double *getArrayValue() {return value.arrayValue; }
    bool setNextFuncSe(SymbolEntry *se);
    SymbolEntry *getNextFuncSe() {return nextFuncSe; }
    static std::string getHexString(double val);
    // You can add any function you need here.
};

// symbol table managing identifier symbol entries
class SymbolTable
{
private:
    std::map<std::string, SymbolEntry*> symbolTable;
    SymbolTable *prev;
    int level;
    static int counter;
public:
    SymbolTable();
    SymbolTable(SymbolTable *prev);
    bool install(std::string name, SymbolEntry* entry);
    SymbolEntry* lookup(std::string name);
    SymbolTable* getPrev() {return prev;};
    int getLevel() {return level;};
    static int getLabel() {return counter++; };
    static void resetLabel() {counter = 0; };
    static int getCounter() {return counter; }
};

extern SymbolTable *identifiers;
extern SymbolTable *globals;

/*  
    Symbol entry for literal constant. Example:

    int a = 1;

    Compiler should create constant symbol entry for literal constant '1'.
*/
class ConstantSymbolEntry : public SymbolEntry
{
public:
    ConstantSymbolEntry(Type *type, double value = 0);
    ConstantSymbolEntry(Type *type, double *arrayValue);
    virtual ~ConstantSymbolEntry() {};
    std::string toStr();
    // You can add any function you need here.
};


/* 
    Symbol entry for identifier. Example:

    int a;
    int b;
    void f(int c)
    {
        int d;
        {
            int e;
        }
    }

    Compiler should create identifier symbol entries for variables a, b, c, d and e:

    | variable | scope    |
    | a        | GLOBAL   |
    | b        | GLOBAL   |
    | c        | PARAM    |
    | d        | LOCAL    |
    | e        | LOCAL +1 |
*/
class IdentifierSymbolEntry : public SymbolEntry
{
private:
    enum {GLOBAL, PARAM, LOCAL};
    std::string name;
    int scope;
    Operand *addr;  // The address of the identifier.
    int paramNo;             // Used when being FuncFParam, otherwise = -1
    int commonParamNo;       // Used when being FuncFParam
    int stackParamNo;        // Used when being FuncFParam
    int intParamCount;       // Used when being FuncDef
    int floatParamCount;     // Used when being FuncDef 
    bool fromSysYLib;
    bool useZeroinitializer;
    int givenInitValNum;
    Function *func = nullptr;
    // You can add any field you need here.

public:
    IdentifierSymbolEntry(Type *type, std::string name, int scope, int paramNo = -1);
    virtual ~IdentifierSymbolEntry() {};
    std::string toStr();
    bool isGlobal() const {return scope == GLOBAL;};
    bool isParam() const {return scope == PARAM;};
    bool isLocal() const {return scope >= LOCAL;};
    int getScope() const {return scope;};
    void setAddr(Operand *addr) {this->addr = addr;};
    Operand* getAddr() {return addr;};
    void setLabel() {label = SymbolTable::getLabel(); }
    int getParamNo() {return paramNo; }
    int getCommonParamNo() {return commonParamNo; }
    void setCommonParamNo(int no) {commonParamNo = no; }
    int getStackParamNo() {return stackParamNo; }
    void setStackParamNo(int no) {stackParamNo = no; }
    int getIntParamCount() {return intParamCount; }
    void setIntParamCount(int no) {intParamCount = no; }
    int getFloatParamCount() {return floatParamCount; }
    void setFloatParamCount(int no) {floatParamCount = no; }
    void setFromSysYLib() {fromSysYLib = true; }
    int getFromSysYLib() {return fromSysYLib; }
    bool getUseZeroinitializer() {return useZeroinitializer; }
    void setUseZeroinitializer(bool val = true) {useZeroinitializer = val; }
    int getGivenInitValNum() {return givenInitValNum; }
    void setGivenInitValNum(int val) {givenInitValNum = val; }
    Function *getFunction() { return func; }
    void setFunction(Function *func) { this->func = func; }
    // You can add any function you need here.
};


/* 
    Symbol entry for temporary variable created by compiler. Example:

    int a;
    a = 1 + 2 + 3;

    The compiler would generate intermediate code like:

    t1 = 1 + 2
    t2 = t1 + 3
    a = t2

    So compiler should create temporary symbol entries for t1 and t2:

    | temporary variable | label |
    | t1                 | 1     |
    | t2                 | 2     |
*/
class TemporarySymbolEntry : public SymbolEntry
{
private:
    
public:
    TemporarySymbolEntry(Type *type, int label);
    virtual ~TemporarySymbolEntry() {};
    std::string toStr();
    // You can add any function you need here.
};

void Marker(int val = 0);
void Marker(std::string s);

#endif
