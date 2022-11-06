%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type *declType; // The Type in DeclStmt 
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATNUM
%token IF ELSE WHILE BREAK CONTINUE
%token INT VOID CONST FLOAT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA LBRACKET RBRACKET
%token ADD SUB MINUS STAR SLASH PERCENT AND OR NOT LESS LESSEQ GREAT GREATEQ EQ NEQ ASSIGN
%token RETURN

%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef
%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp StarExp UnaryExp
%nterm <exprtype> ConstExp
%nterm <type> Type
%nterm <stmttype> VarDefList VarDef ConstArrayIndex InitVal InitValList ArrayIndex
%nterm <stmttype> ConstDefList ConstDef ConstInitVal ConstInitValList
%nterm <stmttype> WhileStmt BreakStmt ContinueStmt

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
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | BreakStmt {$$=$1;}
    | ContinueStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
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
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
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
        | LBRACE RBRACE { $$ = new CompoundStmt(nullptr); }
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
    ;
WhileStmt
    : WHILE LPAREN Cond RPAREN Stmt {
        $$ = new WhileStmt($3, $5);
    }
BreakStmt
    : BREAK SEMICOLON {
        $$ = new BreakStmt();
    }
    ;
ContinueStmt
    : CONTINUE SEMICOLON {
        $$ = new ContinueStmt();
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
    |
    INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, $1);
        $$ = new Constant(se);
    }
    |
    FLOATNUM {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, $1);
        $$ = new Constant(se);
    }
    |
    LPAREN Exp RPAREN {
        $$ = $2;
    }
    ;
UnaryExp
    :
    PrimaryExp {
        $$ = $1;
    }
    |
    ADD UnaryExp {
        $$ = $2;
    }
    |   
    SUB UnaryExp {
        SymbolEntry *tmp = new TemporarySymbolEntry($2->getType(), 
            SymbolTable::getLabel());
        $$ = new OneOpExpr(tmp, OneOpExpr::SUB, $2);
    }
    |   
    NOT UnaryExp {
        SymbolEntry *tmp = new TemporarySymbolEntry($2->getType(), 
            SymbolTable::getLabel());
        $$ = new OneOpExpr(tmp, OneOpExpr::NOT, $2);
    }
    ;
StarExp //乘除取模
    :   
    UnaryExp { $$ = $1;}
    |   
    StarExp STAR UnaryExp
    {
        Type *expType = BinaryExpr::getResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::STAR, $1, $3);  
    }
    |   
    StarExp SLASH UnaryExp 
    {
        Type *expType = BinaryExpr::getResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SLASH, $1, $3);
    }
    |   
    StarExp PERCENT UnaryExp 
    {
        Type *expType = BinaryExpr::getResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::PERCENT, $1, $3);
    }
    ;
