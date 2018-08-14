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

#ifndef __make_tree__
#define __make_tree__

#include "types.h"
#include "memory.h"

aexpr_t mk_aexpr_num(int n);
aexpr_t mk_aexpr_var(tab *memoire, char *fonction_courante, char *name);
aexpr_t mk_aexpr_unop(int op, aexpr_t expr);
aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr);

bexpr_t mk_bexpr_bconst(boolean b);
bexpr_t mk_bexpr_unop(int op, bexpr_t expr);
bexpr_t mk_bexpr_binop(int op, bexpr_t lexpr, bexpr_t rexpr);
bexpr_t mk_bexpr_comp(int op, aexpr_t lexpr, aexpr_t rexpr);

cmd_t mk_cmd_skip(void);
cmd_t mk_cmd_ass(tab *memoire, char *fonction_courante, char *name, aexpr_t expr);
cmd_t mk_cmd_seq(cmd_t cmd1, cmd_t cmd2);
cmd_t mk_cmd_ite(bexpr_t expr, cmd_t cmd_then, cmd_t cmd_else);
cmd_t mk_cmd_while(bexpr_t expr, cmd_t cmd_body);
cmd_t mk_cmd_fct(char *name, char *retun_type);
cmd_t mk_cmd_return_from_aexpr(aexpr_t aexpr);
#endif
