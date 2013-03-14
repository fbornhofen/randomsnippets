CFLAGS=-m64


all: lexer

lexer: lexfile tokens.h tokens.o
	gcc -o lexer lexer.c lex.yy.c tokens.o $(CFLAGS)

tokens.o: tokens.h tokens.c
	gcc -c tokens.c $(CFLAGS)

lexfile: minilisp.flex tokens.h
	flex minilisp.flex
