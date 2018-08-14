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
#include "language.h"
#include "types.h"
#include "see_tree.h"

int token_main(char **fonction_courante, int *ancient_level_ptr, int *actual_level_ptr, FILE *fichier, cmd_t cmd)
{
    if (*actual_level_ptr != *ancient_level_ptr)
    {
        char *indentation = NULL;
        int i;
        indentation = malloc((*ancient_level_ptr + 1) * sizeof(char));
        if (indentation == NULL)
        {
            printf("Plus de mémoire disponible pour l'allocation du tampon \"indentanion\". tag: poiuytre\n");
            exit(-1);
        }
        if (*actual_level_ptr > *ancient_level_ptr)
        {
            for (i=0; i<*ancient_level_ptr; i++)
            {
                indentation[i] = ' ';
            }
            indentation[i] = '\0';
            fprintf(fichier, "%s%s\n", indentation, "{");
        }
        if (*actual_level_ptr < *ancient_level_ptr)
        {
            for (i=0; i<*actual_level_ptr; i++)
            {
                indentation[i] = ' ';
            }
            indentation[i] = '\0';
            fprintf(fichier, "%s%s\n", indentation, "}");
        }
        free(indentation);
    }
    fprintf(fichier, "%s\n", see_cmd(*actual_level_ptr, cmd));
    return 0;
}