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
#include "table.h"
#include "memory.h"


int yyparse();
/*
 * implementer une table de hachage {nom_fonction: [nom_var_0,
 *                                                  nom_var_1,
 *                                                  nom_var_2]}
 * pour ecrire de belles declaration.
 * Refaire une passe pour l'écriture.
 */

int main(int argc, const char * argv[])
{
    table = NULL;
    memoire = NULL;
    // on se garde de la place (passer aux listes
    // pour une implementation plus souple)
    memoire = (int*) malloc(56*sizeof(int));
    if (memoire == NULL)
    {
        printf("Impossible d'allouer la mémoire. tag: fghjtf\n");
        exit(-1);
    }

    fichier = fopen("output/sortie.cpp", "w+");
    if (fichier == NULL)
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier de sortie\n");
        exit(-1);
    }
    actual_level = 0;
    ancient_level = 0;


    fprintf(fichier, "%s\n", "#include \"Var.h\"\n\n");
    while (yyparse() != -1)
    {
        // repeat
    }
    fclose(fichier);
}
