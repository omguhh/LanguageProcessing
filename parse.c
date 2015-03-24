#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int symb;
char * name1;
char * name2; 

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
 lex();
 if(symb==NAME)   { name1=yytext(); lex();  //get value of NAME here & set it to name1
 if(symb==IS)     { lex();   multidefinitions(depth+1); }
 if(symb!=TBEGIN) { error("PROCEDURE","BEGIN EXPECTED\n");  }   {  lex();   mutlicommands(depth+1); 
 if(symb==END)    { error("PROCEDURE","END EXPECTED\n");  }{  lex();  
 if(symb!=NAME)   { error("PROCEDURE","END NAME EXPECTED\n"); }{ name2=yytext();
 if(name1!=name2) { error("PROCEDURE","END NAME AND INITAL NAME MUST BE THE SAME\n"); }
//CHECK TO SEE IF NAME1==NAME2 
 lex();
        }
        }
    } 
  }
}

//<defs> ::= <def>; [<defs>]
multidefinitions(int depth) 
{
 rule("defs",depth);
 definition(depth);
 if(symb==SEMI) {  lex();
 if(symb==NAME){ multidefinitions(depth+1);  } 
  }
   else
    error("defs","; EXPECTED");
}

// <def> ::= <name> : Integer
definition(int depth) 
{
 rule("def",depth);
 if(symb!=NAME){ error("DEF","NAME EXPECTED\n"); } //procedure must be followed by name
 lex();
if(symb==COLO) {
 lex();
 if(symb!=INTEGER) { error("DEF","CAN ONLY DEFINE TYPE INTEGERS\n"); }
 lex();
  }
}

//<commands> ::= <command>; [<commands>]
mutlicommands(int depth) 
{
 rule("mutli_commands",depth);
 command(depth+1);
  if(symb==SEMI) { lex(); 
  if(symb==NAME||symb==IF) {
  mutlicommands(depth+1);
      } 
    }
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
      default: error("command","NAME/IF/FOR expected\n");
   }
}
//<assign> ::= <name> := <expr>
assign(int depth)
{  rule("assign",depth);
   if(symb!=NAME){ error("ASSIGN","NAME EXPECTED\n"); } lex(); //assign must start with name
   if(symb!=ASSIGN){    error("assign",":= expected\n"); }
   lex();
   expr(depth+1);
}
//<if> ::= if <condexpr> then <commands> [else <commands>] end if
ifComm(int depth)
{  rule("if",depth);
   condexpr(depth+1);
   //lex();
   if(symb!=THEN) {   error("if","THEN expected\n"); }
   lex();
   command(depth+1);
   lex();
   if(symb==ELSE) 
   {  lex();
      command(depth+1);  
   }
   lex();
  if(symb!=ENDIF) {   error("if","END IF expected\n"); }
{  lex();  }
}

//<for> ::= for <name> in <number> .. <number> loop <commands> end loop
forComm(int depth)
{
  rule("for",depth);
  if(symb!=NAME){error("FOR","NAME EXPECTED\n");}
  lex();
  if(symb!=IN){error("FOR","IN EXPECTED\n");}
  lex();
  if(symb!=NUMBER){error("FOR","NUMBER EXPECTED\n");}
  lex();
  if(symb!=TO){error("FOR","TO EXPECTED\n");}
  lex();
  if(symb!=NUMBER){error("FOR","SECOND NUMBER ARGUMENT EXPECTED\n");}
  lex();
  if(symb!=ENDLOOP){error("FOR","ENDLOOP EXPECTED\n");}
  lex();
}

//<condexpr> ::= <expr> <bop> <expr>
condexpr(int depth)
{  rule("condexpr",depth);
  if(symb!=THEN) {
   expr(depth+1);
   bop(depth+1);
   expr(depth+1);
  }
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
       expr(depth+1);
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
   if(symb!=THEN) {
   switch(symb)
   {  case NAME: break;
      case NUMBER: break;
      default: error("base"," identifier or integer expected\n");
   }
   lex();
  }
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
