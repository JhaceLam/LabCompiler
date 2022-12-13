#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;

Node::Node()
{
    seq = counter++;
}

void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if(inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode()
{
    Unit *unit = builder->getUnit();
    Function *func = new Function(unit, se);
    BasicBlock *entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.
    builder->setInsertBB(entry);

    stmt->genCode();

    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo
    */
   
}

void UnaryExpr::genCode()
{

}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    if (op == AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());
    }
    else if(op == OR)
    {
        // Todo
    }
    else if(op >= LESS && op <= GREATER)
    {
        // Todo
    }
    else if(op >= ADD && op <= SUB)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    new LoadInstruction(dst, addr, bb);
}

void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    // Todo
}

void InitValNode::genCode()
{

}

void CompoundStmt::genCode()
{
    // Todo
}

void SeqNode::genCode()
{
    // Todo
}

void DefNode::genCode()
{

}

void DeclStmt::genCode()
{
    /*
    IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(id->getSymPtr());
    if(se->isGlobal())
    {
        Operand *addr;
        SymbolEntry *addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
    }
    else if(se->isLocal())
    {
        Function *func = builder->getInsertBB()->getParent();
        BasicBlock *entry = func->getEntry();
        Instruction *alloca;
        Operand *addr;
        SymbolEntry *addr_se;
        Type *type;
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
        entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block.
        se->setAddr(addr);                                          // set the addr operand in symbol entry so that we can use it in subsequent code generation.
    }
    */
}

void ReturnStmt::genCode()
{
    // Todo
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    Operand *src = expr->getOperand();
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    new StoreInstruction(addr, src, bb);
}

void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    // Todo
}

void UnaryExpr::typeCheck()
{
    // Todo
}

void BinaryExpr::typeCheck()
{
    // Todo
}

void Constant::typeCheck()
{
    // Todo
}

void Id::typeCheck()
{
    // Todo
}

void IfStmt::typeCheck()
{
    // Todo
}

void IfElseStmt::typeCheck()
{
    // Todo
}

void CompoundStmt::typeCheck()
{
    // Todo
}

void SeqNode::typeCheck()
{
    // Todo
}

void DefNode::typeCheck()
{

}

void DeclStmt::typeCheck()
{
    // Todo
}

void ReturnStmt::typeCheck()
{
    // Todo
}

void AssignStmt::typeCheck()
{
    // Todo
}

void InitValNode::typeCheck()
{

}

Type* BinaryExpr::getArithmeticResultType(ExprNode *expr1, ExprNode *expr2) {
    Type *exprType;
    if (expr1->getType()->isIntFamily() && expr2->getType()->isIntFamily()) {
        if (expr1->getType()->isConst() && expr2->getType()->isConst()) {
            exprType = TypeSystem::constIntType;
        } else {
            exprType = TypeSystem::intType;
        }
    } else {
        if (expr1->getType()->isConst() && expr2->getType()->isConst()) {
            exprType = TypeSystem::constFloatType;
        } else {
            exprType = TypeSystem::floatType;
        }
    }
    return exprType;
}

Type* BinaryExpr::getRelationalResultType(ExprNode *expr1, ExprNode *expr2) {
    Type *exprType;
    if (expr1->getType()->isConst() && expr2->getType()->isConst()) {
        exprType = TypeSystem::constBoolType;
    } else {
        exprType = TypeSystem::boolType;
    }
    return exprType;
}

