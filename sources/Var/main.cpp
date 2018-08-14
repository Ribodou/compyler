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

#include <iostream>
#include "Var.h"




bool test()
{
    Var a, b, c;
    a = 4;
    b = 5;
    a += b;
    return false;
}


int main()
{
    if (test())
    {
        std::cout << "Tests réussis.\n";
        return 0;
    }
    else
    {
        std::cout << "Tests échoués.\n";
        return -1;
    }
}
