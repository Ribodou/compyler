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
#include <unistd.h>
#include "memory.h"

int yyparse();




int main(int argc, const char * argv[])
{
    tab *memoire = NULL;
    char *fonction_courante = NULL;
    int actual_level = 0;
    int ancient_level = 0;
    FILE *fichier = NULL;

    /* allocation de la mémoire */
    memoire = malloc(sizeof(tab));
    if (memoire == NULL)
    {
        printf("Impossible d'allouer la mémoire. tag: fghjtf\n");
        exit(-1);
    }
    memoire->start = NULL;

    /* allocation du nom de la fonction courante */
    fonction_courante = malloc(256 * sizeof(char));
    if (fonction_courante == NULL)
    {
        printf("Impossible d'allouer le nom de la fonction courante\n");
    }

    /* ouverture du fichier de sortie */
    fichier = fopen("output/sortie.cpp", "w+");
    if (fichier == NULL)
    {
        // On affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier de sortie, BANANE!\n");
        exit(-1);
    }

    /* On inclut un include */
    // TODO: Faire ça avec les autes include potentiels
    fprintf(fichier, "%s\n", "#include \"Var.h\"\n\n");

    while (yyparse(&ancient_level, &actual_level, fichier, &fonction_courante, memoire) != -1)
    {
        // repeat
    }

    afficher(memoire);

    free_memory(&memoire);
    fclose(fichier);
}
