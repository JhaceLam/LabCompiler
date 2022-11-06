%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    #include "parser.h"
    #include <ostream>
    #include <fstream>
    using namespace std;

    extern FILE *yyin; 
    extern FILE *yyout;
    extern bool dump_tokens;

    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
%}

DECIMIAL ([1-9][0-9]*|0)
FLOATNUM (([1-9][0-9]*|0)?(\.[0-9]*)((e|E)[+-]?[0-9]+)?)|(([1-9][0-9]*|0)(e|E)[+-]?[0-9]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]

LINECOMMENT (\/\/[^\n]*)
commentbegin (\/\*)
commentelement (.|\n)
commentend (\*\/)
%x BLOCKCOMMENT

%%
{LINECOMMENT}
{commentbegin} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{commentelement} {}
<BLOCKCOMMENT>{commentend} {BEGIN INITIAL;}

"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\tint");
    return INT;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\tvoid");
    return VOID;
}
"float" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FLOAT\tfloat");
    return FLOAT;
}
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\tif");
    return IF;
};
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
};
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
    return WHILE;
};
"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\tbreak");
    return BREAK;
};
"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\tcontinue");
    return CONTINUE;
};

"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"+" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ADD", "+");
        offset += yyleng;
    #else
        return ADD;
    #endif
}
"-" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SUB", "-");
        offset += yyleng;
    #else
        return SUB;
    #endif
}
"*" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("STAR", "*");
        offset += yyleng;
    #else
        return STAR;
    #endif
}
"/" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SLASH", "/");
        offset += yyleng;
    #else
        return SLASH;
    #endif
}
"%" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("PERCENT", "%%");
        offset += yyleng;
    #else
        return PERCENT;
    #endif
}

"&&" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("AND", "&&");
        offset += yyleng;
    #else
        return AND;
    #endif
}
"||" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("OR", "||");
        offset += yyleng;
    #else
        return OR;
    #endif
}
"!" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("NOT", "!");
        offset += yyleng;
    #else
        return NOT;
    #endif
}

"==" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("EQ", "==");
        offset += yyleng;
    #else
        return EQ;
    #endif
}
"!=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("NEQ", "!=");
        offset += yyleng;
    #else
        return NEQ;
    #endif
}
"<" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LESS", "<");
        offset += yyleng;
    #else
        return LESS;
    #endif
}
">" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("GREAT", ">");
        offset += yyleng;
    #else
        return GREAT;
    #endif
}
"<=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LESSEQ", "<=");
        offset += yyleng;
    #else
        return LESSEQ;
    #endif
}
">=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("GREATEQ", ">=");
        offset += yyleng;
    #else
        return GREATEQ;
    #endif
}

";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
}
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t(");
    return LPAREN;
}
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t)");
    return RPAREN;
}
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t{");
    return LBRACE;
}
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t}");
    return RBRACE;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}
"[" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACKET\t[");
    return LBRACKET;
}
"]" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACKET\t]");
    return RBRACKET;
}

"getint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: getint()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // int getint()
        Type* funcType = new FunctionType(TypeSystem::intType, {});
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0); //作用域GLOBAL(0)
        globalTable->install(yytext, entry);
    }
    return ID;
}
"getch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: getch()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // int getch()
        Type* funcType = new FunctionType(TypeSystem::intType, {});
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0); //作用域GLOBAL(0)
        globalTable->install(yytext, entry);
    }
    return ID;
}
"getfloat" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: getfloat()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {  
        // float getfloat()
        Type* funcType = new FunctionType(TypeSystem::floatType, {});
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0); //作用域GLOBAL(0)
        globalTable->install(yytext, entry);
    }
    return ID;
}
"getarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: getarray()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // int getarray(int[])
		Type *arrayType = new IntArrayType();
		( (IntArrayType *)arrayType )->setDimension(1);
		std::vector<Type*> paramsType;
		paramsType.push_back(arrayType);		
		FunctionType *funcType = new FunctionType(TypeSystem::intType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"getfarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: getfarray()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // int getfarray(float[])
		Type *arrayType = new FloatArrayType();
		( (FloatArrayType *)arrayType )->setDimension(1);
		std::vector<Type*> paramsType;
		paramsType.push_back(arrayType);		
		FunctionType *funcType = new FunctionType(TypeSystem::intType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putint()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putint(int)
		std::vector<Type*> paramsType;
		paramsType.push_back(TypeSystem::intType);		
		FunctionType *funcType = new FunctionType(TypeSystem::voidType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putch()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putch(int)
		std::vector<Type*> paramsType;
		paramsType.push_back(TypeSystem::intType);		
		FunctionType *funcType = new FunctionType(TypeSystem::voidType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putfloat" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putfloat()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putfloat(float)
		std::vector<Type*> paramsType;
		paramsType.push_back(TypeSystem::floatType);		
		FunctionType *funcType = new FunctionType(TypeSystem::voidType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putarray()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putarray(int,int[])
		Type *arrayType = new IntArrayType();
		( (IntArrayType *)arrayType )->setDimension(1);
		std::vector<Type*> paramsType;
		paramsType.push_back(TypeSystem::intType);
		paramsType.push_back(arrayType);		
		FunctionType *funcType = new FunctionType(TypeSystem::voidType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putfarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putfarray()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putfarray(int,float[])
		Type *arrayType = new FloatArrayType();
		( (IntArrayType *)arrayType )->setDimension(1);
		std::vector<Type*> paramsType;
		paramsType.push_back(TypeSystem::intType);
		paramsType.push_back(arrayType);		
		FunctionType *funcType = new FunctionType(TypeSystem::voidType, paramsType);
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}
"putf" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("I/O Function: putf()");

    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    SymbolTable* globalTable = identifiers;
    for(; globalTable->getPrev(); globalTable = globalTable->getPrev());
    // Find the root of SymbolTable *identifiers
    if(globalTable->lookup(yytext) == nullptr)
    {
        // void putf(<FormatString>, int, ...)
        // TODO	
		FunctionType *funcType = nullptr;
		SymbolEntry *entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}

{DECIMIAL} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    yylval.itype = atoi(yytext);
    return INTEGER;
}

{FLOATNUM} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    yylval.ftype = strtof(yytext, NULL);
    return FLOATNUM;
}

{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}
{EOL} yylineno++;
{WHITE}
%%
