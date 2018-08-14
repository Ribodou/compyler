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

#ifndef __types__
#define __types__

typedef enum {false, true} boolean;

typedef struct var *var_t;
typedef struct list_v *list_var_t;
typedef struct aexpr *aexpr_t;
typedef struct bexpr *bexpr_t;
typedef struct cmd *cmd_t;
typedef struct variable *variable_t;

list_var_t table;

struct var
{
    boolean premiereRencontre;
    char *name;                         /* variable name */
    int loc;                            /* variable location */
};


struct list_v
{
  var_t var;
  struct list_v *next;
};


struct aexpr
{
    int tag;                            /* select the value in the union */
    union
    {
        int num;                        /* number */
        var_t var;                      /* variable */
        struct aexpr *expr;             /* operand of a unary op */
        struct
        {
            struct aexpr *lexpr, *rexpr;    /* operands of a binary op */
        } binop;
    } data;
};


struct bexpr
{
    int tag;                            /* select the value in the union */
    union
    {
        boolean bval;                   /* boolean constant */
        struct bexpr *expr;             /* operand of a unary op */
        struct
        {
            struct bexpr *lexpr, *rexpr;    /* operands of a binary op */
        } binop;
        struct
        {
            struct aexpr *lexpr, *rexpr;    /* operands of a binary comparison */
        } comp;
    } data;
};


struct cmd_ass
{
    var_t var;                         /* lhs variable */
    aexpr_t expr;                       /* rhs expression */
};


struct cmd_seq
{
    cmd_t cmd1, cmd2;                   /* left and right commands */
};


/* if - then - else structure */
struct cmd_ite
{
    bexpr_t test;                       /* if test */
    cmd_t cmd_then, cmd_else;           /* then and else commands */
};


struct cmd_while
{
    bexpr_t test;
    cmd_t cmd_body;
};


struct fonction
{
    char *name;
    char *return_type;
    variable_t *arguments;
};


struct cmd_return
{
    int tag;
    union
    {
        aexpr_t aexpr;  // tag = 0
        bexpr_t bexpr;  // tag = 1
    } data;
};


struct cmd
{
    int tag;                            /* select the value in the union */
    union
    {
        struct cmd_ass cmd_ass;         /* assignment command */
        struct cmd_seq cmd_seq;         /* seq composition command */
        struct cmd_ite cmd_ite;         /* if-then-else command */
        struct cmd_while cmd_while;     /* while command */
        struct fonction fonction;       /* function command */
        struct cmd_return cmd_return;   /* return command */
    } data;
};

#endif
