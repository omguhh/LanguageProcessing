#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

int symb;

extern printSymb();
extern char* showSymb(int);
extern int yylex(void);
extern FILE* yyin;

rule(char * name,int depth)
{  int i;
   for(i=0;i<depth;i++)
    printf(" ");
  
   printf("%s\n",name);
}

error(char * rule,char * message)
{  printf("%s: found %s\n",rule,showSymb(symb));
   printf("%s: %s\n",rule,message);
   exit(0);
}

//TRACER FOR ALL THE TOKENS FROM THE SOURCEPROGRAM
//YYLEX RETURNS THE NEXT TOKEN...SO YOURE BASICALLY SAYING
//PRINT AND MOVE
lex()
{  printSymb();
   symb = yylex();
}

//depth represents the depth of the block of code i'm guessing? haha this is so ugly :')
//<program> ::= procedure <name> is [<defs>] begin <commands> end <name>;
program(int depth)
{
 rule("program",depth);
 if(symb!=NAME){ error("PROCEDURE","NAME EXPECTED\n"); } //procedure must be followed by name
 lex();

 if(symb==IS) 
{
  multidefinitions(depth+1);
  lex();
}  
 if(symb==BEGIN) 
{
  commands(depth+1);
  lex();
}

if(symb==END) 
{
 lex();
}
 
}
//<defs> ::= <def>; [<defs>]
//correct
multidefinitions(int depth) 
{
 rule("defs",depth);
 definition(depth);
 if(symb==SEMI) { lex(); multidefinitions(depth+1); } 
}
//wtf is supposed to happen here lmao???????????
// <def> ::= <name> : Integer
definition(int depth) 
{
 rule("def",depth);
 if(symb!=NAME){ error("DEF","NAME EXPECTED\n"); } //procedure must be followed by name
 lex();
 if(symb==COLO) {
    if(symb!=NUMBER)
      { error("DEF","CAN ONLY DEFINE INTEGERS\n"); }
  }
}
//<commands> ::= <command>; [<commands>]
mutli_commands(int depth) 
{
 rule("commands",depth);
 command(depth);
 if (symb==SEMI) { lex(); multi_commands(depth+1); }
}
//<command> ::= <assign> | <if> | <for>
command(int depth)
{  rule("command",depth);
   switch(symb)
   {  case NAME:assign(depth+1);
                break;
      case IF: lex();
               ifComm(depth+1);
               break;
      case FOR: lex();
                  forComm(depth+1);
                  break;
      default: error("command","NAME/IF/FOR/PRINT/WHILE/identifier expected\n");
   }
}
//<assign> ::= <name> := <expr>
//correct
assign(int depth)
{  rule("assign",depth);
   if(symb!=NAME){ error("ASSIGN","NAME EXPECTED\n"); } //assign must start with name
   if(symb!=ASSIGN)
   error("assign",":= expected\n");
   lex();
   expr(depth+1);
}
//<if> ::= if <condexpr> then <commands> [else <commands>] end if
//i know this works
ifComm(int depth)
{  rule("if",depth);
   condexpr(depth+1);
   if(symb!=THEN) 
   error("if","THEN expected\n");
   lex();
  command(depth+1);
   if(symb==ELSE)
   {  lex();
   command(depth+1);  
   }

   if(symb==ENDIF){
  lex();
  command(depth+1);
  }

}

//need to add for command
//<for> ::= for <name> in <number> .. <number> loop <commands> end loop
// forComm(int depth)
// {  rule("for",depth);
//    if(symb!=NAME) {error("FOR","NAME EXPECTED\n");}
//    if(symb!=IN) 
//    error("FOR","IN expected\n");
//    lex();
//    //WTF DO YOU PUT FOR <NUMBER> .. <NUMBER> ?!!!?!

// }

//<condexpr> ::= <expr> <bop> <expr>
//could be right??
condexpr(int depth)
{  rule("condexpr",depth);
   expr(depth+1);
   bop(depth+1);
   expr(depth+1);
   lex();
}
//<bop> ::= < | = | <= | /=
//correct 
bop(int depth)
{
 rule("bop",depth);
 switch(symb) 
  {
    case LT:
    case EQ:
    case LTE:
    case NEQ:lex();
             return;
    default: error("bop","comparison operator expected\n");
  }
}
//<expr> ::= <term> [ {+ | -} <expr>]
expr(int depth)
{  rule("exp",depth);
   term(depth+1);
   if(symb==PLUS || symb==MINUS)
   {  lex();
      expr(depth+1);
   }
}
//<term> ::= <base> [* <term>]

term(int depth)
{  rule("term",depth);
   base(depth+1);
   if(symb==STAR)
   {  lex();
      term(depth+1);
   }
}
//<base> := <int> | <name>
base(int depth)
{  rule("base",depth);
   switch(symb)
   {  case NAME: break;
      case INTEGER: break;
      default: error("base","(, identifier or integer expected\n");
   }
   lex();
}

main(int c,char ** argv)
{  
   if((yyin=fopen(argv[1],"r"))==NULL){  
      printf("can't open %s\n",argv[1]);
      exit(0);
   }
   symb = yylex();
   program(1);
   fclose(yyin);
}
