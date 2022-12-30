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

#include "mathutils.h"
#include <iostream>

using namespace std;

vector<bool> composites;
unsigned long next_prime(unsigned long i);


vector<unsigned long> factors(unsigned long i) {
  vector<unsigned long> list;

  // short circuit for a prime
  if (is_prime(i)) {
    list.push_back(i);
    return list;
  }

  unsigned long f = 2;

  while (i > f) {
    if (i % f == 0) {
      list.push_back(f);
      i /= f;
    } else {
      f = next_prime(f);
    }
  }

  if (i == f) list.push_back(i);

  return list;
}


bool perfect(unsigned long i) {
  return i == 6 || i == 28 || i == 496 || i == 8128;
}


// note: the following only works for monotonically increasing tests of i
bool triangular(unsigned long i) {
  static unsigned long last = 1;
  static unsigned long next_add = 2;
  if (last + next_add == i) {
    last = i;
    next_add++;
    return true;
  }
  return false;
}

// note: the following only works for monotonically increasing tests of i
bool square(unsigned long i) {
  static unsigned long next = 1;
  static unsigned long next_sq = 1;
  if (next_sq == i) {
    next++;
    next_sq = next * next;
    return true;
  }
  return false;
}



const unsigned long c_limit = 0x7FFFFFFF;
const unsigned long c_hlimit = 0x3FFFFFFF;

// build a sieve of Eratosthones
void init_math(callback_t callback, int freq) {
  composites.resize(c_limit + 1);

  unsigned long index = 3;
  while (index < c_hlimit) {
    if (!composites[index / 2]) {
      unsigned long i = (index / 2) + index;  // skips every second index
      while (i <= c_limit) {
        composites[i] = true;
        i += index;      // jump 2 indexes
      }
    }
    index += 2;
    if (callback != 0L && (index - 1) % freq == 0) callback(index);
  }
  
}


bool is_prime(unsigned long i) {
  if (i == 2) return true;
  return (1L & i) && !composites[(i - 1) / 2];
}


unsigned long next_prime(unsigned long i) {
  i = (i - 1) / 2;
  while (composites[++i]);
  return i * 2 + 1;
}

