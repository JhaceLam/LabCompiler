#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
ConstIntType TypeSystem::commonConstInt = ConstIntType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::constIntType = &commonConstInt;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "()";
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