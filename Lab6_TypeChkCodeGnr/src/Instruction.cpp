#include "Instruction.h"
#include "BasicBlock.h"
#include <iostream>
#include "Function.h"
#include "Type.h"
extern FILE* yyout;

Instruction::Instruction(int instType, BasicBlock *insert_bb)
{
    prev = next = this;
    opcode = -1;
    this->instType = instType;
    if (insert_bb != nullptr)
    {
        insert_bb->insertBack(this);
        parent = insert_bb;
    }
}

Instruction::~Instruction()
{
    parent->remove(this);
}

BasicBlock *Instruction::getParent()
{
    return parent;
}

void Instruction::setParent(BasicBlock *bb)
{
    parent = bb;
}

void Instruction::setNext(Instruction *inst)
{
    next = inst;
}

void Instruction::setPrev(Instruction *inst)
{
    prev = inst;
}

Instruction *Instruction::getNext()
{
    return next;
}

Instruction *Instruction::getPrev()
{
    return prev;
}

Operand *Instruction::getDef() {
    if (instType == -1 || instType == STORE || instType == COND || instType == UNCOND || instType == RET) {
        return nullptr;
    } else {
        return operands[0];
    }
}

int Instruction::getAlignNum(Type *type) {
    if (type->isInt() || type->isFloat()) {
        return 4;
    }
    if (type->isPtr()) {
        return sizeof(void *);
    }
    if (type->isArray()) {
        if (dynamic_cast<ArrayType *>(type)->getSize() / 4 < 4) {
            return 4;
        } else {
            return 16;
        }
    }
    return 4;
}

BinaryInstruction::BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb) : Instruction(BINARY, insert_bb)
{
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

BinaryInstruction::~BinaryInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void BinaryInstruction::output() const
{
    Type *type = operands[0]->getType();
    std::string dstStr, src1Str, src2Str, op, typeStr;
    dstStr = operands[0]->toStr();
    src1Str = operands[1]->toStr();
    src2Str = operands[2]->toStr();
    typeStr = operands[0]->getType()->toStr();
    switch (opcode)
    {
    case ADD:
        op = type->isInt() ? "add" : "fadd";
        break;
    case SUB:
        op = type->isInt() ? "sub" : "fsub";
        break;
    case STAR:
        op = type->isInt() ? "mul" : "fmul";
        break;
    case SLASH:
        op = type->isInt() ? "sdiv" : "fdiv";
        break;
    case PERCENT:
        op = "srem";
        break;
    case AND:
        op = "and";
        break;
    case OR:
        op = "or";
        break;
    case XOR:
        op = "xor";
    default:
        break;
    }

    if (operands[1]->getSymbolEntry()->isConstant() && operands[1]->getType()->isFloat()) {
        src1Str = SymbolEntry::getHexString(operands[1]->getSymbolEntry()->getValue());
    }
    if (operands[2]->getSymbolEntry()->isConstant() && operands[2]->getType()->isFloat()) {
        src2Str = SymbolEntry::getHexString(operands[2]->getSymbolEntry()->getValue());
    }

    fprintf(yyout, "  %s = %s %s %s, %s\n", dstStr.c_str(), op.c_str(), typeStr.c_str(), src1Str.c_str(), src2Str.c_str());
}

CmpInstruction::CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb): Instruction(CMP, insert_bb){
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

CmpInstruction::~CmpInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void CmpInstruction::output() const
{
    Type *type = operands[0]->getType();
    std::string cmpStr, dstStr, src1Str, src2Str, op, typeStr;
    cmpStr = type->isInt() ? "icmp" : "fcmp";
    dstStr = operands[0]->toStr();
    src1Str = operands[1]->toStr();
    src2Str = operands[2]->toStr();
    typeStr = operands[1]->getType()->toStr();
    switch (opcode)
    {
    case E:
        op = type->isInt() ? "eq" : "oeq";
        break;
    case NE:
        op = type->isInt() ? "ne" : "one";
        break;
    case L:
        op = type->isInt() ? "slt" : "olt";
        break;
    case LE:
        op = type->isInt() ? "sle" : "ole";
        break;
    case G:
        op = type->isInt() ? "sgt" : "ogt";
        break;
    case GE:
        op = type->isInt() ? "sge" : "oge";
        break;
    default:
        op = "";
        break;
    }

    fprintf(yyout, "  %s = %s %s %s %s, %s\n", dstStr.c_str(), cmpStr.c_str(), op.c_str(), typeStr.c_str(), src1Str.c_str(), src2Str.c_str());
}

UncondBrInstruction::UncondBrInstruction(BasicBlock *to, BasicBlock *insert_bb) : Instruction(UNCOND, insert_bb)
{
    branch = to;
}

void UncondBrInstruction::output() const
{
    fprintf(yyout, "  br label %%B%d\n", branch->getNo());
}

void UncondBrInstruction::setBranch(BasicBlock *bb)
{
    branch = bb;
}

BasicBlock *UncondBrInstruction::getBranch()
{
    return branch;
}

CondBrInstruction::CondBrInstruction(BasicBlock *true_branch, BasicBlock *false_branch, Operand *cond, BasicBlock *insert_bb) : Instruction(COND, insert_bb){
    this->true_branch = true_branch;
    this->false_branch = false_branch;
    cond->addUse(this);
    operands.push_back(cond);
}

CondBrInstruction::~CondBrInstruction()
{
    operands[0]->removeUse(this);
}

void CondBrInstruction::output() const
{
    std::string cond, type;
    cond = operands[0]->toStr();
    int true_label = true_branch->getNo();
    int false_label = false_branch->getNo();
    // br i1 <cond>, label <iftrue>, label <iffalse>
    fprintf(yyout, "  br i1 %s, label %%B%d, label %%B%d\n", cond.c_str(), true_label, false_label);
}

void CondBrInstruction::setFalseBranch(BasicBlock *bb)
{
    false_branch = bb;
}

BasicBlock *CondBrInstruction::getFalseBranch()
{
    return false_branch;
}

void CondBrInstruction::setTrueBranch(BasicBlock *bb)
{
    true_branch = bb;
}

BasicBlock *CondBrInstruction::getTrueBranch()
{
    return true_branch;
}

RetInstruction::RetInstruction(Operand *src, BasicBlock *insert_bb) : Instruction(RET, insert_bb)
{
    if(src != nullptr)
    {
        operands.push_back(src);
        src->addUse(this);
    }
}

RetInstruction::~RetInstruction()
{
    if(!operands.empty())
        operands[0]->removeUse(this);
}

void RetInstruction::output() const
{
    if(operands.empty())
    {
        fprintf(yyout, "  ret void\n");
    }
    else
    {
        std::string ret, type;
        ret = operands[0]->toStr();
        type = operands[0]->getType()->toStr();
        fprintf(yyout, "  ret %s %s\n", type.c_str(), ret.c_str());
    }
}

AllocaInstruction::AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb) : Instruction(ALLOCA, insert_bb)
{
    operands.push_back(dst);
    dst->setDef(this);
    this->se = se;
}

