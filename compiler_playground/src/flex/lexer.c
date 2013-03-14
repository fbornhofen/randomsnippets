#include <stdio.h>

#include "tokens.h"

FILE* yyin;
YYSTYPE yylval;
int yylex(void);

int main(int argc, char** argv)
{
    int cur_tok = 0;
    yyin = stdin;
    do {
        cur_tok = yylex();
        printf("%s (%s)\n", yylval, token_type_to_string(cur_tok));
    } while (cur_tok != UNKNOWN);   
    return 0;
}

