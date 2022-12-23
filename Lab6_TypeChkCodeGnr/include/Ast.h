#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <stack>
#include "Operand.h"
#include "Type.h"

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;
class Type;

class Node
{
private:
    static int counter;
    int seq;
protected:
    std::vector<Instruction*> true_list;
    std::vector<Instruction*> false_list;
    static IRBuilder *builder;
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb, bool setTrueBranch = true);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);
    bool typeCheckDone;

public:
    Node();
    int getSeq() const {return seq;};
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    virtual void typeCheck() = 0;
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
    int kind;
public:
    enum {EXPR, BINARY, UNARY, CONST, ID, INITVAL, CALL, CAST};
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry) {kind = EXPR; typeCheckDone = false; }
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    Type *getType() {return symbolEntry->getType(); }
    virtual Type *getFormedType() {return getType(); }
    bool isId() {return kind == ID; }
    bool isFuncCallExpr() {return kind == CALL; }
    bool isImplicitCastExpr() {return kind == CAST; }
    bool isBinaryExpr() {return kind == BINARY; }
    bool isUnaryExpr() {return kind == UNARY; }
    bool isInitValNode() {return kind == INITVAL; }
    virtual double getValue() = 0;
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
        AND, OR, LESS, LESSEQ, GREATER, GREATEQ, EQ, NEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2);
    static Type *getArithmeticResultType(ExprNode *expr1, ExprNode *expr2);
    static Type *getRelationalResultType(ExprNode *expr1, ExprNode *expr2);
    void output(int level);
    void typeCheck();
    void genCode();
    double getValue();
};

class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {SUB, NOT}; // NOT is not used, cause in parser.y 'NOT UnaryExp' in converted into BinaryExpr::EQ
    UnaryExpr(SymbolEntry *se, int op, ExprNode* expr);
    ExprNode *getExpr() {return expr; }
    void output(int level);
    void typeCheck();
    void genCode();
    double getValue();
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se) {dst = new Operand(se); };
    void output(int level);
    double getValue();
    void typeCheck();
    void genCode();
};

class ArrayIndexNode : public StmtNode
{
private:
    std::vector<ExprNode *> exprList;
public:
    ArrayIndexNode() {};
    bool isConst();
    void append(ExprNode *next) {exprList.push_back(next); }
    void insert(ExprNode *next) {exprList.insert(exprList.begin(), next); }
    std::vector<ExprNode *> &getExprList() {return exprList; }
    void output(int level);
    void typeCheck() {}
    void genCode() {}
};

class Id : public ExprNode
{
private:
    ArrayIndexNode *index;
    Type *formedType;
    bool isLVal;
public:
    Id(SymbolEntry *se, ArrayIndexNode *idx = nullptr);
    Type *getFormedType() {return formedType; }
    void output(int level);
    double getValue();
    void typeCheck();
    void genCode();
    bool getIsLVal() {return isLVal; }
    void setIsLVal(bool val = true) {isLVal = val; }
};

class InitValNode : public ExprNode
{
private:
    std::vector<ExprNode *> initValList;
    bool useZeroinitializer;
public:
    InitValNode(SymbolEntry *se) : ExprNode(se), useZeroinitializer(false) {dst = new Operand(se); kind = INITVAL; }
    void append(ExprNode *next);
    bool isFull();
    void fill();
    std::vector<ExprNode *> &getInitValList() {return initValList; }
    void output(int level);
    double getValue(); // should not be called
    void typeCheck();
    void genCode();
    void setUseZeroinitializer(bool val = true) {useZeroinitializer = val; }
    bool getUseZeroinitializer() {return useZeroinitializer; }
};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class DefNode : public StmtNode
{
private:
    Id *id;
    ExprNode *initVal;
public:
    DefNode(Id *id, ExprNode *initVal = nullptr);
    bool isConst() {return id->getType()->isConst(); }
    bool isArray() {return id->getType()->isArray(); }
    Id* getId() {return id; }
    void output(int level);
    void typeCheck();
    void genCode();

    static bool hasDeclareMemset;
    static bool hasDeclareMemcpy;
};