AllocaInstruction::~AllocaInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
}

void AllocaInstruction::output() const
{
    std::string dst, type;
    dst = operands[0]->toStr();
    type = se->getType()->toStr();
    int alignNum = getAlignNum(operands[0]->getType());
    // %2 = alloca [4 x [2 x [3 x i32]]], align 16
    fprintf(yyout, "  %s = alloca %s, align %d\n", dst.c_str(), type.c_str(), alignNum);
}

LoadInstruction::LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb) : Instruction(LOAD, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src_addr);
    dst->setDef(this);
    src_addr->addUse(this);
}

LoadInstruction::~LoadInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void LoadInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string src_type;
    std::string dst_type;
    dst_type = operands[0]->getType()->toStr();
    src_type = operands[1]->getType()->toStr();
    int alignNum = getAlignNum(operands[0]->getType());
    // %2 = load i32, i32* @idx1, align 4
    fprintf(yyout, "  %s = load %s, %s %s, align %d\n", dst.c_str(), dst_type.c_str(), src_type.c_str(), src.c_str(), alignNum);
}

StoreInstruction::StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb) : Instruction(STORE, insert_bb)
{
    operands.push_back(dst_addr);
    operands.push_back(src);
    dst_addr->addUse(this);
    src->addUse(this);
}

StoreInstruction::~StoreInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
}

void StoreInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string src_type = operands[1]->getType()->toStr();
    int alignNum = getAlignNum(operands[1]->getType());
    
    if (operands[1]->getSymbolEntry()->isConstant() && operands[1]->getType()->isFloat()) {
        src = SymbolEntry::getHexString(operands[1]->getSymbolEntry()->getValue());
        // Marker(std::to_string(operands[1]->getSymbolEntry()->getValue()) + " " + SymbolEntry::getHexString(operands[1]->getSymbolEntry()->getValue()));
    }
    fprintf(yyout, "  store %s %s, %s %s, align %d\n", src_type.c_str(), src.c_str(), dst_type.c_str(), dst.c_str(), alignNum);
}

//增加函数调用指令
CallInstruction::CallInstruction(Operand *dst, SymbolEntry *funcSe, std::vector<Operand *> params, BasicBlock *insert_bb) 
    : Instruction(CALL, insert_bb), funcSe(funcSe) {
        operands.push_back(dst); //设置返回值
        //返回值不为空，设置其定义指令def为本条指令
        if(dst)
            dst->setDef(this); 
        //遍历参数列表，依次放入指令的操作数operands中
        for(auto param : params){
            operands.push_back(param);
            param->addUse(this); //给参数设置调用它的指令（即当前指令）
        }
    } 

