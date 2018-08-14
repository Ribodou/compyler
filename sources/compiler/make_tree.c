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
#include "types.h"
#include "make_tree.h"
#include "table.h"
#include "fonctions_bien_pratiques.h"



aexpr_t mk_aexpr_num(int n)
{
    aexpr_t arbre = (aexpr_t) malloc(sizeof(struct aexpr));
    arbre->data.num = n;
    arbre->tag = 0;
    return arbre;
}


aexpr_t mk_aexpr_var(char *name)
{
    if(name == NULL)
    {
        fprintf(stderr, "Error in mk_aexpr_var : name == NULL.\n");
        exit(-1);
    }
    if(table_lookup_id(name) == NULL)
    {
        var_t var = table_add_id(name);
        var->premiereRencontre = true;
        /*fprintf(stderr, "Erreur in mk_aexpr_var : variable non définie - Erreur gérée.\n");*/
    }
    aexpr_t arbre = (aexpr_t) malloc(sizeof(struct aexpr));
    arbre->data.var = table_lookup_id(name);
    arbre->tag = 6;
    return arbre;
}


aexpr_t mk_aexpr_unop(int op, aexpr_t expr)
{
    aexpr_t arbre = (aexpr_t) malloc(sizeof(struct aexpr));
    arbre->tag = op;
    arbre->data.expr = expr;
    return arbre;
}


aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr)
{
    aexpr_t arbre = (aexpr_t) malloc(sizeof(struct aexpr));
    arbre->tag = op;
    arbre->data.binop.lexpr = lexpr;
    arbre->data.binop.rexpr = rexpr;
    return arbre;
}


