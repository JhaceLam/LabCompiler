#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>

class Type
{
private:
    int kind;
protected:
    enum {INT, VOID, FLOAT, FUNC, INT_ARRAY, CONST_INT, CONST_INT_ARRAY, FLOAT_ARRAY, CONST_FLOAT, CONST_FLOAT_ARRAY};
public:
    Type(int kind) : kind(kind) {};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    bool isInt() const {return kind == INT;};
    bool isVoid() const {return kind == VOID;};
    bool isFloat() const {return kind == FLOAT;};
    bool isFunc() const {return kind == FUNC;};
    bool isIntArray() const {return kind == INT_ARRAY;};
    bool isFloatArray() const {return kind == FLOAT_ARRAY;}
    bool isConstInt() const {return kind == CONST_INT;};
    bool isConstIntArray() const {return kind == CONST_INT_ARRAY;};
    bool isConstFloat() const {return kind == CONST_FLOAT;};
    bool isConstFloatArray() const {return kind == CONST_FLOAT_ARRAY;}

    bool isArray() const {
        return kind == INT_ARRAY || kind == CONST_INT_ARRAY ||
            kind == FLOAT_ARRAY || kind == CONST_FLOAT_ARRAY;
    }
    bool isIntFamily() const {
        return kind == INT || kind == CONST_INT || 
            kind == INT_ARRAY || kind == CONST_INT_ARRAY;
    }
    bool isConst() const {
        return kind == CONST_INT || kind == CONST_INT_ARRAY ||
            kind == CONST_FLOAT || kind == CONST_FLOAT_ARRAY;
    }
};

class IntType : public Type
{
private:
    int size;
public:
    IntType(int size) : Type(Type::INT), size(size){};
    std::string toStr();
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FloatType : public Type
{
public:
    FloatType() : Type(Type::FLOAT){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    Type *returnType;
    std::vector<Type*> paramsType;
public:
    FunctionType(Type* returnType, std::vector<Type*> paramsType) : 
    Type(Type::FUNC), returnType(returnType), paramsType(paramsType){};
    std::string toStr();
};

class IntArrayType : public Type
{
private:
    int dimension;
public:
    IntArrayType() : Type(Type::INT_ARRAY) {};
    void setDimension(int d);
    std::string toStr();
};

class ConstIntType : public Type
{
public:
    ConstIntType() : Type(Type::CONST_INT){};
    std::string toStr();
};

class ConstIntArrayType : public Type
{
private:
    int dimension;
public:
    ConstIntArrayType() : Type(Type::CONST_INT_ARRAY) {};
    void setDimension(int d);
    std::string toStr();
};

class ConstFloatType : public Type
{
public:
    ConstFloatType() : Type(Type::CONST_FLOAT){};
    std::string toStr();
};

class FloatArrayType : public Type
{
private:
    int dimension;
public:
    FloatArrayType() : Type(Type::FLOAT_ARRAY){};
    void setDimension(int d);
    std::string toStr();
};

class ConstFloatArrayType : public Type
{
private:
    int dimension;
public:
    ConstFloatArrayType() : Type(Type::CONST_FLOAT_ARRAY){};
    void setDimension(int d);
    std::string toStr();
};

class TypeSystem
{
private:
    static IntType commonInt;
    static VoidType commonVoid;
    static FloatType commonFloat;
    static ConstIntType commonConstInt;
    static ConstFloatType commonConstFloat;
public:
    static Type *intType;
    static Type *voidType;
    static Type *floatType;
    static Type *constIntType;
    static Type *constFloatType;
};

#endif
