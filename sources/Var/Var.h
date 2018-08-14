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

#include <string>


/*
 * This class is designed to represent every data in the python program.
 * Its operators has been surcharged to allow the compiler to write a
 * beautiful code and thus improve readability.
 * If you want to improve the program, you can simply change the type of
 * any variable you want, since it should have the same operator as
 * before, it should work just nice!
 */
class Var
{
    private:

    int tag;
    union
    {
        int p_entier;  // 0
        double p_double;  // 1
        bool p_boolean;  // 2
    } data;
    std::string p_string;  // 3


    public:
    Var();
    ~Var();
    Var operator=(int integer);
    Var operator=(double d);
    Var operator=(bool b);
    Var operator=(std::string str);
    bool operator==(Var const& other);
    bool operator!=(Var const& other);
    Var &operator+=(Var const& other);
    //Var &operator-=(const& Var other);
    //Var &operator*=(const& Var other);
    //Var &operator/=(const& Var other);
};