char* see_aexpr(aexpr_t ae)
{
    char *retour;
    char *chaine1, *chaine2;
    allouer_chaine_256(&retour);
    int bufSize = 256 * sizeof(char);
    switch (ae->tag) {
        case 0 :
            snprintf(retour, bufSize, "%d", ae->data.num);
            return retour;
            break;

        case 1 : // add
            chaine1 = see_aexpr(ae->data.binop.lexpr);
            chaine2 = see_aexpr(ae->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " + ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;

        case 2 :
            chaine1 = see_aexpr(ae->data.binop.lexpr);
            chaine2 = see_aexpr(ae->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " - ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;

        case 3 : // mult
            chaine1 = see_aexpr(ae->data.binop.lexpr);
            chaine2 = see_aexpr(ae->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " * ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;

        case 4 : // div
            chaine1 = see_aexpr(ae->data.binop.lexpr);
            chaine2 = see_aexpr(ae->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " / ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;

        case 5 : // moins de négation
            chaine1 = see_aexpr(ae->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s", "- ", chaine2);
            free(chaine1);
            return retour;
            break;

        case 6 : //variable
            snprintf(retour, bufSize, "%s", ae->data.var->name);
            return retour;
            break;

        default :
            printf("Tag affichage aexpr non reconnu.\n");
            exit(-1);
            break;
    }
}


bexpr_t mk_bexpr_bconst(boolean b)
{
    bexpr_t arbre = (bexpr_t) malloc(sizeof(struct bexpr));
    arbre->data.bval = b;
    arbre->tag = 0;
    return arbre;
}



bexpr_t mk_bexpr_unop(int op, bexpr_t expr)
{
    bexpr_t arbre = (bexpr_t) malloc(sizeof(struct bexpr));
    arbre->tag = op;
    arbre->data.expr = expr;
    return arbre;
}


bexpr_t mk_bexpr_binop(int op, bexpr_t lexpr, bexpr_t rexpr)
{
    bexpr_t arbre = (bexpr_t) malloc(sizeof(struct bexpr));
    arbre->tag = op;
    arbre->data.binop.lexpr = lexpr;
    arbre->data.binop.rexpr = rexpr;
    return arbre;
}


bexpr_t mk_bexpr_comp(int op, aexpr_t lexpr, aexpr_t rexpr)
{
    bexpr_t arbre = (bexpr_t) malloc(sizeof(struct bexpr));
    arbre->tag = op;
    arbre->data.comp.lexpr = lexpr;
    arbre->data.comp.rexpr = rexpr;
    return arbre;
}



char* see_bexpr(bexpr_t be)
{
    char *retour = NULL;
    char *chaine1, *chaine2;
    allouer_chaine_256(&retour);
    int bufSize = 256 * sizeof(char);
    switch (be->tag) {
        case 0 : // const
            if(be->data.bval == true)
            {
                snprintf(retour, bufSize, "%s", "true");
            }
            else
            {
                snprintf(retour, bufSize, "%s", "false");
            }
            return retour;
            break;
        case 1 :  // !
            chaine1 = see_bexpr(be->data.expr);
            snprintf(retour, bufSize, "%s%s", "! ", chaine1);
            free(chaine1);
            return retour;
            break;
        case 2 :  // ||
            chaine1 = see_bexpr(be->data.binop.lexpr);
            chaine2 = see_bexpr(be->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " || ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;
        case 3 :  // &&
            chaine1 = see_bexpr(be->data.binop.lexpr);
            chaine2 = see_bexpr(be->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " && ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;
        case 4 :  // >
            chaine1 = see_bexpr(be->data.binop.lexpr);
            chaine2 = see_bexpr(be->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " > ", chaine2);
            free(chaine1);
            free(chaine2);
        return retour;
            break;
        case 5 :  // <
            chaine1 = see_bexpr(be->data.binop.lexpr);
            chaine2 = see_bexpr(be->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " < ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;
        case 6 :  // ==
            chaine1 = see_bexpr(be->data.binop.lexpr);
            chaine2 = see_bexpr(be->data.binop.rexpr);
            snprintf(retour, bufSize, "%s%s%s", chaine1, " == ", chaine2);
            free(chaine1);
            free(chaine2);
            return retour;
            break;
        default :
            printf("Tag affichage booleen non reconnu.");
            break;
    }
}




cmd_t mk_cmd_skip(void)
{
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 0;
    return arbre;
}


cmd_t mk_cmd_ass(char *name, aexpr_t expr)
{
    if(name == NULL)
    {
        fprintf(stderr, "Error in mk_cmd_ass : name == NULL.\n");
        exit(-1);
    }
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 1;
    arbre->data.cmd_ass.expr = expr;

    if(table_lookup_id(name) == NULL)
    {
        var_t var = table_add_id(name);
        var->premiereRencontre = true;
        /*fprintf(stderr, "Erreur in mk_aexpr_ass : variable non définie - Erreur gérée.\n");*/
    }
    arbre->data.cmd_ass.var = table_lookup_id(name);
    return arbre;
}


cmd_t mk_cmd_seq(cmd_t cmd1, cmd_t cmd2)
{
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 2;
    arbre->data.cmd_seq.cmd1 = cmd1;
    arbre->data.cmd_seq.cmd2 = cmd2;
    return arbre;
}


cmd_t mk_cmd_ite(bexpr_t expr, cmd_t cmd_then, cmd_t cmd_else)
{
    if(expr == NULL)
    {
        fprintf(stderr, "Error in mk_cmd_ite : expr == NULL.\n");
        exit(-1);
    }
    if(cmd_then == NULL)
    {
        fprintf(stderr, "Error in mk_cmd_ite : cmd_then == NULL.\n");
        exit(-1);
    }
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 3;
    arbre->data.cmd_ite.test = expr;
    arbre->data.cmd_ite.cmd_then = cmd_then;
    arbre->data.cmd_ite.cmd_else = cmd_else;
    return arbre;
}


cmd_t mk_cmd_while(bexpr_t expr, cmd_t cmd_body)
{
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 4;
    arbre->data.cmd_while.test = expr;
    arbre->data.cmd_while.cmd_body = cmd_body;
    return arbre;
}


cmd_t mk_cmd_fct(char *name, char *return_type)
{
    cmd_t arbre = (cmd_t) malloc(sizeof(struct cmd));
    arbre->tag = 5;
    allouer_chaine_256(&(arbre->data.fonction.name));
    allouer_chaine_256(&(arbre->data.fonction.return_type));
    int bufSize = 256 * sizeof(char);
    if (snprintf(arbre->data.fonction.name, bufSize, "%s", name) >= bufSize)
    {
        printf("Nom de fonction trop long. Tag: fbnuyg.\n");
        exit(-1);
    }
    if (snprintf(arbre->data.fonction.return_type, bufSize, "%s", return_type) >= bufSize)
    {
        printf("Type de fonction trop long. Tag: tfvbn.\n");
        exit(-1);
    }
    return arbre;
}


cmd_t mk_cmd_return_from_aexpr(aexpr_t aexpr)
{
    cmd_t arbre = NULL;
    arbre = (cmd_t) malloc(sizeof(struct cmd));
    if (arbre == NULL)
    {
        printf("Impossible d'allouer l'arbre. tag: hjij\n");
        exit(-1);
    }
    arbre->tag = 6;
    arbre->data.cmd_return.tag = 0;
    arbre->data.cmd_return.data.aexpr = aexpr;
    return arbre;
}


char* see_cmd(int level, cmd_t cmd)
{
    char *retour;
    char *chaine0, *chaine1, *chaine2, *chaine3;
    char *indentation = NULL;
    int i;
    int bufSize = 256 * sizeof(char);
    allouer_chaine_256(&retour);

    indentation = malloc((level + 1) * sizeof(char));
    if (indentation == NULL)
    {
        printf("Plus de mémoire disponible pour l'allocation du tampon \"indentanion\". tag: poiuytre\n");
        exit(-1);
    }
    for (i=0; i<level; i++)
    {
        indentation[i] = ' ';
    }
    indentation[i] = '\0';

    switch (cmd->tag)
    {
        case 0 : //skip
            snprintf(retour, bufSize, "%s", "");
            free(indentation);
            return retour;
            break;
        case 1 : //assign
            allouer_chaine_256(&chaine0);
            allouer_chaine_256(&chaine1);

            // si ce n'est pas la premiere renconte, on declare la variable
            if (cmd->data.cmd_ass.var->premiereRencontre == true)
            {
                cmd->data.cmd_ass.var->premiereRencontre == false;
                snprintf(chaine0, bufSize, "%s%s%s%s", indentation, "Var ", cmd->data.cmd_ass.var->name, ";\n");
            }
            else
            {
                snprintf(chaine0, bufSize, "%s", "");
            }

            snprintf(chaine1, bufSize, "%s", cmd->data.cmd_ass.var->name);
            chaine2 = see_aexpr(cmd->data.cmd_ass.expr);
            snprintf(retour, bufSize, "%s%s%s%s%s%s", chaine0, indentation, chaine1, " = ", chaine2, ";");
            free(chaine0);
            free(chaine1);
            free(chaine2);
            free(indentation);
            return retour;
            break;
        case 2 : //seq (;)
            chaine1 = see_cmd(level, cmd->data.cmd_seq.cmd1);
            chaine2 = see_cmd(level, cmd->data.cmd_seq.cmd2);
            snprintf(retour, bufSize, "%s%s%s", chaine1, ";", chaine2);
            free(chaine1);
            free(chaine2);
            free(indentation);
            return retour;
            break;
        case 3 : //if then else
            chaine1 = see_bexpr(cmd->data.cmd_ite.test);
            chaine2 = see_cmd(level, cmd->data.cmd_ite.cmd_then);
            if(cmd->data.cmd_ite.cmd_else != NULL)
            {
                chaine3 = see_cmd(level, cmd->data.cmd_ite.cmd_else);
                snprintf(retour, bufSize, "%s%s%s%s%s%s%s", "if (", chaine1, " )\n{\n", chaine2, "}\nelse\n{\n", chaine3, "}\n");
                free(chaine3);
            }
            else
            {
                snprintf(retour, bufSize, "%s%s%s%s%s", "if (", chaine1, ")\n{\n", chaine2, "}\n");
            }
            free(chaine1);
            free(chaine2);
            free(indentation);
            return retour;
            break;
        case 4 : //while do
            chaine1 = see_bexpr(cmd->data.cmd_while.test);
            chaine2 = see_cmd(level, cmd->data.cmd_while.cmd_body);
            snprintf(retour, bufSize, "%s%s%s%s%s", "while (", chaine1, ")\n{\n", chaine2, "}\n");
            free(chaine1);
            free(chaine2);
            free(indentation);
            return retour;
            break;
        case 5:
            snprintf(retour, bufSize, "%s%s%s%s", cmd->data.fonction.return_type, " ", cmd->data.fonction.name, "()");
            free(indentation);
            return retour;
            break;
        case 6:
            switch(cmd->data.cmd_return.tag)
            {
                case 0:
                    chaine1 = see_aexpr(cmd->data.cmd_return.data.aexpr);
                    break;
                default:
                    printf("%i\n",cmd->data.cmd_return.tag );
                    printf("tag affichage return non reconnu. tag: uytdf\n");
                    exit(-1);
            }
            snprintf(retour, bufSize, "%s%s%s%s", indentation, "return ", chaine1, ";");
            free(indentation);
            return retour;
            break;
        default :
            printf("Tag affichage commande non reconnu.");
            free(indentation);
            free(retour);
            exit(-1);
            break;
    }
}
