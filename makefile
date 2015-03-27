
all: 	nodes.h tokens.h
	flex tada.lex
	gcc -c lex.yy.c
	gcc -c ast_parser.c
	gcc -c print.c
	gcc -c pretty.c
	gcc -o astparser print.o pretty.o lex.yy.o ast_parser.o

clean:
	rm -rf *.o lex.yy.c lexical parser astparser comp

lexical: 
	flex tada.lex
	gcc -c lex.yy.c
	gcc -c lex.c
	gcc -c print.c
	gcc -o lexical lex.yy.o print.o lex.o

parser: 
	flex tada.lex
	gcc -c lex.yy.c
	gcc -c parse.c
	gcc -c print.c	
	gcc -o parser print.o lex.yy.o parse.o

comp:   nodes.h tokens.h parse.c simp.lex print.c comp.c pretty.c
	flex simp.lex
	gcc -c lex.yy.c
	gcc -c parse.c
	gcc -c print.c
	gcc -c pretty.c
	gcc -c comp.c
	gcc -o comp print.o pretty.o lex.yy.o parse.o comp.o
