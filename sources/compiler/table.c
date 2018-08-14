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
#include <string.h>
#include "types.h"
#include "table.h"
#include "memory.h"
#include "fonctions_bien_pratiques.h"



var_t table_lookup_id(char *name)
{
    if(name == NULL)
    {
        fprintf(stderr, "Error in table_lookup_id : name == NULL.\n");
        exit(-1);
    }
    list_var_t iterator = table;
    while(iterator != NULL)
    {
        if(strcmp(name,iterator->var->name) == 0)
        {
            return iterator->var;
        }
        iterator = iterator->next;
    }
    return NULL;
}

//We make the hypothesis that the list is already sorted
var_t table_add_id(char *name)
{
    //Allocate new
    var_t new_var = (var_t) malloc(sizeof(struct var));
    allouer_chaine_256(&(new_var->name));
    int bufSize = 256 * sizeof(char);
    snprintf(new_var->name, bufSize, "%s", name);
    new_var->loc = -1;
    list_var_t new = (list_var_t) malloc(sizeof(struct list_v));
    new->var = new_var;
    new->next = NULL;

    //Find the value of loc & add the guy in the list
    list_var_t iterator = table;

    int i = 0;
    if(iterator != NULL)
    {
        while(iterator->next != NULL)
        {
            //If the integer is already in the list : free
            if(strcmp(name,iterator->var->name) == 0)
            {
                free(new_var);
                free(new);
                return iterator->var;
            }
            //There is some room to add the guy
            if(i+1 != iterator->next->var->loc)
            {
                //#1 : node before (loc is correct)
                //#2 : new node
                //#3 : node after (loc is too big)
                new_var->loc = i+1; //#2 : loc(#1) + 1 = i + 1
                new->next = iterator->next;  //#2->next = #1->next = #3
                iterator->next = new; //#1->next = #2
                return new_var;
            }
            iterator = iterator->next;
            i++;
        }
        //End of the list : add the new node
        new_var->loc = i+1;
        iterator->next = new;
        return new_var;
    }
    else
    {
        //The table is empty! Allocate it
        new_var->loc = 0;
        table = new;
        return new_var;
    }
}

int print_var_values(void)
{
    list_var_t iterator = table;
    while(iterator != NULL)
    {
        //affiche le nom de la variable
        //affiche la valeur contenue dans sa location de mémoire.
        printf("Table : (Name : %s, Loc : %d, Val : %d)\n", iterator->var->name, iterator->var->loc, mem_get_val(iterator->var->loc));
        iterator = iterator->next;
    }
    return EXIT_SUCCESS;
}
