#include "Unit.h"
#include "Type.h"
#include <string>
#include <stack>
#include <vector>
#include "Ast.h"

extern FILE* yyout;

void Unit::insertFunc(Function *f)
{
    func_list.push_back(f);
    if (f->getSymPtr()->toStr().compare("@main") == 0) {
        main = f;
    }
}

void Unit::removeFunc(Function *func)
{
    func_list.erase(std::find(func_list.begin(), func_list.end(), func));
}

void Unit::insertDeclare(SymbolEntry *se) {
    if (std::find(declare_list.begin(), declare_list.end(), se) == declare_list.end()) {
        declare_list.push_back(se);
    }    
}

void Unit::removeDeclare(SymbolEntry *se) {
    auto iter = std::find(declare_list.begin(), declare_list.end(), se);
    if (iter != declare_list.end()) {
        declare_list.erase(iter);
    }
}

void Unit::insertGlobal(SymbolEntry *se, ExprNode *initVal) {
    if (std::find(global_list.begin(), global_list.end(), se) == global_list.end()) {
        global_list.push_back(se);
        global_initVal_list.push_back(initVal);
    }
}

void Unit::removeGlobal(SymbolEntry *se) {
    int i;
    for (i = 0; i < static_cast<int>(global_list.size()); i++) {
        if (se == global_list[i]) {
            global_list.erase(global_list.begin() + i);
            global_initVal_list.erase(global_initVal_list.begin() + i);
            break;
        }
    }
}

void Unit::output() const
{   
    int cnt = -1;
    for (SymbolEntry *se : global_list) {
        cnt++;
        if (se->getType()->isInt()) {
            fprintf(yyout, "@%s = global %s %d, align 4\n", se->toStr().c_str(), 
                se->getType()->toStr().c_str(), (int)(se->getValue()));
            continue;
        }
        if (se->getType()->isFloat()) {
            std::string hexStr = SymbolEntry::getHexString(se->getValue());
            fprintf(yyout, "@%s = global %s %s, align 4\n",
                    se->toStr().c_str(), se->getType()->toStr().c_str(), hexStr.c_str());
            continue;
        }
        if (se->getType()->isArray()) {
            fprintf(yyout, "@%s = global ", se->toStr().c_str());
            if (dynamic_cast<IdentifierSymbolEntry *>(se)->getUseZeroinitializer()) {
                fprintf(yyout, "%s zeroinitializer", se->getType()->toStr().c_str());
                continue;
            }

            ArrayType *arrayType = dynamic_cast<ArrayType *>(se->getType());
            Type *baseType;
            double *arrayValue = static_cast<double *>(se->getArrayValue());
            int idx = 0;
            std::stack<ArrayType *> arrayTypeStack;
            std::stack<int> elemGenCntStack; // the number of element which has been generated
            std::stack<InitValNode *> initValNodeStack;
            arrayTypeStack.push(arrayType);
            elemGenCntStack.push(0);
            initValNodeStack.push(dynamic_cast<InitValNode *>(global_initVal_list[cnt]));
            while (!arrayTypeStack.empty()) {
                ArrayType *&currentType = arrayTypeStack.top();
                Type *elememtType = currentType->getElementType();
                if (initValNodeStack.top()->getUseZeroinitializer()) {
                    fprintf(yyout, "%s zeroinitializer", currentType->toStr().c_str());
                    arrayTypeStack.pop();
                    elemGenCntStack.pop();
                    initValNodeStack.pop();
                    if (arrayTypeStack.empty()) {
                        break;
                    }
                    elemGenCntStack.top()++;
                    continue;
                }
                if (!elememtType->isArray()) {
                    baseType = elememtType;
                    fprintf(yyout, "%s [", currentType->toStr().c_str());
                    for (int i = 0; i < currentType->getLength(); i++) {
                        if (i) {
                            fprintf(yyout, ", ");
                        }
                        if (elememtType->isInt()) {
                            fprintf(yyout, "i32 %d", static_cast<int>(arrayValue[idx++]));
                        } else {
                            std::string hexStr = SymbolEntry::getHexString(arrayValue[idx++]);
                            fprintf(yyout, "float %s", hexStr.c_str());
                        }
                    }
                    fprintf(yyout, "]");
                    arrayTypeStack.pop();
                    elemGenCntStack.pop();
                    initValNodeStack.pop();
                    if (arrayTypeStack.empty()) {
                        break;
                    }
                    elemGenCntStack.top()++;
                } else {
                    if (elemGenCntStack.top() < currentType->getLength()) {
                        if (!elemGenCntStack.top())
                            fprintf(yyout, "%s [", currentType->toStr().c_str());
                        else {
                            fprintf(yyout, ", ");
                        }
                        initValNodeStack.push(dynamic_cast<InitValNode *>(initValNodeStack.top()->getInitValList()[elemGenCntStack.top()])); 
                        arrayTypeStack.push(dynamic_cast<ArrayType *>(elememtType));
                        elemGenCntStack.push(0);
                    } else {
                        fprintf(yyout, "]");
                        arrayTypeStack.pop();
                        elemGenCntStack.pop();
                        initValNodeStack.pop();
                        if (arrayTypeStack.empty()) {
                            break;
                        }
                        elemGenCntStack.top()++;
                    }
                }
            }

            if (arrayType->getSize() / baseType->getSize() < 4) {
                fprintf(yyout, ", align 4\n");
            } else {
                fprintf(yyout, ", align 16\n");
            }
        }
    }
    fprintf(yyout, "\n");
    for (auto &func : func_list) {
        func->output();
        fprintf(yyout, "\n");
    }
    
    for (SymbolEntry *se : declare_list) {
        assert(se->getType()->isFunc());
        FunctionType* type = dynamic_cast<FunctionType *>(se->getType());
        std::string typeStr = type->toStr();
        std::string paramAndParenStr = typeStr.substr(typeStr.find('('));
        fprintf(yyout, "declare %s %s%s\n", 
            type->getRetType()->toStr().c_str(), se->toStr().c_str(), paramAndParenStr.c_str());
    }
}

Unit::~Unit()
{
    for(auto &func:func_list)
        delete func;
}
