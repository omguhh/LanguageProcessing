#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int symb;
extern char * yytext;

char * showSymb(int symb)
{  switch(symb)   {  	
  case PROCEDURE: return "procedure";
  case IS: return "is";
  case BEGIN: return "begin";
  case END: return "end";
  case SEMI: return ";";
  case ASSIGN: return ":=";

  case NUMBER: return "NUMBER";
  case NAME: return "NAME";

  case IF: return "if";
  case THEN: return "then";
  case ELSE: return "else";
  case ENDIF: return "end if";
  case FOR: return "for";
  case IN: return "in";
  case TO: return "to";
  case LOOP: return "loop";
  case ENDLOOP: return "endloop";

  case LT:return "<";
  case EQ: return "=";
  case LTE: return "<=";
  case NEQ: return "\=";

  case PLUS: return "+";
  case MINUS: return "-";
  case STAR: return "*";
  case COLO: return ":";

  case EOF: return "EOF";

  default: printf("bad symbol: %d",symb);
   }
}

printSymb()
{  char * s;
   printf("%s ",showSymb(symb));
   if(symb==NAME || symb==NUMBER){
    if(yytext == NULL)
      printf("Error: yytext is null");
    else
      printf("%s\n",yytext);
   } else
    printf("\n");
}
