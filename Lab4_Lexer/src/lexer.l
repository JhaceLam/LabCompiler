%option noyywrap
%option yylineno
%{
    /*
    * You will need to comment this line in lab5.
    */
    #define ONLY_FOR_LEX
    
    #ifdef ONLY_FOR_LEX
    #include "symbolTable.h"
    #else
    #define YYSTYPE void *
    #include "parser.h"
    #endif

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include <string>

    #ifdef ONLY_FOR_LEX
    #include <ostream>
    #include <fstream>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;

    int offset = 1;
    SymbolTable table;

    void DEBUG_FOR_LAB4(string token, string lexeme, string property=""){
        fprintf(yyout, "[DEBUG LAB4]: \t%10s%10s%10d%10d%10s\n", 
        token.c_str(), lexeme.c_str(), yylineno, offset, property.c_str());
    }

    #endif
%}

INTCONST ([1-9][0-9]*|0)
OCTAL (0[1-7][0-7]*)
HEX (0(x|X)[1-9a-fA-F][0-9a-fA-F]*)
FRACTION (\.[0-9]*)
EXPONENT ((e|E)[+-]?[0-9]+)
FLOAT (([1-9][0-9]*|0)?(\.[0-9]*)((e|E)[+-]?[0-9]+)?)|(([1-9][0-9]*|0)(e|E)[+-]?[0-9]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*

STRING_LITERAL (\"[^\n]*\")

EOL (\r\n|\n|\r)
WHITE [\t ]

LINECOMMENT (\/\/[^\n]*)
commentbegin (\/\*)
commentelement (.|\n)
commentend (\*\/)
%x BLOCKCOMMENT

%%

"float" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FLOAT", "float");
        offset += yyleng;
    #else
        return FLOAT;
    #endif 
}
"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INT", "int");
        offset += yyleng;
    #else
        return INT;
    #endif
}
"void" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("VOID", "void");
        offset += yyleng;
    #else
        return VOID;
    #endif 
}
"if" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("IF", "if");
        offset += yyleng;
    #else
        return IF;
    #endif
};
"else" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ELSE", "else");
        offset += yyleng;
    #else
        return ELSE;
    #endif
};
"return" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RETURN", "return");
        offset += yyleng;
    #else
        return RETURN;
    #endif
}
"while" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("WHILE", "while");
        offset += yyleng;
    #else
        return WHILE;
    #endif
}
"for" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FOR", "for");
        offset += yyleng;
    #else
        return FOR;
    #endif
}
"break" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("BREAK", "break");
        offset += yyleng;
    #else
        return BREAK;
    #endif
}
"continue" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("CONTINUE", "continue");
        offset += yyleng;
    #else
        return CONTINUE;
    #endif
}

"=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGN", "=");
        offset += yyleng;
    #else
        return ASSIGN;
    #endif
}
"+" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("PLUS", "+");
        offset += yyleng;
    #else
        return PLUS;
    #endif
}
"-" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("MINUS", "-");
        offset += yyleng;
    #else
        return MINUS;
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
        DEBUG_FOR_LAB4("PERCENT", "%");
        offset += yyleng;
    #else
        return PERCENT;
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

"," {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("COMMA", ",");
        offset += yyleng;
    #else
        return COMMA;
    #endif
}
";" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SEMICOLON", ";");
        offset += yyleng;
    #else
        return SEMICOLON;
    #endif
}
"(" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LPAREN", "(");
        offset += yyleng;
    #else
        return LPAREN;
    #endif
}
")" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RPAREN", ")");
        offset += yyleng;
    #else
    return RPAREN;
    #endif
}
"{" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LBRACE", "{");
        offset += yyleng;
    #else
        return LBRACE;
    #endif
}
"}" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RBRACE", "}");
        offset += yyleng;
    #else
        return RBRACE;
    #endif
}
"[" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LSQUARE", "[");
        offset += yyleng;
    #else
        return LSQUARE;
    #endif
}
"]" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RSQUARE", "]");
        offset += yyleng;
    #else
        return RSQUARE;
    #endif
}

{INTCONST} {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INTCONST", yytext);
        offset += yyleng;
    #else
        return INTCONST;
    #endif
}
{OCTAL} {
    #ifdef ONLY_FOR_LEX
        char *endptr;
        int decimalVal = strtol(yytext, &endptr, 8);
        DEBUG_FOR_LAB4("INTCONST", to_string(decimalVal));
        offset += yyleng;
    #else
        return INTCONST;
    #endif
}
{HEX} {
    #ifdef ONLY_FOR_LEX
        char *endptr;
        int decimalVal = strtol(yytext, &endptr, 16);
        DEBUG_FOR_LAB4("INTCONST", to_string(decimalVal));
        offset += yyleng;
    #else
        return INTCONST;
    #endif
}
{FLOAT} {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FLOAT", yytext);
        offset += yyleng;
    #else
        return FLOAT;
    #endif
}
{ID} {
    #ifdef ONLY_FOR_LEX
        string id_string = string(yytext);
        string position = to_string(yylineno) + ":" + to_string(offset);
        table.insert(id_string, position);

        DEBUG_FOR_LAB4("ID", yytext, position);
        offset += yyleng;
    #else
        return ID;
    #endif
}
{STRING_LITERAL} {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("STRING_LITERAL", yytext);
        offset += yyleng;
    #else
        return STRING_LITERAL;
    #endif
}

{EOL} {
    // yylineno++;
    #ifdef ONLY_FOR_LEX
        offset = 0;
    #endif
}
{WHITE} {
    #ifdef ONLY_FOR_LEX
        offset += yyleng;
    #endif
}

{LINECOMMENT}
{commentbegin} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{commentelement} {}
<BLOCKCOMMENT>{commentend} {BEGIN INITIAL;}

%%

#ifdef ONLY_FOR_LEX
int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Argument Not Enough");
        exit(EXIT_FAILURE);
    }

    if(!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr, "No such file or directory: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(!(yyout = fopen(argv[3], "w"))){
        fprintf(stderr, "No such file or directory: %s", argv[3]);
        exit(EXIT_FAILURE);
    }

    yylineno = 1;
    offset = 0;

    fprintf(yyout, "[DEBUG LAB4]: \t%10s%10s%10s%10s%10s\n", 
        "token", "lexeme", "yylineno", "offset", "position");
    
    yylex();
    return 0;
}
#endif
