#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int symb;
extern char * yytext;

char * showSymb(int symb)
{  switch(symb)   {  	
  case PROCEDURE: return "PROCEDURE";
  case IS: return "IS";
  case TBEGIN: return "BEGIN";
  case END: return "END";
  case SEMI: return ";";
  case ASSIGN: return ":=";

  case NUMBER: return "NUMBER";
  case NAME: return "NAME";

  case IF: return "IF";
  case THEN: return "THEN";
  case ELSE: return "ELSE";
  case ENDIF: return "END IF";
  case FOR: return "FOR";
  case IN: return "IN";
  case TO: return "TO";
  case LOOP: return "LOOP";
  case ENDLOOP: return "END LOOP";

  case LT:return "<";
  case EQ: return "=";
  case LTE: return "<=";
  case NEQ: return "/=";

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
