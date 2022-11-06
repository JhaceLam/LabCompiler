#include "Ast.h"
#include "SymbolTable.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::counter = 0;

Node::Node()
{
    seq = counter++;
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

Type* ExprNode::getType()
{
    return symbolEntry->getType();
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case STAR:
            op_str = "star";
            break;
        case SLASH:
            op_str = "slash";
            break;
        case PERCENT:
            op_str = "percent";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case EQ:
            op_str = "eq";
            break;
        case NEQ:
            op_str = "neq";
            break;
        case GREAT:
            op_str = "great";
            break;
        case GREATEQ:
            op_str = "greateq";
            break;
        case LESSEQ:
            op_str = "lesseq";
            break;
    }

    std::string expType = symbolEntry->getType()->toStr();
    if (isConst) {
        fprintf(yyout, "%*cConstBinaryExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    } else {
        fprintf(yyout, "%*cBinaryExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    }
    expr1->output(level + 4);
    expr2->output(level + 4);
}

Type* BinaryExpr::getResultType(ExprNode *exp1, ExprNode *exp2) {
    Type *expType;
    if (exp1->getType()->isIntFamily() && exp2->getType()->isIntFamily()) {
        if (exp1->getType()->isConst() && exp2->getType()->isConst()) {
            expType = TypeSystem::constIntType;
        } else {
            expType = TypeSystem::intType;
        }
    } else {
        if (exp1->getType()->isConst() && exp2->getType()->isConst()) {
            expType = TypeSystem::constFloatType;
        } else {
            expType = TypeSystem::floatType;
        }
    }
    return expType;
}

Type* BinaryExpr::getRelResultType(ExprNode *exp1, ExprNode *exp2) {
    Type *expType;
    if (exp1->getType()->isConst() && exp2->getType()->isConst()) {
        expType = TypeSystem::constIntType;
    } else {
        expType = TypeSystem::intType;
    }
    return expType;
}

void OneOpExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
    }

    std::string expType = symbolEntry->getType()->toStr();
    if (isConst) {
        fprintf(yyout, "%*cConstOneOpExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    } else {
        fprintf(yyout, "%*cOneOpExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    }
    expr->output(level + 4);
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    std::string nodeName = symbolEntry->getType()->isInt() ? 
        "IntegerLiteral" : "FloatLiteral";
    fprintf(yyout, "%*c%s\tvalue: %s\ttype: %s\n", level, ' ',
            nodeName.c_str(), value.c_str(), type.c_str());
}

void ArrayIndexNode::append(ExprNode *next)
{
    exprList.push_back(next);
}

int ArrayIndexNode::getDemension()
{
    return exprList.size();
}

void ArrayIndexNode::output(int level)
{
    if (isConst) {
        fprintf(yyout, "%*cConstArrayIndexNode:\n", level, ' ');
    } else {
        fprintf(yyout, "%*cArrayIndexNode:\n", level, ' ');
    }
    for(std::vector<ExprNode *>::iterator iter = exprList.begin(); 
    iter != exprList.end(); iter++) {
        (*iter)->output(level + 4);
    }
}

bool Id::isArray()
{
    return symbolEntry->getType()->isArray();
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    std::string constStr = isConst ? "Const " : "";
    fprintf(yyout, "%*c%sId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
        constStr.c_str(), name.c_str(), scope, type.c_str());
    if (isArray() && index != nullptr) {
        index->output(level + 4);
    }
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if (stmt == nullptr) {
        fprintf(yyout, "%*cNullStmt\n", level + 4, ' ');
    } else {
        stmt->output(level + 4);
    }
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void InitValNode::append(InitValNode *next)
{
    initValList.push_back(next);
}

void InitValNode::output(int level)
{
    if (isConst) {
        fprintf(yyout, "%*cConstInitValNode\n", level, ' ');
    } else {
        fprintf(yyout, "%*cInitValNode\n", level, ' ');
    }
    for (std::vector<InitValNode *>::iterator iter = initValList.begin(); 
    iter != initValList.end(); iter++) {
        (*iter)->output(level + 4);
    }
    if (expr != nullptr) {
        expr->output(level + 4);
    }
}

bool DefNode::isArray()
{
    return id->isArray();
}

void DefNode::output(int level)
{
    std::string constStr = isConst ? "Const" : "";
    std::string arrayStr = isArray() ? "Array" : "";
    std::string typeStr = id->getType()->isIntFamily() ? "Int" : "Float";
    fprintf(yyout, "%*cDefNode - %s %s %s \n", level, ' ', 
        constStr.c_str(), typeStr.c_str(), arrayStr.c_str());
    id->output(level + 4);
    if (initVal != nullptr) {
        initVal->output(level + 4);
    } else {
        fprintf(yyout, "%*cNo initial value\n", level + 4, ' ');
    }
}

void DeclStmt::append(DefNode *next)
{
    varDefList.push_back(next);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    for (std::vector<DefNode *>::iterator iter = varDefList.begin(); 
    iter != varDefList.end(); iter++) {
        (*iter)->output(level + 4);
    }
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    loopStmt->output(level + 4);
}

void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    stmt->output(level + 4);
}
