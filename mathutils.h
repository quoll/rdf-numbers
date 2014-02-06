/*
 * Copyright 2005 Paula Gearon
 *
 * This file is part of rdf-generator.
 *
 * rdf-generator is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * rdf-generator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MATHUTILS_H
#define __MATHUTILS_H
#include <vector>

typedef void (*callback_t)(unsigned int i);

void init_math(callback_t callback, int freq = 100000);
bool perfect(unsigned long i);
bool triangular(unsigned long i);
std::vector<unsigned long> factors(unsigned long i);
bool is_prime(unsigned long i);

#endif  // __MATHUTILS_H
