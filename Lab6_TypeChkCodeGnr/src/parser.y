%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    #include <cstring>
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type *declType; // The Basic Type in DeclStmt
    ArrayType *initArrayType; // ArrayType for InitValNode
    std::stack<InitValNode *> initValNodeStack; // Used for initializing array
    int lbraceCount = 0;
    int idx;
    double *initArrayValue; 
    int intParamNo;
    int floatParamNo;
    int stackParamNo;
    std::stack<StmtNode *> whileStack;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    float ftype;
    char *strtype;
    StmtNode *stmttype;
    ExprNode *exprtype;
    Type *type;
    SymbolEntry *se;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATNUM
%token IF ELSE WHILE BREAK CONTINUE
%token INT VOID CONST FLOAT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA LBRACKET RBRACKET
%token ADD SUB STAR SLASH PERCENT AND OR NOT LESS LESSEQ GREATER GREATEQ EQ NEQ ASSIGN
%token RETURN

%type <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef VarDeclStmt
%type <stmttype> ExprStmt EmptyStmt WhileStmt BreakStmt ContinueStmt
%type <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp StarExp UnaryExp
%type <type> Type
%type <stmttype> ArrayIndex VarDef VarDefList ConstDeclStmt ConstDefList ConstDef
%type <stmttype> FuncArrayIndex FuncFParam FuncFParams FuncRParams
%type <exprtype> InitVal InitValList

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {$$=$1; }
    | BlockStmt {$$=$1; }
    | IfStmt {$$=$1; }
    | ReturnStmt {$$=$1; }
    | DeclStmt {$$=$1; }
    | FuncDef {$$=$1; }
    | ExprStmt {$$ = $1; }
    | EmptyStmt {$$ = $1; }
    | WhileStmt {$$ = $1; }
    | BreakStmt {$$ = $1; }
    | ContinueStmt {$$ = $1; }
    ;
VarDef
    :
    ID {
        SymbolEntry *se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        ExprNode *initVal;
        if (declType->isInt()) {
            initVal = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType));
        } else {
            initVal = new Constant(new ConstantSymbolEntry(TypeSystem::constFloatType));
        }
        $$ = new DefNode(new Id(se), initVal);

        delete []$1;
    }
    |
    ID ASSIGN InitVal {
        SymbolEntry *se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        $$ = new DefNode(new Id(se), $3);

        delete []$1;
    }
    |
    ID ArrayIndex {
        if (!dynamic_cast<ArrayIndexNode *>($2)->isConst()) {
            fprintf(stderr, "Error in VarDef -> ID ConstArrayIndex ASSIGN InitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>($2)->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);

        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));
        SymbolEntry *seForInitVal = new ConstantSymbolEntry(initArrayType, initArrayValue);
        InitValNode *initValNode = new InitValNode(seForInitVal);
        initValNode->fill();

        Type *seType = initArrayType->deepCopy();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, $1, identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        Id *id = new Id(se, dynamic_cast<ArrayIndexNode *>($2));
        $$ = new DefNode(id, initValNode);
  
        delete []$1;
    }
    |
    ID ArrayIndex ASSIGN {
        if (!dynamic_cast<ArrayIndexNode *>($2)->isConst()) {
            fprintf(stderr, "Error in VarDef -> ID ConstArrayIndex ASSIGN InitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>($2)->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);
        while (!initValNodeStack.empty()) {
            initValNodeStack.pop();
        }

        idx = 0;
        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));

        Type *seType = initArrayType->deepCopy();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, $1, identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        $<se>$ = se;
    } 
    InitVal {
        Id *id = new Id($<se>4, dynamic_cast<ArrayIndexNode *>($2));
        $$ = new DefNode(id, $5);

        delete []$1;
    }
    ;
VarDefList
    :
    VarDefList COMMA VarDef {
        DeclStmt *node = dynamic_cast<DeclStmt *>($1);
        node->append(dynamic_cast<DefNode *>($3));
        $$ = node;
    }
    |
    VarDef {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>($1));
        $$ = node;
    }
    ;