double BinaryExpr::getValue() {
    double val = 0;
    double val1 = expr1->getValue(), val2 = expr2->getValue();
    switch(op)
    {
        case ADD:
            val = val1 + val2;
            break;
        case SUB:
            val = val1 - val2;
            break;
        case STAR:
            val = val1 * val2;
            break;
        case SLASH:
            if (val2 != 0) {
                if (expr1->getType()->isIntFamily() && expr2->getType()->isIntFamily()) {
                    val = (int)val1 / (int)val2;
                } else {
                    val = val1 / val2;
                }
            } else {
                fprintf(stderr, "Error in BinaryExpr::getValue() : divided by zero");
            }
            break;
        case PERCENT:
            if (expr1->getType()->isIntFamily() && expr2->getType()->isIntFamily()) {
                if (val2 != 0) {
                    val = (int)val1 % (int)val2;
                } else {
                    fprintf(stderr, "Error in BinaryExpr::getValue() : divided by zero");
                }
            } else {
                fprintf(stderr, "Error in BinaryExpr::getValue() : float operands in MOD");
            }
            break;
        case AND:
            val = (int)val1 && (int)val2;
            break;
        case OR:
            val = (int)val1 || (int)val2;
            break;
        case LESS:
            val = (int)val1 < (int)val2;
            break;
        case EQ:
            val = (int)val1 == (int)val2;
            break;
        case NEQ:
            val = (int)val1 != (int)val2;
            break;
        case GREATER:
            val = (int)val1 > (int)val2;
            break;
        case GREATEQ:
            val = (int)val1 >= (int)val2;
            break;
        case LESSEQ:
            val = (int)val1 <= (int)val2;
            break;
    }
    return val;
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
        case GREATER:
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
    if (symbolEntry->getType()->isConst()) {
        fprintf(yyout, "%*cConstBinaryExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    } else {
        fprintf(yyout, "%*cBinaryExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    }
    expr1->output(level + 4);
    expr2->output(level + 4);
}

double UnaryExpr::getValue() {
    double val = 0;
    double val1 = expr->getValue();
    switch (op) {
        case NOT:
            val = !((int)val1);
            break;
        case SUB:
            val = -val1;
            break;
    }
    return val;
}

void UnaryExpr::output(int level)
{
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
    if (symbolEntry->getType()->isConst()) {
        fprintf(yyout, "%*cConstOneOpExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    } else {
        fprintf(yyout, "%*cOneOpExpr\t op: %s\t DataType: %s\n", 
            level, ' ', op_str.c_str(), expType.c_str());
    }
    expr->output(level + 4);
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

double Constant::getValue() {
    return symbolEntry->getValue();
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    std::string nodeName = symbolEntry->getType()->isIntFamily() ? 
        "IntegerLiteral" : "FloatLiteral";
    fprintf(yyout, "%*c%s\tvalue: %s\ttype: %s\n", level, ' ',
            nodeName.c_str(), value.c_str(), type.c_str());
}

double Id::getValue() {
    return symbolEntry->getValue();
}

Id::Id(SymbolEntry *se, ArrayIndexNode *idx) : ExprNode(se), index(idx) {
    Type *dstType;
    if (getType()->isInt()) {
        dstType = getType()->isConst() ? TypeSystem::constIntType : TypeSystem::intType;
    } else if (getType()->isFloat()) {
        dstType = getType()->isConst() ? TypeSystem::constFloatType : TypeSystem::floatType;
    } else if (getType()->isArray()) {
        dstType = new PointerType(dynamic_cast<ArrayType *>(getType())->getElementType(), getType()->isConst());
    }
    SymbolEntry *temp = new TemporarySymbolEntry(dstType, SymbolTable::getLabel()); 
    dst = new Operand(temp);
};

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    std::string constStr = getType()->isConst() ? "Const " : "";
    fprintf(yyout, "%*c%sId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
        constStr.c_str(), name.c_str(), scope, type.c_str());
    if (getType()->isArray() && index != nullptr) {
        index->output(level + 4);
    }
}

bool ArrayIndexNode::isConst() {
    for (ExprNode *expr : exprList) {
        if (!expr->getType()->isConst()) {
            return false;
        }
    }
    return true;
}

void ArrayIndexNode::output(int level)
{
    if (isConst()) {
        fprintf(yyout, "%*cConstArrayIndexNode:\n", level, ' ');
    } else {
        fprintf(yyout, "%*cArrayIndexNode:\n", level, ' ');
    }

    for(auto iter = exprList.begin(); iter != exprList.end(); iter++) {
        if ((*iter) == nullptr) {
            fprintf(yyout, "%*cNot Given\n", level + 4, ' ');
        } else {
            (*iter)->output(level + 4);
        }
    }
}

double InitValNode::getValue() {
    fprintf(stderr, "Error: call InitValNode::getValue()\n");
    return -1;
}

void InitValNode::append(ExprNode *next) {
    initValList.push_back(next);
}

bool InitValNode::isFull() {
    if (getType()->isArray()) {
        return (int)initValList.size() >= dynamic_cast<ArrayType *>(getType())->getLength();
    } else {
        fprintf(stderr, "ERROR in InitValNode::isFull()");
        return false;
    }
}

void InitValNode::fill() {
    if (!getType()->isArray()) {
        fprintf(stderr, "ERROR in InitValNode::fill()");
        return;
    }

    Type *elementType = dynamic_cast<ArrayType *>(getType())->getElementType();
    if (elementType->isArray()) {
        ArrayType *elementArrayType = dynamic_cast<ArrayType *>(elementType);
        elementArrayType = new ArrayType(elementArrayType->getElementType(), elementArrayType->getLength(), true);
        while (!isFull()) {
            InitValNode *node = new InitValNode(new ConstantSymbolEntry(elementArrayType));
            append(node);
        }
        for (ExprNode *expr : initValList) {
            dynamic_cast<InitValNode *>(expr)->fill();
        }
    } else {
        if (elementType->isInt()) elementType = TypeSystem::constIntType;
        if (elementType->isFloat()) elementType = TypeSystem::constFloatType;
        while (!isFull()) {
            ExprNode *node = new Constant(new ConstantSymbolEntry(elementType, 0.0));
            append(node);
        }
    }

    bool isConst = true;
    for (ExprNode *expr : initValList) {
        if (!expr->getType()->isConst()) {
            isConst = false;
            break;
        }
    }
    if (isConst) {
        getType()->setConst();
    }
}

void InitValNode::output(int level)
{
    std::string constStr = getType()->isConst() ? "Const" : "";
    std::string typeStr = getType()->toStr();
    fprintf(yyout, "%*c%sArrayInitValNode\ttype: %s\n", level, ' ', constStr.c_str(), typeStr.c_str());

    for (auto iter = initValList.begin(); iter != initValList.end(); iter++) {
        (*iter)->output(level + 4);
    }
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    stmt1->output(level);
    stmt2->output(level);
}

DefNode::DefNode(Id *id, ExprNode *initVal) : id(id)
{
    if (initVal) {
        this->initVal = initVal;
    } else {
        this->initVal = nullptr;
    }
}

void DefNode::output(int level)
{
    std::string constStr = isConst() ? "Const" : "";
    fprintf(yyout, "%*c%sDefNode\n", level, ' ', constStr.c_str());

    id->output(level + 4);
    if (initVal != nullptr) {
        initVal->output(level + 4);
    }
}

bool DeclStmt::isConst()
{
    for (DefNode *node : defNodeList) {
        if (!node->isConst()) {
            return false;
        }
    }
    return true;
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    for (DefNode *node : defNodeList) {
        node->output(level + 4);
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
    if (retValue) {
        retValue->output(level + 4);
    }
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
    if (paramsDecl) {
        paramsDecl->output(level + 4);
    }
    stmt->output(level + 4);
}

void FuncCallParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncCallParamsNode\n", level, ' ');
    for (ExprNode *node : paramsList) {
        node->output(level + 4);
    }
}

void FuncCallNode::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry *>(symbolEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
            level, ' ', name.c_str(), type.c_str(), scope);
    
    if(params != nullptr){
        params->output(level + 4);
    }
}

void WhileStmt::output(int level) {
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}

void BreakStmt::output(int level) {
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level) {
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ExprStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' '); 
    if (expr) {
        expr->output(level + 4);
    }
}

void EmptyStmt::output(int level) {
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}