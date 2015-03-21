#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int symb;
extern char * yytext;

char * showSymb(int symb)
{  switch(symb)
   {  	case  PROCEDURE: return "procedure";
      	case  COlO: return ":";
	case SEMI: return ";";
	case ASSIGN: return ":=";
	case IF: return "if";
	case ENDIF: return "end if";
	case THEN: return "then";
	case END: return "end";
	case DO:return "do";
	case IS:return "is";
	case FOR:return "for";
	case IN:return "in";
	case LOOP:return "loop";
	case ENDLOOP:return "endloop";

      	case  PLUS: return "+";
      	case  MINUS: return "-";
      	case  STAR: return "*";
      	case  SLASH: return "/";
     	case  LBRA: return "(";
      	case  RBRA: return ")";
      	case  LT: return "<";
      	case  LTE: return "<=";
      	case  EQ: return "=";
      	case  NEQ: return "!=";
      	case  GTE: return ">=";
      	case  GT: return ">";
      	case EOF: return "EOF";
      	default: printf("bad symbol: %d",symb);
   }
}

printSymb()
{  char * s;
   printf("%s ",showSymb(symb));
   if(symb==ID || symb==INT){
    if(yytext == NULL)
      printf("Error: yytext is null");
    else
      printf("%s\n",yytext);
   } else
    printf("\n");
}