ConstDef
    :
    ID ASSIGN InitVal {
        if (!($3->getType()->isConst())) {
            fprintf(stderr, "Error in ConstDef -> ID ASSIGN ConstInitVal : not ConstInitVal\n");
        }

        SymbolEntry *se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        $$ = new DefNode(new Id(se), $3);

        delete []$1;
    }
    |
    ID ArrayIndex ASSIGN {
        if (!dynamic_cast<ArrayIndexNode *>($2)->isConst()) {
            fprintf(stderr, "Error in ConstDef -> ID ConstArrayIndex ASSIGN ConstInitVal : not ConstArrayIndex\n");
        }

        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>($2)->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter)->getValue());
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        initArrayType = dynamic_cast<ArrayType *>(currentType);
        while (!initValNodeStack.empty()) {
            initValNodeStack.pop();
        }

        idx = 0;
        initArrayValue = new double[initArrayType->getSize() / declType->getSize()];
        memset(initArrayValue, 0, initArrayType->getSize() / declType->getSize() * sizeof(double));

        Type *seType = initArrayType->deepCopy();
        dynamic_cast<ArrayType *>(seType)->deepSetConst();
        SymbolEntry* se = new IdentifierSymbolEntry(seType, $1, identifiers->getLevel());
        se->setArrayValue(initArrayValue);
        if (!identifiers->install($1, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $1);
        }
        $<se>$ = se;
    } 
    InitVal {
        if (!($5->getType()->isConst())) {
            fprintf(stderr, "Error in ConstDef -> ID ConstArrayIndex ASSIGN ConstInitVal : not ConstInitVal\n");
        }

        Id *id = new Id($<se>4, dynamic_cast<ArrayIndexNode *>($2));
        $$ = new DefNode(id, $5);

        delete []$1;
    }
    ;
ConstDefList
    :
    ConstDefList COMMA ConstDef {
        DeclStmt *node = dynamic_cast<DeclStmt *>($1);
        node->append(dynamic_cast<DefNode *>($3));
        $$ = node;
    }
    |
    ConstDef {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>($1));
        $$ = node;
    }
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "Error: identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    | ID ArrayIndex {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "Error: identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se, (ArrayIndexNode *)$2 );
        delete []$1;
    }
    ;
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);} 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    |
    RETURN SEMICOLON {
        $$ = new ReturnStmt(nullptr);
    }
    ;
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;
PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, $1);
        $$ = new Constant(se);
    }
    | FLOATNUM {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, $1);
        $$ = new Constant(se);
    }
    | LPAREN Exp RPAREN {
        $$ = $2;
    }
    ;
StarExp
    : 
    UnaryExp { $$ = $1;}
    |   
    StarExp STAR UnaryExp
    {
        Type *expType = BinaryExpr::getArithmeticResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::STAR, $1, $3);  
    }
    |   
    StarExp SLASH UnaryExp 
    {
        Type *expType = BinaryExpr::getArithmeticResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SLASH, $1, $3);
    }
    |   
    StarExp PERCENT UnaryExp 
    {
        Type *expType = BinaryExpr::getArithmeticResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::PERCENT, $1, $3);
    }
    ;
AddExp
    :
    StarExp {$$ = $1;}
    |
    AddExp ADD StarExp
    {
        Type *expType = BinaryExpr::getArithmeticResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB StarExp
    {
        Type *expType = BinaryExpr::getArithmeticResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp LESSEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
    }
    |
    RelExp GREATER AddExp
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
    }
    |
    RelExp GREATEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
    }
    |
    RelExp EQ AddExp
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    |
    RelExp NEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
    }
    ;   
