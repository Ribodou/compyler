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

#ifndef __memory__
#define __memory__

#include "types.h"

/* La mémoire est à voir comme un dictionnaire Python: chaque clef est le nom
 * d'une fonction et la valeur associée à cette clef est la liste des noms des 
 * variables de cette fonction.
 * 
 * 
 * Un petit schéma pour les non Pythonistes (bouh...)
 * 
 *       start           next            next           next
 * tab     ->     key     ->     key     ->      key     ->     NULL
 * 
 *                 | head         | head          | head
 *                 v              v               v
 * 
 *               value          value           value
 * 
 *                 | next         | next          | next
 *                 v              v               v
 * 
 *               value          NULL             NULL
 *                 | next
 *                 v
 *                NULL
 */


typedef struct _value
{
    char *var_name;
    struct _value *next;
} value;


typedef struct _key
{
    char *fonc_name;
    value *head;
    struct _key *next;
} key;


typedef struct _tab
{
    key *start;
} tab;



/*
 * Alloue une structure value et initialise var_name au parametre name.
 * Set next to NULL.
 * @param name: the name of the variable
 * @return: the value
 */
value *create_value(char *name);


/*
 * Alloue une structure key et initialise var_fonc au parametre name.
 * Set head and next to NULL.
 * @param name: the name of the function
 * @return: the key
 */
key *create_key(char *name);


/*
 * Ajoute une vakeur a la clef de nom fonc_name. Si la clef n'existe pas, on la
 * créer. Si la valeur éxiste déja, on ne fait rien.
 * @param memoire: la mémoire (table de hachage)
 * @param fonc_name: the name of the function
 * @param var_name: the name of the function
 */
void ajout_memoire(tab *memoire, char *fonc_name, char *var_name);


/*
 * Retourne la liste des values (variables) de la fonction nommée fonc_name.
 * @param memoire: la mémoire (table de hachage)
 * @param fonc_name: the name of the function
 * @return: a pointer to the first value
 */
value *get_names(tab *memoire, char *fonc_name);


/*
 * Libère toutes les valeurs assosciées à une clef.
 * @param clef: la clef dont on veut supprimer toutes les valeurs.
 */
void free_all_values_of_a_key(key *clef);


/*
 * Libère la mémoire.
 * @param memoire_ptr: un pointeur sur la mémoire (table de hachage)
 */
void free_memory(tab **memoire);


/*
 * Renvoie true si une variable de nom var_name est dans la fonction fonc_name.
 * Renvoie false sinon.
 * @param memoire: la mémoire (table de hachage)
 * @param fonc_name: le nom de la fonction dans laquelle chercher.
 * @param var_name: le nom de la variable a chercher.
 * @return: un boolen
 */
boolean est_dans_fonction(tab *memoire, char *fonc_name, char *var_name);


/*
 * Affiche le nom de toute les variable de toutes les fonctions.
 * @param memoire: la mémoire (table de hachage)
 */
void afficher(tab *memoire);
#endif
