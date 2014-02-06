/*
 * Copyright 2005 Paul Gearon
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

#include <sstream>
#include <assert.h>
#include "roman.h"

using namespace std;

string rdigit(char d, int size);

bool can_be_roman(unsigned long i) {
  return i < 40000;
}


string roman(unsigned long i) {
  ostringstream ss;
  ss << i;
  string s = ss.str();

  int l = s.length();

  assert(l <= 5);

  string result;
  for (int pos = 0; pos < l; pos++) {
    result += rdigit(s.data()[pos], l - pos);
  }
  return result;
}


const char* ones[] = {
  "I", "X", "C", "M", "&#x2182;"
};

const char* fives[] = {
  "V", "L", "D", "&#x2181;"
};


string rdigit(char d, int size) {
  assert(size < 5 || (size == 5 && d < '5'));
  size--;
  string result;
  switch (d - '0') {
    case 3:
      result += ones[size];  // fall through
    case 2:
      result += ones[size];  // fall through
    case 1:
      result += ones[size];
      break;

    case 4:
      result += ones[size];  // fall through
    case 5:
      result += fives[size];
      break;

    case 6:
      result = fives[size];
      result += ones[size];
      break;
    case 7:
      result = fives[size];
      result += ones[size];
      result += ones[size];
      break;
    case 8:
      result = fives[size];
      result += ones[size];
      result += ones[size];
      result += ones[size];
      break;

    case 9:
      result = ones[size];
      result += ones[size + 1];
      break;
  }
  return result;
}

