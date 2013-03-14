%{
#include "tokens.h"
%}

digit [0-9]
letter [a-zA-Z]

%%

"("             { return LPAREN; }
")"             { return RPAREN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIV; }
"="             { return EQ; }
">="            { return GTEQ; }
"<="            { return LTEQ; }
">"             { return GT; }
"<"             { return LT; }
"!="            { return NEQ; }

{letter}({digit}|{letter})* { yylval = strdup(yytext); return IDENT; }
":"({letter}|{digit}|"-")*  { yylval = strdup(yytext); return SYMBOL; }
{digit}*                    { yylval = strdup(yytext); return INTEGER; }
L?\"(\\.|[^\\"])*\"         { yylval = strdup(yytext); return STRING; }


[ \t\n\r]

.               { printf("Unknown character [%c]\n",yytext[0]);
                  return UNKNOWN;    }

%%
 
int yywrap(void){return 1;}

