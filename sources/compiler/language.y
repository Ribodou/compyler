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
    #include "make_tree.h"
    #include "see_tree.h"
    #include "memory.h"
    #include "language.h"
    #include "types.h"

    int yylex(void);
    void yyerror(int *anciant_level_ptr, int *actual_level_ptr, FILE *fichier, char **fonction_courante_ptr, tab *memoire, char const*);
%}

%parse-param {int *ancient_level_ptr} {int *actual_level_ptr} {FILE *fichier} {char **fonction_courante_ptr} {tab *memoire}

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
%token THATSALLFOLKS RETURN DEF
%token<id> VAR
%left ';'
%left ASSIGN
%left DO
%left ELSE
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
%left SEQ
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
        *ancient_level_ptr = *actual_level_ptr;
        *actual_level_ptr = 0;
        int retour = token_main(fonction_courante_ptr, ancient_level_ptr, actual_level_ptr, fichier, $1);
        return retour;
    }
    |
    LEVEL cmd
    {
        *ancient_level_ptr = *actual_level_ptr;
        *actual_level_ptr = $1;
        int retour = token_main(fonction_courante_ptr, ancient_level_ptr, actual_level_ptr, fichier, $2);
        return retour;
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
        $$ = mk_aexpr_var(memoire, *fonction_courante_ptr, $1);
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
        $$ = mk_cmd_ass(memoire, *fonction_courante_ptr, $1, $5);
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
        snprintf(*fonction_courante_ptr, 256 * sizeof(char), "%s", "main");
        $$ = mk_cmd_fct("main", "int");
    }
    |
    RETURN SPACE aexpr
    {
        $$ = mk_cmd_return_from_aexpr($3);
    }
    |
    DEF SPACE VAR
;
%%

void yyerror(int *anciant_level, int *actual_level, FILE *fichier, char **fonction_courante, tab *memoire, char const *msg) {
    fprintf (stderr, "%s\n", msg);
}