CallInstruction::~CallInstruction() 
{
    if (operands[0]) {
        operands[0]->setDef(nullptr);
        if (operands[0]->usersNum() == 0)
            delete operands[0];
    }
    for (int i = 1; i < (int)operands.size(); i++)
        operands[i]->removeUse(this);
}
    
void CallInstruction::output() const 
{
    fprintf(yyout, "  ");
    //如果操作数列表的第一个不为空 输出(即返回值不为空)
    if (operands[0]) {
        std::string dst0 = operands[0]->toStr();
        fprintf(yyout, "%s = ", dst0.c_str());
    }
    //输出函数返回类型和函数名
    FunctionType *ftype = dynamic_cast<FunctionType *>(funcSe->getType());
    std::string fname = funcSe->toStr();
    std::string rettype = ftype->getRetType()->toStr();
    fprintf(yyout, "call %s %s(", rettype.c_str(), fname.c_str());
    //输出参数列表
    for(int i = 1; i < (int)operands.size(); i++)
    {
        if(i != 1)
            fprintf(yyout, ", ");
        std::string pname = operands[i]->toStr();
        std::string ptype = operands[i]->getType()->toStr();
        fprintf(yyout, "%s %s", ptype.c_str(), pname.c_str());
    }
    fprintf(yyout, ")\n");
}

std::vector<Operand *> CallInstruction::getUse() {
    std::vector<Operand*> vec;
    for (auto iter = operands.begin() + 1; iter != operands.end(); iter++)
        vec.push_back(*iter);
    return vec;
}

//增加符号扩展指令(0填充)
ZextInstruction::ZextInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb) : Instruction(ZEXT, insert_bb) {
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this); //目的操作数本指令定义
    src->addUse(this); //源操作数本指令引用
}

ZextInstruction::~ZextInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void ZextInstruction::output() const {
    std::string dst = operands[0]->toStr();
    std::string srcname = operands[1]->toStr();
    std::string srctype = operands[1]->getType()->toStr();
    // %Y = zext i1 true to i32
    fprintf(yyout, "  %s = zext %s %s to i32\n", dst.c_str(), srctype.c_str(), srcname.c_str());
}

GepInstruction::GepInstruction(Operand *dst, Operand *arr, Operand *idx, BasicBlock *insert_bb, bool isParam) : Instruction(GEP, insert_bb) {
    operands.push_back(dst);
    operands.push_back(arr);
    operands.push_back(idx);
    dst->setDef(this);
    arr->addUse(this);
    idx->addUse(this);
    this->isParam = isParam;
}

GepInstruction::~GepInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void GepInstruction::output() const {
    Operand* dst = operands[0];
    Operand* arr = operands[1];
    Operand* idx = operands[2];
    PointerType *ptrArrType = dynamic_cast<PointerType *>(arr->getType());
    std::string firstIndex = !isParam ? ", i32 0" : "";
    // %27 = getelementptr inbounds [4 x [2 x [3 x i32]]], [4 x [2 x [3 x i32]]]* @b, i32 0, i32 %26    
    fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s%s, i32 %s\n", 
        dst->toStr().c_str(), 
        ptrArrType->getValueType()->toStr().c_str(),
        ptrArrType->toStr().c_str(), arr->toStr().c_str(), 
        firstIndex.c_str(), idx->toStr().c_str());
}

ItoFInstruction::ItoFInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb) : Instruction(ITOF, insert_bb){
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}
                
ItoFInstruction::~ItoFInstruction(){
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void ItoFInstruction::output() const{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dsttype = operands[0]->getType()->toStr();
    std::string srctype = operands[1]->getType()->toStr();
    fprintf(yyout, "  %s = sitofp %s %s to %s\n", 
        dst.c_str(), srctype.c_str(), src.c_str(), dsttype.c_str());
}

FtoIInstruction::FtoIInstruction(Operand* dst, Operand* src, BasicBlock* insert_bb) : Instruction(FTOI, insert_bb) {
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

FtoIInstruction::~FtoIInstruction(){
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void FtoIInstruction::output() const{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dsttype = operands[0]->getType()->toStr();
    std::string srctype = operands[1]->getType()->toStr();
    fprintf(yyout, "  %s = fptosi %s %s to %s\n", 
        dst.c_str(), srctype.c_str(), src.c_str(), dsttype.c_str());
}

BitcastInstruction::BitcastInstruction(Operand* dst, Operand* src, BasicBlock* insert_bb) : Instruction(BITCAST, insert_bb) {
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

BitcastInstruction::~BitcastInstruction() {
    operands[0]->setDef(nullptr);
    if (operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void BitcastInstruction::output() const {
    Operand *dst = operands[0];
    Operand *src = operands[1];
    // %2 = bitcast [2 x [3 x i32]]* %1 to i8*
    fprintf(yyout, "  %s = bitcast %s %s to %s\n", 
        dst->toStr().c_str(), src->getType()->toStr().c_str(), src->toStr().c_str(), dst->getType()->toStr().c_str());
}