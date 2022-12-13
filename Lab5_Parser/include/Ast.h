#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
#include "SymbolTable.h"
#include "Type.h"

class SymbolEntry;
class Type;

class Node
{
private:
    static int counter;
    int seq;
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
public:
    bool isConst;
    ExprNode(SymbolEntry *symbolEntry, bool isConst = false) : 
        symbolEntry(symbolEntry), isConst(isConst) {};
    Type* getType();
};

class StmtNode : public Node
{};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, STAR, SLASH, PERCENT, 
        AND, OR, LESS, EQ, NEQ, GREAT, GREATEQ, LESSEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : 
        ExprNode(se, expr1->isConst && expr2->isConst), 
        op(op), expr1(expr1), expr2(expr2){};
    void output(int level);

    static Type *getResultType(ExprNode *exp1, ExprNode *exp2);
    static Type *getRelResultType(ExprNode *exp1, ExprNode *exp2);
};

class OneOpExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {SUB, NOT};
    OneOpExpr(SymbolEntry *se, int op, ExprNode* expr): 
        ExprNode(se, expr->isConst), op(op), expr(expr){};
    void output(int level);
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se, true){};
    void output(int level);
};

class ArrayIndexNode : public StmtNode
{
private:
    std::vector<ExprNode *> exprList;
public:
    bool isConst;
    ArrayIndexNode(bool isConst = false) : isConst(isConst) {};
    void append(ExprNode *next);
    void insert(ExprNode *next);
    int getDemension();
    void output(int level);
};

class Id : public ExprNode
{
private:
    ArrayIndexNode *index;
public:
    Id(SymbolEntry *se) : 
        ExprNode(se, se->getType()->isConst()), index(nullptr) {};
    Id(SymbolEntry *se, ArrayIndexNode *idx) : 
        ExprNode(se, se->getType()->isConst()), index(idx) {};
    bool isArray();
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
    void output(int level);
};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1( ), stmt2(stmt2){};
    void output(int level);
};

class InitValNode: public StmtNode
{
private:
    ExprNode *expr;
    std::vector<InitValNode *> initValList;
public:
    bool isConst;
    InitValNode(ExprNode *expr1 = nullptr, bool isConst = false) : 
        expr(expr1), isConst(isConst) {};
    void append(InitValNode *next);
    void output(int level);
};

class DefNode : public StmtNode
{
private:
    Id *id;
    InitValNode *initVal;
public:
    bool isConst;
    DefNode(Id *id, InitValNode *initVal, bool isConst = false) : 
        id(id), initVal(initVal), isConst(isConst) {};
    bool isArray();
    Id* getId() {return id;}
    void output(int level);
};

class DeclStmt : public StmtNode
{
private:
    std::vector<DefNode *> varDefList;
public:
    bool isConst;
    DeclStmt(bool isConst = false) : isConst(isConst) {};
    void append(DefNode *next);
    void output(int level);
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *loopStmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *loopStmt) : 
        cond(cond), loopStmt(loopStmt) {};
    void output(int level);
};

class BreakStmt : public StmtNode
{
public:
    void output(int level);
};

class ContinueStmt : public StmtNode
{
public:
    void output(int level);
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
};

class FuncDefParamsNode : public StmtNode
{
private:
    std::vector<Id*> paramsList;
public:
    FuncDefParamsNode() {};
    void append(Id* next);
    std::vector<Type*> getParamsType();
    void output(int level);
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FuncDefParamsNode *params;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, FuncDefParamsNode *params, StmtNode *stmt) : 
        se(se), params(params), stmt(stmt){};
    void output(int level);
};

class FuncCallParamsNode : public StmtNode
{
private:
    std::vector<ExprNode *> paramsList;
public:
    FuncCallParamsNode(){};
    void append(ExprNode *next);
    void output(int level);
};

class FuncCallNode : public ExprNode
{
private:
    Id* funcId;
    FuncCallParamsNode* params;
public:
    FuncCallNode(SymbolEntry *se, Id* id, FuncCallParamsNode* params) : 
        ExprNode(se), funcId(id), params(params){};
    void output(int level);
};

class ExpStmt : public StmtNode
{
private:
    ExprNode *exp;
public:
    ExpStmt(ExprNode *exp1) : exp(exp1) {};
    void output(int level);
};

class EmptyStmt : public StmtNode
{
public:
    EmptyStmt(){};
    void output(int level);
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};

#endif
