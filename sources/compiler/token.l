%option noyywrap
%{
    /* Copyright (C) 2018 Lucas Robidou
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char *);

    #include "types.h"
    #include "memory.h"
    #include "compiler.h"
    #include "fonctions_bien_pratiques.h"
    #include "types.h"
%}

MAIN ^if[ ]+__name__[ ]*==[ ]*'__main__'[:]$
IDENT ([_A-Za-z])([_A-Za-z0-9]*)

/*if : printf("un main dans le l"); return(MAIN);*/
%%

[\n]        /*printf("newline\n");*/ return(NEWLINE);
[\t]+       /*printf("tab ");*/ return(TAB);
[\!]        return *yytext;
true        yylval.bval = 1; return(BCONST);
false       yylval.bval = 0; return(BCONST);
[\|]        return *yytext;
[-/+*]      return *yytext;
[0-9]+      /*printf("NUM = %s", yytext);*/ yylval.ival = atoi(yytext); return(NUM);
pass        return(PASS);
[=]         /*printf("equal "); */return(EQUAL);
[\;]        return(SEQ);
if          return(IF);
then        return(THEN);
else        return(ELSE);
while       return(WHILE);
do          return(DO);
def         return(DEF);
^[ ]+       yylval.ival = strlen(yytext); /*printf("indentation (%i) ", yylval.ival);*/ return(LEVEL);
[ ]+        /*printf("spaaace! ");*/return(SPACE);
return      /*printf("return "); */return(RETURN);
[(]         return(P_LEFT);
[)]         return(P_RIGHT);
<<EOF>>   return(THATSALLFOLKS);


{MAIN} {return(MAIN);}



{IDENT} {
          //Warning : this malloc will never be freed
          allouer_chaine_256(&(yylval.id));
          int bufSize = 256 * sizeof(char);
          if (snprintf(yylval.id, bufSize, "%s", yytext) >= bufSize)
          {
              printf("Aie Caramba! Encore raté! Y'a plus de place dans mon buffer!\n");
              printf("Viens me voir, zélé programmeur! Je suis dans le fichier .l!\n");
              printf("Voici un tag que tu peux copier-coller pour faciliter ta recherche: ldubsjsk:vjdo.\n");
              exit(-1);
          }
          return(VAR);
        }

. printf("autre chose inconnue : %s\n", yytext); return *yytext;


%%
