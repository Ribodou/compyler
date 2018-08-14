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
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "see_tree.h"
#include "memory.h"



value *create_value(char *name)
{
    value *val = NULL;
    val = malloc(sizeof(value));
    if (val == NULL)
    {
        printf("Impossible d'allouer de la mémoire. tag: oiu56bkg\n");
        exit(-1);
    }
    val->var_name = NULL;
    int size = (strlen(name) + 1) * sizeof(char);
    val->var_name = malloc(size);
    if (snprintf(val->var_name, size, "%s", name) >= size)
    {
        // n'est pas sensé arriver, vérification par acquis de conscience
        printf("Impossible de recopier le nom de la variable. tag: uytfv\n");
        exit(-1);
    }
    val->next = NULL;
    return val;
}


key *create_key(char *name)
{
    key *clef = NULL;
    clef = malloc(sizeof(key));
    if (clef == NULL)
    {
        printf("Erreur creation clef. Tag: FGZKGY.\n");
        exit(-1);
    }
    int size = (strlen(name) + 1) * sizeof(char);
    clef->fonc_name = malloc(size);
    if (snprintf(clef->fonc_name, size, "%s", name) >= size)
    {
        printf("Pas assez de place pour recopier le nom de la fonction! tag: 8446456\n");
        exit(-1);
    }
    clef->head = NULL;
    clef->next = NULL;
    return clef;
}


void ajout_memoire(tab *memoire, char *fonc_name, char *var_name)
{
    if (memoire->start == NULL)
    {
        key *clef = create_key(fonc_name);
        value *valeur = create_value(var_name);
        memoire->start = clef;
        memoire->start->head = valeur;
    }
    else
    {
        key *itere_clef = memoire->start;
        key *clef = NULL;
        while (itere_clef != NULL)
        {
            if (strcmp(itere_clef->fonc_name, fonc_name) == 0)
            {
                clef = itere_clef;
                itere_clef = NULL;
            }
            else
            {
                itere_clef = itere_clef->next;
            }
        }
        if (clef == NULL)
        {
            // aucune clef ne correspond à cette fonction
            // créons-la là (désolé)
            clef = create_key(fonc_name);
            // itere_clef pointe vers la fin de la table, pas d'élément suivant à gérer si on ajoute après lui
            // c'est dingue, on croirait presque que ça a été pensé avant!

            // ...mais en fait non
            // je suis le roi de l'impro
            itere_clef->next = clef;
        }

        // a-t-ton déja rencontré cette variable dans cette fonction?
        // cas trivial, c'est la premiere variable que l'on croise une variable dans cette fonction
        if (clef->head == NULL)
        {
            value *valeur = create_value(var_name);
            clef->head = valeur;
        }
        else
        {
            value *iterer_valeur = clef->head;
            value *valeur = NULL;
            do
            {
                if (strcmp(iterer_valeur->var_name, var_name) == 0)
                {
                    valeur = iterer_valeur;
                }
                if (iterer_valeur->next != NULL)
                {
                    iterer_valeur = iterer_valeur->next;
                }
            } while (iterer_valeur->next != NULL);
            if (valeur == NULL)
            {
                // on n'a pas trouvé la variable => on l'ajoute
                valeur = create_value(var_name);
                iterer_valeur->next = valeur;
            }
        }
    }
}


value *get_names(tab *memoire, char *fonc_name)
{
    value *valeur = NULL;
    key *iterer = memoire->start;
    key *clef = NULL;

    if (memoire->start == NULL)
    {
        return valeur;  // NULL
    }
    do
    {
        if (strcmp(clef->fonc_name, fonc_name) == 0)
        {
            clef = iterer;
        }
        /* Si la table n'a qu'un élément, on doit s'arreter. */
        if (iterer->next != NULL)
        {
            iterer = iterer->next;
        }
    } while(iterer->next != NULL);
    if (clef == NULL)
    {
        return valeur;  // NULL
    }
    return clef->head;
}


void free_all_values_of_a_key(key *clef)
{
    value *valeur;
    while(clef->head != NULL)
    {
        valeur = clef->head;
        clef->head = valeur->next;
        free(valeur);
    }
}

void free_memory(tab **memoire_ptr)
{
    key *clef;
    while((*memoire_ptr)->start != NULL)
    {
        clef = (*memoire_ptr)->start;
        (*memoire_ptr)->start = clef->next;
        free_all_values_of_a_key(clef);
        free(clef);
    }
    free(*memoire_ptr);
}


boolean est_dans_fonction(tab *memoire, char *fonc_name, char *var_name)
{
    key *clef = NULL;
    key *iter_key = memoire->start;
    
    /* trouvons le maillon de la fonction */
    while(iter_key != NULL)
    {
        if (strcmp(iter_key->fonc_name, fonc_name) == 0)
        {
            /* on a trouvé la bonne clef, on arrete l'iteration
            (passer iter_key à NULL fait échouer le test dans le while) */
            clef = iter_key;
            iter_key = NULL;
        }
        else
        {
            iter_key = iter_key->next;
        }
    }

    /* si la clef n'existe pas, on renvoit false */
    if (clef == NULL)
    {
        return false;
    }

    /* cherchons la valeur dont le nom est var_name */
    value *iter_value = clef->head;
    while (iter_value != NULL)
    {
        if (strcmp(iter_value->var_name, var_name) == 0)
        {
            return true;
        }
        iter_value = iter_value->next;
    }
    return false;
}


void afficher(tab *memoire)
{
    key *clef = memoire->start;
    while(clef != NULL)
    {
        printf("Nom de la fonction: %s\n", clef->fonc_name);
        value *val = clef->head;
        while (val != NULL)
        {
            printf("Nom de la variable: %s\n", val->var_name);
            val = val->next;
        }
        printf("\n\n");
        clef = clef->next;
    }
}