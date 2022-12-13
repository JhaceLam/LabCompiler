#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <map>

class Type;
class Operand;

typedef union {
    double numValue;
    void *arrayValue;
} valueUnionType;

class SymbolEntry
{
private:
    int kind; // one of {CONSTANT, VARIABLE, TEMPORARY}
protected:
    enum {CONSTANT, VARIABLE, TEMPORARY};
    bool sysy;
    Type *type; // Date type
    valueUnionType value;

public:
    SymbolEntry(Type *type, int kind);
    virtual ~SymbolEntry() {};
    bool isConstant() const {return kind == CONSTANT;};
    bool isTemporary() const {return kind == TEMPORARY;};
    bool isVariable() const {return kind == VARIABLE;};
    Type* getType() {return type;};
    void setType(Type *type) {this->type = type;};
    virtual std::string toStr() = 0;
    void setValue(double val) {value.numValue = val; }
    double getValue() {return value.numValue; }
    void setArrayValue(void *val) {value.arrayValue = val; }
    void *getArrayValue() {return value.arrayValue; }
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
    ConstantSymbolEntry(Type *type, void *arrayValue);
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
    int label;
    int paramNo;             // Used when being FuncFParam, otherwise = -1
    int commonParamNo;       // Used when being FuncFParam
    int stackParamNo;        // Used when being FuncFParam
    int intParamCount;       // Used when being FuncDef
    int floatParamCount;     // Used when being FuncDef 
    // You can add any field you need here.

public:
    IdentifierSymbolEntry(Type *type, std::string name, int scope, int paramNo = -1);
    IdentifierSymbolEntry(Type *type, std::string name, int scope, int paramNo, bool sysy);
    virtual ~IdentifierSymbolEntry() {};
    std::string toStr();
    bool isGlobal() const {return scope == GLOBAL;};
    bool isParam() const {return scope == PARAM;};
    bool isLocal() const {return scope >= LOCAL;};
    int getScope() const {return scope;};
    void setAddr(Operand *addr) {this->addr = addr;};
    Operand* getAddr() {return addr;};
    int getLabel() {return label; }
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
    int label; // the number following t, like '1' in 't1'
public:
    TemporarySymbolEntry(Type *type, int label);
    virtual ~TemporarySymbolEntry() {};
    std::string toStr();
    int getLabel() const {return label;};
    // You can add any function you need here.
};

#endif
