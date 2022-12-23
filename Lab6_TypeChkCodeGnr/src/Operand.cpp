#include "Operand.h"
#include <sstream>
#include <algorithm>
#include <string.h>

std::string Operand::toStr() const
{
    std::string res = se->toStr();
    if (se->isVariable() && dynamic_cast<IdentifierSymbolEntry *>(se)->isGlobal()) {
        res = "@" + res;
    }
    return SymbolTable::getMappedLabelStr(res);
}

void Operand::removeUse(Instruction *inst)
{
    auto i = std::find(uses.begin(), uses.end(), inst);
    if(i != uses.end())
        uses.erase(i);
}

