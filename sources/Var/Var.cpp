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
#include <string>
#include <vector>
#include "Var.h"



Var::Var()
{
    tag = -1;
    data.p_entier = 0;
}


Var::~Var()
{

}


Var Var::operator=(int integer)
{
    Var v;
    v.tag = 0;
    v.data.p_entier = integer;
    std::cout << v.data.p_entier << "\n";
    return v;
}

Var Var::operator=(double d)
{
    Var v;
    v.tag = 1;
    v.data.p_double = d;
    return v;
}

Var Var::operator=(bool b)
{
    Var v;
    v.tag = 3;
    v.data.p_boolean = b;
    return v;
}

Var Var::operator=(std::string str)
{
    Var v;
    v.tag = 4;
    v.p_string = str;
    return v;
}


bool Var::operator==(Var const& other)
{
    if (tag != other.tag)
    {
        return false;
    }
    switch(tag)
    {
        case 0:
            return data.p_entier == other.data.p_entier;
            /* not mandatory, but I prefer it this way
             * (may avoid error if return is removed)
             */
            break;
        case 1:
            return data.p_double == other.data.p_double;
            break;
        case 2:
            return data.p_boolean == other.data.p_boolean;
            break;
        case 3:
            return p_string == other.p_string;
            break;
        default:
            std::cout << "Unknown tag in operator==.\n";
            exit(-1);
    }
}


bool Var::operator!=(Var const& other)
{
    if (tag != other.tag)
    {
        return true;
    }
    switch(tag)
    {
        case 0:
            return data.p_entier != other.data.p_entier;
            /* not mandatory, but I prefer it this way
             * (may avoid error if return is removed)
             */
            break;
        case 1:
            return data.p_double != other.data.p_double;
            break;
        case 2:
            return data.p_boolean != other.data.p_boolean;
            break;
        case 3:
            return p_string != other.p_string;
            break;
        default:
            std::cout << "Unknown tag in operator!=.\n";
            exit(-1);
    }
}


Var &Var::operator+=(Var const& other)
{
    if (tag != other.tag)
    {
        //TODO
        exit(-1);
    }
    std::cout << other.tag << "\n";
    std::cout << other.data.p_entier << "\n";
    switch(tag)
    {
        case 0:
            data.p_entier += other.data.p_entier;
            /* not mandatory, but I prefer it this way
             * (may avoid error if return is removed)
             */
            break;
        case 1:
            data.p_double += other.data.p_double;
            break;
        case 2:
            data.p_boolean += other.data.p_boolean;
            break;
        case 3:
            p_string += other.p_string;
            break;
        default:
            std::cout << "Unknown tag in operator+=.\n";
            exit(-1);
    }
    return *this;
}
