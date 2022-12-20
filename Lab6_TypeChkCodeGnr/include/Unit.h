#ifndef __UNIT_H__
#define __UNIT_H__

#include <vector>
#include "Function.h"
#include <assert.h>
#include "Ast.h"

class Unit
{
    typedef std::vector<Function *>::iterator iterator;
    typedef std::vector<Function *>::reverse_iterator reverse_iterator;

private:
    std::vector<Function *> func_list; // 函数定义列表
    std::vector<SymbolEntry *> declare_list; // 函数声明列表
    std::vector<SymbolEntry *> global_list; // 全局变量列表
    std::vector<ExprNode *> global_initVal_list;
    Function *main;
public:
    Unit() = default;
    ~Unit() ;
    void insertFunc(Function *);
    void removeFunc(Function *);
    void insertDeclare(SymbolEntry *);
    void removeDeclare(SymbolEntry *);
    void insertGlobal(SymbolEntry *se, ExprNode *initVal);
    void removeGlobal(SymbolEntry *se);
    std::vector<Function *> &getFuncList() {return func_list; }
    std::vector<SymbolEntry *> &getDeclaseList() {return declare_list; }
    std::vector<SymbolEntry *> &getGlobalList() {return global_list; }
    Function *getMain() {return main; }
    void output() const;
    iterator begin() { return func_list.begin(); };
    iterator end() { return func_list.end(); };
    reverse_iterator rbegin() { return func_list.rbegin(); };
    reverse_iterator rend() { return func_list.rend(); };
};

#endif