AddExp //加减法
    :
    StarExp {$$ = $1;}
    |
    AddExp ADD StarExp
    {
        Type *expType = BinaryExpr::getResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB StarExp
    {
        Type *expType = BinaryExpr::getResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
RelExp //关系运算
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp LESSEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
    }
    |
    RelExp GREAT AddExp
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREAT, $1, $3);
    }
    |
    RelExp GREATEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
    }
    |
    RelExp EQ AddExp
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    |
    RelExp NEQ AddExp 
    {
        Type *expType = BinaryExpr::getRelResultType($1, $3);
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
        Type *expType = BinaryExpr::getRelResultType($1, $3);
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
        Type *expType = BinaryExpr::getRelResultType($1, $3);
        SymbolEntry *se = new TemporarySymbolEntry(expType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
ConstExp
    : AddExp {
        $$ = $1;
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
    Type VarDefList SEMICOLON {
        $$ = $2;
    }
    |
    CONST Type ConstDefList SEMICOLON {
        $$ = $3;
    }
    ;
FuncDef
    :
    Type ID {
        Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN RPAREN
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, $6);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
ConstArrayIndex
    :
    ConstArrayIndex LBRACKET ConstExp RBRACKET {
        ArrayIndexNode *node = (ArrayIndexNode *)$1;
        node->append( (ExprNode *)$3 );
        $$ = node;
    }
    |
    LBRACKET ConstExp RBRACKET {
        ArrayIndexNode *node = new ArrayIndexNode(true);
        node->append( (ExprNode *)$2 );
        $$ = node;
    }
    ; 
ArrayIndex
    : ArrayIndex LBRACKET Exp RBRACKET {
        ArrayIndexNode *node = (ArrayIndexNode *)$1;
        node->append( (ExprNode *)$3 );
        $$ = node;
    }
    | LBRACKET Exp RBRACKET {
        ArrayIndexNode *node = new ArrayIndexNode();
        node->append( (ExprNode *)$2 );
        $$ = node;
    }
    ;
InitVal
    :
    Exp {
        InitValNode *node = new InitValNode( (ExprNode *)$1 );
        $$ = node;
    }
    |
    LBRACE InitValList RBRACE {
        $$ = $2;
    }
    |
    LBRACE RBRACE {
        InitValNode *node = new InitValNode();
        $$ = node;
    }
    ;
InitValList
    :
    InitValList COMMA InitVal {
        InitValNode *node = (InitValNode *)$1;
        node->append( (InitValNode *)$3 );
        $$ = node;
    }
    |
    InitVal {
        InitValNode *node = new InitValNode();
        node->append( (InitValNode *)$1 );
        $$ = node;
    }
    ;
VarDef 
    :
    ID {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DefNode(new Id(se), nullptr);
        delete []$1;
    }
    |
    ID ASSIGN InitVal {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DefNode(new Id(se), (InitValNode *)$3 );
        delete []$1;
    }
    |
    ID ConstArrayIndex {
        Type *type;
        if (declType->isInt()) {
            type = new IntArrayType();
        } else {
            type = new FloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        identifiers->install($1, se);
        Id *id = new Id(se, (ArrayIndexNode *)$2 );
        $$ = new DefNode(id, nullptr);

        int demension = ( (ArrayIndexNode *)$2 )->getDemension();
        if (declType->isInt()) {
            ( (IntArrayType *)type )->setDimension(demension);
        } else {
            ( (FloatArrayType *)type )->setDimension(demension);
        }
    }
    |
    ID ConstArrayIndex ASSIGN InitVal {
        Type *type;
        if (declType->isInt()) {
            type = new IntArrayType();
        } else {
            type = new FloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        identifiers->install($1, se);
        Id *id = new Id(se, (ArrayIndexNode *)$2 );
        $$ = new DefNode(id, (InitValNode *)$4 );

        int demension = ( (ArrayIndexNode *)$2 )->getDemension();
        if (declType->isInt()) {
            ( (IntArrayType *)type )->setDimension(demension);
        } else {
            ( (FloatArrayType *)type )->setDimension(demension);
        }
    }
    ;
VarDefList
    : VarDefList COMMA VarDef {
        DeclStmt *node = (DeclStmt *)$1;
        node->append( (DefNode *)$3 );
        $$ = node;
    }
    |
    VarDef {
        DeclStmt *node = new DeclStmt();
        node->append( (DefNode *)$1 );
        $$ = node;
    }
    ;
ConstInitVal
    : ConstExp {
        InitValNode *node = new InitValNode( (ExprNode *)$1 , true);
        $$ = node;
    }
    |
    LBRACE ConstInitValList RBRACE {
        $$ = $2;
    }
    |
    LBRACE RBRACE {
        InitValNode *node = new InitValNode(nullptr, true);
        $$ = node;
    }
    ;
ConstInitValList 
    : ConstInitValList COMMA ConstInitVal {
        InitValNode *node = (InitValNode *)$1;
        node->append( (InitValNode *)$3 );
        $$ = node;
    }
    |
    ConstInitVal {
        InitValNode *node = new InitValNode(nullptr, true);
        node->append( (InitValNode *)$1 );
        $$ = node;
    }
    ;
ConstDef 
    : ID ASSIGN ConstInitVal {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(declType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DefNode(new Id(se, true), (InitValNode *)$3 , true);
        delete []$1;
    }
    |
    ID ConstArrayIndex ASSIGN ConstInitVal {
        Type *type;
        if (declType->isInt()) {
            type = new ConstIntArrayType();
        } else {
            type = new ConstFloatArrayType();
        }
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        identifiers->install($1, se);
        Id *id = new Id(se, (ArrayIndexNode *)$2 , true);
        $$ = new DefNode(id, (InitValNode *)$4 , true);

        int demension = ( (ArrayIndexNode *)$2 )->getDemension();
        if (declType->isInt()) {
            ( (ConstIntArrayType *)type )->setDimension(demension);
        } else {
            ( (ConstFloatArrayType *)type )->setDimension(demension);
        }
    }
    ;
ConstDefList  
    :   ConstDefList COMMA ConstDef {
        DeclStmt *node = (DeclStmt *)$1;
        node->append( (DefNode *)$3 );
        $$ = node;
    }
    |
    ConstDef {
        DeclStmt *node = new DeclStmt(true);
        node->append( (DefNode *)$1 );
        $$ = node;
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
