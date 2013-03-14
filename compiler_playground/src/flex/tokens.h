#ifndef __MINILISP_TOKENS_H__
#define __MINILISP_TOKENS_H__

typedef char* YYSTYPE;
extern YYSTYPE yylval;

enum {
    UNKNOWN,
    LPAREN,
    RPAREN,
    PLUS,
    MINUS,
    TIMES,
    DIV,
    EQ,
    GTEQ,
    LTEQ,
    GT,
    LT,
    NEQ,
    IDENT,
    SYMBOL,
    INTEGER,
    STRING
};

const char* token_type_to_string(int); 

#endif

