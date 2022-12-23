#include "Function.h"
#include "Unit.h"
#include "Type.h"
#include <list>

extern FILE* yyout;

Function::Function(Unit *u, SymbolEntry *s)
{
    assert(s->isVariable());
    entry = new BasicBlock(this);
    sym_ptr = s;
    parent = u;
    dynamic_cast<IdentifierSymbolEntry *>(s)->setFunction(this);
    u->insertFunc(this);
    lastAlloca = nullptr;
}

Function::~Function()
{
    /*
    auto delete_list = block_list;
    for (auto &i : delete_list)
        delete i;
    parent->removeFunc(this);
    */
}

// remove the basicblock bb from its block_list.
void Function::remove(BasicBlock *bb)
{
    block_list.erase(std::find(block_list.begin(), block_list.end(), bb));
}

void Function::output() const
{
    SymbolTable::resetLabelMap();

    FunctionType *funcType = dynamic_cast<FunctionType *>(sym_ptr->getType());
    Type *retType = funcType->getRetType();
    std::vector<Type *> paramsType = funcType->getParamsType();
    std::vector<SymbolEntry *> paramsSe = funcType->getParamsSe();
    if (!paramsSe.size()) {
        fprintf(yyout, "define %s %s() {\n", retType->toStr().c_str(), sym_ptr->toStr().c_str());
    } else {
        fprintf(yyout, "define %s %s(", retType->toStr().c_str(), sym_ptr->toStr().c_str());
        for (int i = 0; i < (int)paramsSe.size(); i++) {
            if (i) {
                fprintf(yyout, ", ");
            }
            std::string labelStr = SymbolTable::getMappedLabelStr(paramsSe[i]->toStr());
            fprintf(yyout, "%s %s", paramsType[i]->toStr().c_str(), labelStr.c_str());
        }
        fprintf(yyout, ") {\n");
    }
    
    // dfs
    std::set<BasicBlock *> visited;
    std::list<BasicBlock *> q;
    q.push_back(entry);
    visited.insert(entry);
    while (!q.empty())
    {
        auto bb = q.front();
        q.pop_front();
        bb->output();
        for (auto succ = bb->succ_begin(); succ != bb->succ_end(); succ++)
        {
            if (visited.find(*succ) == visited.end())
            {
                visited.insert(*succ);
                q.push_back(*succ);
            }
        }
    }

    fprintf(yyout, "}\n");
}

void Function::addAlloca(Instruction *inst) {
    if (!lastAlloca) {
        entry->insertFront(inst);
    } else {
        entry->insertBefore(inst, lastAlloca->getNext());
    }
    lastAlloca = inst;
}