LAndExp
    :
    RelExp {$$ = $1;}
    |
    LAndExp AND RelExp
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp
    :
    LAndExp {$$ = $1;}
    |
    LOrExp OR LAndExp
    {
        Type *expType = BinaryExpr::getRelationalResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
Type
    :
    INT {
        declType = TypeSystem::intType;
        $$ = TypeSystem::intType;
    }
    |
    FLOAT {
        declType = TypeSystem::floatType;
        $$ = TypeSystem::floatType;
    }
    |
    VOID {
        $$ = TypeSystem::voidType;
    }
    ;
DeclStmt
    :
    VarDeclStmt {
        $$ = $1;
    }
    |
    ConstDeclStmt {
        $$ = $1;
    }
    ;
VarDeclStmt
    :
    Type VarDefList SEMICOLON {
        $$ = $2;
    }
    ;
ConstDeclStmt
    :
    CONST Type {
        if (declType->isInt()) {
            declType = TypeSystem::constIntType;
        } else if (declType->isFloat()) {
            declType = TypeSystem::constFloatType;
        } else {
            fprintf(stderr, "Error: Invalid type \'const void\' \n"); 
        }
    }
    ConstDefList SEMICOLON {
        $$ = $4;
    }
    ;
FuncDef
    :
    Type ID {
        identifiers = new SymbolTable(identifiers);

        intParamNo = 0;
        floatParamNo = 0;
        stackParamNo = 0;
    }
    LPAREN FuncFParams RPAREN {
        std::vector<Type*> paramsType;
        std::vector<SymbolEntry *> paramsSe;
        if ($5) {
            for (DefNode *defNode : dynamic_cast<DeclStmt *>($5)->getDefNodeList()) {
                paramsType.push_back(defNode->getId()->getType());
                paramsSe.push_back(defNode->getId()->getSymPtr());
            }
        }
        
        Type *funcType = new FunctionType($1, paramsType, paramsSe);
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(funcType, $2, identifiers->getPrev()->getLevel());
        dynamic_cast<IdentifierSymbolEntry *>(se)->setIntParamCount(intParamNo);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setFloatParamCount(floatParamNo);
        if (!identifiers->getPrev()->install($2, se)) {
            fprintf(stderr, "Error: conflicting declaration of identifier %s\n", $2);
        }
        $<se>$ = se; 
    }
    BlockStmt
    {
        $$ = new FunctionDef($<se>7, dynamic_cast<DeclStmt *>($5), $8);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
ArrayIndex
    : ArrayIndex LBRACKET Exp RBRACKET {
        ArrayIndexNode *node = dynamic_cast<ArrayIndexNode *>($1);
        node->append($3);
        $$ = node;
    }
    | LBRACKET Exp RBRACKET {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append($2);
        $$ = node;
    }
    ;
UnaryExp
    :
    PrimaryExp {
        $$ = $1;
    }
    |
    ID LPAREN FuncRParams RPAREN {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }

        $$ = new FuncCallNode(se, dynamic_cast<FuncCallParamsNode *>($3));
    }
    |
    ADD UnaryExp {
        $$ = $2;
    }
    |   
    SUB UnaryExp {
        Type *type = $2->getType();
        if (type->isInt() && dynamic_cast<IntType *>(type)->getSize() == 1) {
            if (type->isConst()) {  
                type = TypeSystem::constIntType;
            } else {
                type = TypeSystem::intType;
            }
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        $$ = new UnaryExpr(tmp, UnaryExpr::SUB, $2);
    }
    |   
    NOT UnaryExp {
        Type *type = $2->getType();
        if (type->isInt()) {
            if (type->isConst()) {
                type = TypeSystem::constBoolType;
            } else {
                type = TypeSystem::boolType;
            }
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        $$ = new UnaryExpr(tmp, UnaryExpr::NOT, $2);
    }
    ;
InitVal
    :
    Exp {
        $$ = $1;

        if (!initValNodeStack.empty()) {
            double val = $1->getValue();
            if (declType->isInt() && $1->getType()->isFloat()) {
                val = (int)val;
            }
            initArrayValue[idx++] = val;

            if (!initValNodeStack.top()->getType()->isArray()) {
                initValNodeStack.top()->append($1);
            } else {
                ArrayType *arrType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType());
                while (arrType) {
                    if (arrType->getElementType()->isArray()) {
                        arrType = dynamic_cast<ArrayType *>(arrType->getElementType());
                        SymbolEntry *se = new ConstantSymbolEntry(arrType, initArrayValue + idx - 1);
                        InitValNode *node = new InitValNode(se);
                        initValNodeStack.top()->append(node);
                        initValNodeStack.push(node);
                    } else {
                        initValNodeStack.top()->append($1);
                        while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                            initValNodeStack.pop();
                        }
                        break;
                    }
                }
            }
        }
    }
    |
    LBRACE RBRACE {
        SymbolEntry* se;
        InitValNode *node;
        if (initValNodeStack.empty()) {
            se = new ConstantSymbolEntry(initArrayType, initArrayValue + idx);
            node = new InitValNode(se);
            idx += initArrayType->getSize() / declType->getSize();
        } else {
            Type *type = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            int elemNum = type->getSize() / declType->getSize();
            se = new ConstantSymbolEntry(type, initArrayValue + idx);
            node = new InitValNode(se);
            initValNodeStack.top()->append(node);
            idx += elemNum;
            
            while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                initValNodeStack.pop();
            }
        }
        $$ = node;

        if (lbraceCount == 0) {
            dynamic_cast<InitValNode *>($$)->fill();
        }
    }
    |
    LBRACE {
        lbraceCount++;

        if (!initValNodeStack.empty()) {
            Type *subType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            initArrayType = dynamic_cast<ArrayType *>(subType);
        }
        SymbolEntry *se = new ConstantSymbolEntry(initArrayType, initArrayValue + idx);
        InitValNode* node = new InitValNode(se);
        if (!initValNodeStack.empty()) {
            initValNodeStack.top()->append(node);
        }
        initValNodeStack.push(node);
        $<exprtype>$ = node;

        if (initArrayType->getElementType()->isArray()) {
            initArrayType = dynamic_cast<ArrayType *>(initArrayType->getElementType());
        }
    } 
    InitValList RBRACE {
        lbraceCount--;
        while (initValNodeStack.top() != $<exprtype>2 && (int)initValNodeStack.size() > lbraceCount + 1) {
            initValNodeStack.pop();
        }
        if (initValNodeStack.top() == $<exprtype>2) {
            initValNodeStack.pop();
        }
        $$ = $<exprtype>2;
        if (!initValNodeStack.empty()) {
            while (initValNodeStack.top()->isFull() && (int)initValNodeStack.size() != lbraceCount) {
                initValNodeStack.pop();
            }
        }
        int elemNum = dynamic_cast<ArrayType *>($$->getType())->getSize() / declType->getSize();
        while (idx % elemNum) {
            idx++;
        }
        if (!initValNodeStack.empty()) {
            Type *subType = dynamic_cast<ArrayType *>(initValNodeStack.top()->getType())->getElementType();
            initArrayType = dynamic_cast<ArrayType *>(subType);
        }

        if (lbraceCount == 0) {
            dynamic_cast<InitValNode *>($$)->fill();
        }
    }
    ;
