static const char* G_TOKEN_TYPE_TO_STRING[] = {
    "UNKNOWN",
    "LPAREN",
    "RPAREN",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIV",
    "EQ",
    "GTEQ",
    "LTEQ",
    "GT",
    "LT",
    "NEQ",
    "IDENT",
    "SYMBOL",
    "INTEGER",
    "STRING"
};

const char* token_type_to_string(int tok_type)
{
    return G_TOKEN_TYPE_TO_STRING[tok_type];
}

