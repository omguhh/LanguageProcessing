%{
#include "tokens.h"
%}

NUMBER     [0-9]
NAME 	   [a-zA-z][a-zA-z0-9]*
      
%%

"procedure" 	{ return PROCEDURE;}
"is" 		{ return IS;}
"begin"		{return TBEGIN;}
"end"		{ return END;}
";" 		{ return SEMI;}
":=" 		{ return ASSIGN;}
"if"		{ return IF;}
"then"		{ return THEN;}
"else"		{ return ELSE;}
"end if" 	{return ENDIF;}
"for" 		{ return FOR;}
"in" 		{ return IN;}
".."		{return TO;}
"loop" 		{ return LOOP;}
"end loop" 	{ return ENDLOOP;}
"<" 		{ return LT;}
"=" 		{ return EQ;}
"<=" 		{ return LTE;}
"/=" 		{ return NEQ;}
"+"  		{ return PLUS;}
"-"		{ return MINUS;}  
":"		{ return COLO;}
"*" 		{ return STAR;}
"Integer"	{return INTEGER;}
{NUMBER}+ 	{ return NUMBER; }
{NAME} 		{ return NAME; }
<<EOF>>	 	{return EOF;}


[ \t\n]+     /* eat up whitespace */

%%

int yywrap() { return EOF; }