class DeclStmt : public StmtNode
{
private:
    std::vector<DefNode *> defNodeList;
public:
    DeclStmt() {};
    bool isConst();
    void append(DefNode *next) {defNodeList.push_back(next); }
    std::vector<DefNode *> &getDefNodeList() {return defNodeList; }
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt) {typeCheckDone = false; typeCheck(); }
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : 
        cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {typeCheckDone = false; typeCheck(); };
    void output(int level);
    void typeCheck();
    void genCode();
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode *retValue = nullptr) : retValue(retValue) {typeCheck(); }
    void output(int level);
    void typeCheck() {}
    void genCode();
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) { typeCheckDone = false; typeCheck(); };
    void output(int level);
    void typeCheck();
    void genCode();
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    DeclStmt *paramsDecl;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, DeclStmt *paramsDecl, StmtNode *stmt) : 
        se(se), paramsDecl(paramsDecl), stmt(stmt) {};
    SymbolEntry *getSymbolEntry() {return se; }
    void output(int level);
    void typeCheck();
    void genCode();
};

class FuncCallParamsNode : public StmtNode
{
private:
    std::vector<ExprNode *> paramsList;
public:
    FuncCallParamsNode() {};
    void append(ExprNode *next) {paramsList.push_back(next); };
    void output(int level);
    void typeCheck() {}
    void genCode();
    std::vector<ExprNode *> &getParamslist() {return paramsList;};
};

class FuncCallExpr : public ExprNode
{
private:
    FuncCallParamsNode* params;
    Type *formedType;
public:
    FuncCallExpr(SymbolEntry *se, FuncCallParamsNode *params = nullptr);
    void output(int level);
    void typeCheck();
    void genCode();
    double getValue() {return 0; }
    Type *getFormedType() {return formedType; }
};

class ImplicitCastExpr : public ExprNode
{
private:
    ExprNode* expr;
    Type *castType;
public:
    ImplicitCastExpr(ExprNode *expr, Type *castType);
    void output(int level);
    void typeCheck() {}
    void genCode();
    double getValue();
    Type *getFormedType() {return castType; }
    static ExprNode *floatToBool(ExprNode *srcExpr);
    static ExprNode *intToBool(ExprNode *srcExpr);
    static ExprNode *intToFloat(ExprNode *srcExpr);
    static ExprNode *floatToInt(ExprNode *srcExpr);
};

class ExprStmt : public StmtNode {
private:
    ExprNode* expr;
public:
    ExprStmt(ExprNode* expr) : expr(expr) {};
    void output(int level);
    void typeCheck() {}
    void genCode();
};

class EmptyStmt : public StmtNode {
public:
    EmptyStmt() {};
    void output(int level);
    void typeCheck() {}
    void genCode() {}
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;
    BasicBlock* condbb;
    BasicBlock* endbb;
public:
    WhileStmt(ExprNode *cond, StmtNode *stmt = nullptr) : cond(cond), stmt(stmt) {typeCheckDone = false; typeCheck(); };
    void setStmt(StmtNode *stmt) {this->stmt = stmt; }
    void output(int level);
    void typeCheck();
    void genCode();
    BasicBlock* getcondbb() {return this->condbb;}
    BasicBlock* getendbb() {return this->endbb;}
};

class BreakStmt : public StmtNode
{
private:
    StmtNode *whileStmt;
public:
    BreakStmt(StmtNode *whileStmt) : whileStmt(whileStmt) {typeCheckDone = true; };
    void output(int level);
    void typeCheck() {}
    void genCode();
};

class ContinueStmt : public StmtNode
{
private:
    StmtNode *whileStmt;
public:
    ContinueStmt(StmtNode* whileStmt) : whileStmt(whileStmt) {typeCheckDone = true; };
    void output(int level);
    void typeCheck() {}
    void genCode();
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    void typeCheck();
    void genCode(Unit *unit);
};

#endif