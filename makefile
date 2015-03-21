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

clean:
	rm -rf *.o lex.yy.c lexical parser
