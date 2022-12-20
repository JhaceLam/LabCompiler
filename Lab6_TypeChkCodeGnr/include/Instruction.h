#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "Operand.h"
#include <vector>
#include <map>

class BasicBlock;

class Instruction
{
public:
    Instruction(int instType, BasicBlock *insert_bb = nullptr);
    virtual ~Instruction();
    int getInstType() {return instType; }
    bool isBin() const { return instType == BINARY; };
    bool isUncond() const {return instType == UNCOND; };
    bool isCond() const {return instType == COND; };
    bool isRet() const {return instType == RET; }; //函数返回指令
    bool isLoad() const {return instType == LOAD; };
    bool isStore() const {return instType == STORE; }
    bool isCmp() const {return instType == CMP; };
    bool isAlloc() const {return instType == ALLOCA; };
    bool isCall() const {return instType == CALL; };
    bool isZext() const {return instType == ZEXT; };
    bool isGep() const {return instType == GEP; };
    bool isIntToFloat() const {return instType == ITOF; };
    bool isFloatToInt() const {return instType == FTOI; };
    bool isBitCast() const {return instType == BITCAST; };
    BasicBlock *getParent();
    void setParent(BasicBlock *);
    void setNext(Instruction *);
    void setPrev(Instruction *);
    Instruction *getNext();
    Instruction *getPrev();
    virtual void output() const = 0;
    virtual std::vector<Operand *> getUse() {return std::vector<Operand *>(); }
    Operand *getDef();
    static int getAlignNum(Type *type);

protected:
    int instType;
    unsigned opcode;
    Instruction *prev; 
    Instruction *next;
    BasicBlock *parent;
    std::vector<Operand*> operands;
    enum {BINARY, COND, UNCOND, RET, LOAD, STORE, CMP, ALLOCA, CALL, ZEXT, GEP, ITOF, FTOI, BITCAST};
};

// meaningless instruction, used as the head node of the instruction list.
class DummyInstruction : public Instruction
{
public:
    DummyInstruction() : Instruction(-1, nullptr) {};
    void output() const {};
};

class AllocaInstruction : public Instruction
{
public:
    AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb = nullptr);
    ~AllocaInstruction();
    void output() const;
private:
    SymbolEntry *se;
};

class LoadInstruction : public Instruction
{
public:
    LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb = nullptr);
    ~LoadInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1]}); }
};

class StoreInstruction : public Instruction
{
public:
    StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb = nullptr);
    ~StoreInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[0], operands[1]}); }
};

class BinaryInstruction : public Instruction
{
public:
    BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~BinaryInstruction();
    void output() const;
    enum {ADD, SUB, STAR, SLASH, PERCENT, AND, OR, XOR};
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1], operands[2]}); }
};

class CmpInstruction : public Instruction
{
public:
    CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~CmpInstruction();
    void output() const;
    enum {E, NE, L, GE, G, LE};
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1], operands[2]}); }
};

// unconditional branch
class UncondBrInstruction : public Instruction
{
public:
    UncondBrInstruction(BasicBlock *to, BasicBlock *insert_bb = nullptr);
    void output() const;
    void setBranch(BasicBlock *);
    BasicBlock *getBranch();
protected:
    BasicBlock *branch;
};

// conditional branch
class CondBrInstruction : public Instruction
{
public:
    CondBrInstruction(BasicBlock *true_branch, BasicBlock *false_branch, Operand *cond, BasicBlock *insert_bb = nullptr);
    ~CondBrInstruction();
    void output() const;
    void setTrueBranch(BasicBlock*);
    BasicBlock* getTrueBranch();
    void setFalseBranch(BasicBlock*);
    BasicBlock* getFalseBranch();
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[0]}); }
protected:
    BasicBlock* true_branch;
    BasicBlock* false_branch;
};

class RetInstruction : public Instruction
{
public:
    RetInstruction(Operand *src, BasicBlock *insert_bb = nullptr);
    ~RetInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return operands.size() ? std::vector<Operand *>({operands[0]}) : std::vector<Operand *>(); }
};

//增加函数调用指令
class CallInstruction : public Instruction 
{
private:
    SymbolEntry* funcSe;
    
public:
    CallInstruction(Operand *dst, SymbolEntry* funcSe, std::vector<Operand*> params, BasicBlock *insert_bb = nullptr);
    ~CallInstruction();
    void output() const;
    std::vector<Operand *> getUse();
};

//增加符号扩展指令(0填充)
class ZextInstruction : public Instruction
{
public:
    ZextInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb = nullptr);
    //dst是扩展后的操作数，src是源操作数
    ~ZextInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1]}); }
};

class GepInstruction : public Instruction {
private:
    bool isParam; // true: arr[][idx1][idx2]   false: arr[idx1][idx2]
public:
    GepInstruction(Operand *dst, Operand *arr, Operand *idx, BasicBlock *insert_bb = nullptr, bool isParam = false);
    ~GepInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1], operands[2]}); }
};

//增加浮点整型转换指令
class FtoIInstruction : public Instruction{
public:
    FtoIInstruction(Operand* dst, Operand* src, BasicBlock* insert_bb = nullptr);
    ~FtoIInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1]}); }
};

class ItoFInstruction : public Instruction{
public:
    ItoFInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb = nullptr);
    ~ItoFInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1]}); }
};

class BitcastInstruction : public Instruction {
public:
    BitcastInstruction(Operand* dst, Operand* src, BasicBlock* insert_bb = nullptr);
    ~BitcastInstruction();
    void output() const;
    std::vector<Operand *> getUse() {return std::vector<Operand *>({operands[1]}); }
};

#endif