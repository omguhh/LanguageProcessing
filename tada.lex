%{
#include "tokens.h"
%}

NUMBER     [0-9]
NAME 	   [a-zA-Z0-9]*         
%%

"procedure" { return PROCEDURE;}
"is" 		{ return IS;}
"begin"		{return BEGIN;}
"end"		{ return END;}
";" 		{ return SEMI;}
":=" 		{ return ASSIGN;}

{NUMBER}+ 	{ return NUMBER; }
{NAME} 	{ return NAME; }

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
"\=" 		{ return NEQ;}

":" 		{ return COLO;}


"+"  		{ return PLUS;}
"-"			{ return MINUS;}  
"*" 		{ return STAR;}
":" 		{ return COLO;}


<<EOF>>	 	{return EOF;}


[ \t\n]+     /* eat up whitespace */

%%

int yywrap() { return EOF; }
