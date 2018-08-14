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

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "make_tree.h"
    #include "see_tree.h"
    #include "memory.h"

    int yylex(void);
    void yyerror(char const*);
%}

%union{
    char *id;
    int ival;
    int bval;
    cmd_t cmd;
    aexpr_t aexpr;
    bexpr_t bexpr;
}

%token<ival> NUM LEVEL
%token<id> ID
%token<bval> BCONST

%token PASS SEQ IF THEN ELSE WHILE DO NEWLINE EQUAL TAB SPACE MAIN
%token THATSALLFOLKS RETURN
%token<id> VAR
%left ';'
%left SEQ
%left ASSIGN
%left DO
%left '|'
%left '!'
%left '&'
%left '>'
%left '<'
%left '='
%left '~'
%left '+'
%left '-'
%left '*'
%left '/'
%token P_LEFT P_RIGHT



%type<cmd> cmd
%type<aexpr> aexpr
%type<bexpr> bexpr

/* first symbol */
 %start main

%%

main:
    cmd
    {
        ancient_level = actual_level;
        actual_level = 0;
        if (actual_level != ancient_level)
        {
            char *indentation = NULL;
            int i;
            indentation = malloc((ancient_level + 1) * sizeof(char));
            if (indentation == NULL)
            {
                printf("Plus de mémoire disponible pour l'allocation du tampon \"indentanion\". tag: poiuytre\n");
                exit(-1);
            }
            if (actual_level > ancient_level)
            {
                for (i=0; i<ancient_level; i++)
                {
                    indentation[i] = ' ';
                }
                indentation[i] = '\0';
                fprintf(fichier, "%s%s\n", indentation, "{");
            }
            if (actual_level < ancient_level)
            {
                for (i=0; i<actual_level; i++)
                {
                    indentation[i] = ' ';
                }
                indentation[i] = '\0';
                fprintf(fichier, "%s%s\n", indentation, "}");
            }
            free(indentation);
        }
        fprintf(fichier, "%s\n", see_cmd(0, $1));
        return 0;
    }
    |
    LEVEL cmd
    {
        ancient_level = actual_level;
        actual_level = $1;
        if (actual_level != ancient_level)
        {
            char *indentation = NULL;
            int i;
            indentation = malloc((ancient_level + 1) * sizeof(char));
            if (indentation == NULL)
            {
                printf("Plus de mémoire disponible pour l'allocation du tampon \"indentanion\". tag: poiuytre\n");
                exit(-1);
            }
            if (actual_level > ancient_level)
            {
                for (i=0; i<ancient_level; i++)
                {
                    indentation[i] = ' ';
                }
                indentation[i] = '\0';
                fprintf(fichier, "%s%s\n", indentation, "{");
            }
            if (actual_level < ancient_level)
            {
                for (i=0; i<actual_level; i++)
                {
                    indentation[i] = ' ';
                }
                indentation[i] = '\0';
                fprintf(fichier, "%s%s\n", indentation, "}");
            }
            free(indentation);
        }
        fprintf(fichier, "%s\n", see_cmd($1, $2));
        return 0;
    }
    |
    THATSALLFOLKS
    {
        return -1;
    }
 ;





aexpr:
    P_LEFT aexpr P_RIGHT
    {
        $$ = $2;
    }
    |
    NUM
    {
        $$ = mk_aexpr_num($1);
    }
    |
    VAR
    {
        $$ = mk_aexpr_var($1);
    }
    |
    aexpr '+' aexpr
    {
        $$ = mk_aexpr_binop(1, $1,$3);
    }
    |
    aexpr '-' aexpr
    {
        $$ = mk_aexpr_binop(2, $1,$3);
    }
    |
    aexpr '*' aexpr
    {
        $$ = mk_aexpr_binop(3, $1,$3);
    }
    |
    aexpr '/' aexpr
    {
        $$ = mk_aexpr_binop(4, $1,$3);
    }
    |
    '-' aexpr
    {
        $$ = mk_aexpr_unop(5, $2);
    }
;



bexpr:
    P_LEFT bexpr P_RIGHT
    {
        $$ = $2;
    }
    |
    BCONST
    {
        $$ = mk_bexpr_bconst($1);
    }
    |
    '!' bexpr
    {
         $$ = mk_bexpr_unop(1, $2);
    }
    |
    bexpr '|' bexpr
    {
         $$ = mk_bexpr_binop(2, $1, $3);
    }
    |
    bexpr '&' bexpr
    {
        $$ = mk_bexpr_binop(3, $1, $3);
    }
    |
    aexpr '>' aexpr
    {
         $$ = mk_bexpr_comp(4, $1, $3);
    }
    |
    aexpr '<' aexpr
    {
         $$ = mk_bexpr_comp(5, $1, $3);
    }
    |
    aexpr '=' aexpr
    {
         $$ = mk_bexpr_comp(6, $1, $3);
    }
;


cmd:
    P_LEFT cmd P_RIGHT
    {
        $$ = $2;
    }
    |
    PASS
    {
        $$ = mk_cmd_skip();
    }
    |
    VAR SPACE EQUAL SPACE aexpr
    {
        $$ = mk_cmd_ass($1, $5);
    }
    |
    cmd SEQ cmd
    {
        $$ = mk_cmd_seq($1, $3);
    }
    |
    IF bexpr THEN cmd ELSE cmd
    {
        $$ = mk_cmd_ite($2, $4, $6);
    }
    |
    IF bexpr THEN cmd
    {
        $$ = mk_cmd_ite($2, $4, NULL);
    }
    |
    WHILE bexpr DO cmd
    {
        $$ = mk_cmd_while($2, $4);
    }
    |
    MAIN
    {
        $$ = mk_cmd_fct("main", "int");
    }
    |
    RETURN SPACE aexpr
    {
        $$ = mk_cmd_return_from_aexpr($3);
    }
;
%%

void yyerror(char const *msg) {
    fprintf (stderr, "%s\n", msg);
}
