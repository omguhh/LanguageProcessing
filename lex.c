#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int symb;

extern int yylex(void);
extern FILE *   yyin;
extern voidprintSymb(void);


main(int argc,char ** argv)
{  
   if((yyin=fopen(argv[1],"r"))==NULL)
   {  printf("can't open %s\n",argv[1]);
      exit(0);
   }

   symb = yylex();
   printSymb();

   while(symb != EOF)
   {  
   	   symb = yylex();
   	   printSymb();
   }

   fclose(yyin);
}
