#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
FloatType TypeSystem::commonFloat = FloatType();
ConstIntType TypeSystem::commonConstInt = ConstIntType();
ConstFloatType TypeSystem::commonConstFloat = ConstFloatType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::floatType = &commonFloat;
Type* TypeSystem::constIntType = &commonConstInt;
Type* TypeSystem::constFloatType = &commonConstFloat;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FloatType::toStr()
{
    return "float";
}

void FunctionType::setparamsType(std::vector<Type*> givenParamsType)
{
    paramsType = givenParamsType;
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for (int i = 0; i < (int)paramsType.size(); i++){
        if (i != 0) buffer << ", ";
        buffer << paramsType[i]->toStr();
    }
    buffer << ")";
    return buffer.str();
}

void IntArrayType::setDimension(int d)
{
    dimension = d;
}

std::string IntArrayType::toStr()
{
    std::ostringstream buffer;
    buffer  << "int array [" << dimension << " dimensions]" ;
    return buffer.str();
}

std::string ConstIntType::toStr()
{
    return "const int";
}

void ConstIntArrayType::setDimension(int d)
{
    dimension = d;
}

std::string ConstIntArrayType::toStr()
{
    std::ostringstream buffer;
    buffer  << "const int array [" << dimension << " dimensions]" ;
    return buffer.str();
}

std::string ConstFloatType::toStr()
{
    return "const float";
}

void FloatArrayType::setDimension(int d)
{
    dimension = d;
}

std::string FloatArrayType::toStr()
{
    std::ostringstream buffer;
    buffer  << "float array [" << dimension << " dimensions]" ;
    return buffer.str();
}

void ConstFloatArrayType::setDimension(int d)
{
    dimension = d;
}

std::string ConstFloatArrayType::toStr()
{
    std::ostringstream buffer;
    buffer  << "const float array [" << dimension << " dimensions]" ;
    return buffer.str();
}