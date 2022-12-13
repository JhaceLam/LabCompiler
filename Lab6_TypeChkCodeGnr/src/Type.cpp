#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(32, false);
IntType TypeSystem::commonBool = IntType(1, false);
FloatType TypeSystem::commonFloat = FloatType(32, false);
VoidType TypeSystem::commonVoid = VoidType();
IntType TypeSystem::commonConstInt = IntType(32, true);
IntType TypeSystem::commonConstBool = IntType(1, true);
FloatType TypeSystem::commonConstFloat = FloatType(32, true);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;
Type* TypeSystem::floatType = &commonFloat;
Type* TypeSystem::constIntType = &commonConstInt;
Type* TypeSystem::constBoolType = &commonConstBool;
Type* TypeSystem::constFloatType = &commonConstFloat;

bool Type::isIntFamily()
{
    Type *currentType = this;
    while (currentType != nullptr && currentType->isArray()) {
        currentType = dynamic_cast<ArrayType *>(currentType)->getElementType();
    }
    return currentType->isInt();
}

std::string IntType::toStr()
{
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}

std::string FloatType::toStr()
{
    std::ostringstream buffer;
    buffer << "f" << size;
    return buffer.str();
}

int VoidType::getSize() {
    fprintf(stderr, "Error: invalid application of sizeof to a void type\n");
    return 1;
}

std::string VoidType::toStr()
{
    return "void";
}

int FunctionType::getSize() {
    fprintf(stderr, "Error: invalid application of sizeof to a function type\n");
    return 1;
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for (auto iter = paramsType.begin(); iter != paramsType.end(); iter++) {
        buffer << (*iter)->toStr();
        if (iter + 1 != paramsType.end()) {
            buffer << ", ";
        }
    }
    buffer << ')';
    return buffer.str();
}

std::string PointerType::toStr()
{
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}

ArrayType::ArrayType(Type *elementType, int length, bool constant) : 
    Type(Type::ARRAY, constant), elementType(elementType), length(length) {
        size = elementType->getSize() * length;
    };

std::string ArrayType::toStr()
{
    std::ostringstream buffer;
    Type *currentType = this;
    bool lengthNotGiven = false;
    int bracketNum = 0;
    while (currentType != nullptr && currentType->isArray()) {
        ArrayType *currentArrayType = dynamic_cast<ArrayType *>(currentType);
        if (currentArrayType->getLength() == -1) {
            lengthNotGiven = true;
        } else {
            buffer << "[" << currentArrayType->getLength() << " x ";
            bracketNum++;
        }
        currentType = currentArrayType->getElementType();
    }
    buffer << currentType->toStr() << std::string(bracketNum, ']');
    if (lengthNotGiven) buffer << "*";
    return buffer.str();
}

PointerType::PointerType(Type* valueType, bool constant) : Type(Type::PTR, constant) {
    this->valueType = valueType; 
    size = sizeof(void *);
};

Type *IntType::deepCopy() {
    Type *newType = new IntType(this->size, this->constant);
    return newType;
}

Type *FloatType::deepCopy() {
    Type *newType = new FloatType(this->size, this->constant);
    return newType;
}

Type *VoidType::deepCopy() {
    Type *newType = new VoidType();
    return newType;
}

Type *FunctionType::deepCopy() {
    Type *newReturnType = returnType->deepCopy();
    std::vector<Type *> newParamsType;
    for (Type *type : paramsType) {
        newParamsType.push_back(type->deepCopy());
    }
    fprintf(stderr, "Error : FunctionType::deepCopy() has not been implemented.\n");
    Type *newType = new FunctionType(newReturnType, newParamsType, this->paramsSe);
    return newType;
}

Type *ArrayType::deepCopy() {
    std::vector<int> lenVec;
    Type *currentType = this;
    ArrayType *parentType;
    while (currentType->isArray()) {
        lenVec.push_back(dynamic_cast<ArrayType *>(currentType)->getLength());
        currentType = dynamic_cast<ArrayType *>(currentType)->getElementType();
    }
    currentType = currentType->deepCopy();
    for (auto iter = lenVec.rbegin(); iter != lenVec.rend(); iter++) {
        parentType = new ArrayType(currentType, *iter);
        if (currentType->isArray()) {
            dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
        }
        currentType = parentType;
    }
    Type *newType = dynamic_cast<ArrayType *>(currentType);
    return newType;
}

void ArrayType::deepSetConst(bool value) {
    Type *currentType = this;
    while (currentType->isArray()) {
        currentType->setConst(value);
        currentType = dynamic_cast<ArrayType *>(currentType)->getElementType();
    }
    currentType->setConst(value);
}

Type *PointerType::deepCopy() {
    Type *newType = new PointerType(valueType->deepCopy(), this->constant);
    return newType;
}

std::string StringType::toStr() {
    std::ostringstream buffer;
    buffer << "const char[" << length << "]";
    return buffer.str();
}

Type *StringType::deepCopy() {
    fprintf(stderr, "Error : StringType::deepCopy() has not been implemented.\n");
    return new StringType(this->length);
}