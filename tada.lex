%{
#include "tokens.h"
%}

NUMBER     [0-9]
NAME 	   [a-zA-Z]         
%%

";" 		{ return SEMI;}
":" 		{ return COLO;}
{NUMBER}+ 	{ return NUMBER; }
{NAME}+ 	{ return NAME; }
"procedure" 	{ return PROCEDURE;}
":=" 		{ return ASSIGN;}
"if"		{ return IF;}
"end if" 	{return ENDIF;}
"then"		{ return THEN;}
"else"		{ return ELSE;}
"end"		{ return END;}

"do" 		{ return DO;}
"is" 		{ return IS;}
"for" 		{ return FOR;}
"in" 		{ return IN;}
"loop" 		{ return LOOP;}
"end loop" 	{ return ENDLOOP;}

"+"  		{ return PLUS;}
"-"		{ return MINUS;}  
"*" 		{ return STAR;}
"<" 		{ return LT;}
"<=" 		{ return LTE;}
"==" 		{ return EQ;}
"!=" 		{ return NEQ;}
">" 		{ return GT;}
">=" 		{ return GTE;}

<<EOF>>	 {return EOF;}


[ \t\n]+     /* eat up whitespace */

%%

int yywrap() { return EOF; }