InitValList 
    :
    InitVal {
        $$ = $1;
    }
    |
    InitValList COMMA InitVal {
        $$ = $1;
    }
    ;
FuncArrayIndex
    :
    FuncArrayIndex LBRACKET Exp RBRACKET {
        ArrayIndexNode *node = dynamic_cast<ArrayIndexNode *>($1);
        node->append($3);
        $$ = node;
    }
    |
    LBRACKET RBRACKET {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append(nullptr);
        $$ = node;
    }
    ;
FuncFParam
    :
    Type ID {
        SymbolEntry *se;
        if ($1->isFloat()) {
            se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel(), floatParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (floatParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        } else {
            se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel(), intParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (intParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install($2, se);
        $$ = new DefNode(new Id(se), nullptr);
        delete []$2;
    }
    |
    CONST Type ID {
        Type *seType = $2->deepCopy();
        seType->setConst();

        SymbolEntry *se;
        if ($2->isFloat()) {
            se = new IdentifierSymbolEntry(seType, $3, identifiers->getLevel(), floatParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (floatParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        } else {
            se = new IdentifierSymbolEntry(seType, $3, identifiers->getLevel(), intParamNo++);
            dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
            if (intParamNo > 4) {
                dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
            }
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install($3, se);
        $$ = new DefNode(new Id(se), nullptr);
        delete []$3;
    }
    |
    Type ID FuncArrayIndex {
        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>($3)->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter) ? (*iter)->getValue() : -1);
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(currentType, $2, identifiers->getLevel(), intParamNo++);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
        if (intParamNo > 4) {
            dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install($2, se);
        $$ = new DefNode(new Id(se), nullptr);
        delete []$2;
    }
    |
    CONST Type ID FuncArrayIndex {
        Type *currentType = declType;
        ArrayType *parentType;
        std::vector<ExprNode *> exprList = dynamic_cast<ArrayIndexNode *>($4)->getExprList();
        for (auto iter = exprList.rbegin(); iter != exprList.rend(); iter++) {
            parentType = new ArrayType(currentType, (*iter) ? (*iter)->getValue() : -1);
            if (currentType->isArray()) {
                dynamic_cast<ArrayType *>(currentType)->setParentType(parentType);
            }
            currentType = parentType;
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(currentType, $3, identifiers->getLevel(), intParamNo++);
        dynamic_cast<IdentifierSymbolEntry *>(se)->setCommonParamNo(intParamNo + floatParamNo - 1);
        if (intParamNo > 4) {
            dynamic_cast<IdentifierSymbolEntry *>(se)->setStackParamNo(stackParamNo++);
        }
        dynamic_cast<IdentifierSymbolEntry *>(se)->setLabel();
        dynamic_cast<IdentifierSymbolEntry *>(se)->setAddr(new Operand(se));

        identifiers->install($3, se);
        $$ = new DefNode(new Id(se), nullptr);
        delete []$3;
    }
    ;
FuncFParams
    :
    FuncFParams COMMA FuncFParam {
        DeclStmt *node = dynamic_cast<DeclStmt *>($1);
        node->append(dynamic_cast<DefNode *>($3));
        $$ = node;
    }
    |
    FuncFParam {
        DeclStmt *node = new DeclStmt();
        node->append(dynamic_cast<DefNode *>($1));
        $$ = node;
    }
    |
    %empty {
        $$ = nullptr;
    }
    ;
FuncRParams
    :
    FuncRParams COMMA Exp {
        FuncCallParamsNode* node = (FuncCallParamsNode*) $1;
        node->append($3);
        $$ = node;
    }
    |
    Exp {
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->append($1);
        $$ = node;
    }
    |
    %empty {
        $$ = nullptr;
    }
    ;
WhileStmt
    :
    WHILE LPAREN Cond RPAREN {
        WhileStmt *node = new WhileStmt($3, nullptr);
        whileStack.push(node);
        $<stmttype>$ = node;
    }
    Stmt {
        WhileStmt *node = dynamic_cast<WhileStmt *>($<stmttype>5);
        node->setStmt($6);
        whileStack.pop();
        $$ = node;
    }
    ;
BreakStmt
    :
    BREAK SEMICOLON {
        if (!whileStack.empty()) {
            $$ = new BreakStmt(whileStack.top());
        } else {
            fprintf(stderr, "Error : break statement not within a while loop\n");
        }
    }
    ;
ContinueStmt
    :
    CONTINUE SEMICOLON {
        if (!whileStack.empty()) {
            $$ = new ContinueStmt(whileStack.top());
        } else {
            fprintf(stderr, "Error : continue statement not within a while loop\n");
        }
    }
    ;
ExprStmt
    : 
    Exp SEMICOLON {
        $$ = new ExprStmt($1);
    }
    ;
EmptyStmt
    : SEMICOLON {
        $$ = new EmptyStmt();
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
