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

#include <string>
#include <sstream>
#include <assert.h>
#include "labels.h"

using namespace std;

string place_label(int pos) throw (format_exception);
string group_label(char* buffer, bool first = false);
inline string digit(int d);
inline string teen_digit(int d);
inline string ten_digit(int d);

string calc_label(unsigned long i) throw (format_exception) {
  ostringstream ss;
  ss << i;
  string s = ss.str();
  int len = s.length();

  
  char buf[4] = "000";
  
  // p is an offset into a group of 3
  int p = (3 - (len % 3)) % 3;
  // q is the offset into the string
  int q;
  for (q = 0; p < 3; p++, q++) buf[p] = s.data()[q];

  string result(group_label(buf, true));
  if (q != s.length()) result += place_label(s.length() - q);

  // repeat for all the groups of 3
  while (q != s.length()) {
    // fill the buffer with the next group
    for (p = 0; p < 3; p++) buf[p] = s.data()[q++];
    // ignore empty groups
    if (buf[0] != '0' || buf[1] != '0' || buf[2] != '0') {
      result += " " + group_label(buf);
      if (q != s.length()) result += place_label(s.length() - q);
    }
  }

  return result;
}


string place_label(int pos) throw (format_exception) {
  assert(pos % 3 == 0);
  switch (pos) {
    case 0:
      return "";
    case 3:
      return " thousand";
    case 6:
      return " million";
    case 9:
      return " billion";
    case 12:
      return " trillion";
  }
  
  throw format_exception("Number too large");
}


string group_label(char* buffer, bool first) {
  string result;
  // determine the hundred value
  if (buffer[0] != '0') {
    result = digit(buffer[0]);
    result += " hundred";
    if (buffer[1] != '0' || buffer[2] != '0')
      result += " and ";
  } else {
    if (!first)
      result += "and ";
  }

  if (buffer[1] != '0') {
    // do the tens value
    if (buffer[1] != '1') {
      result += ten_digit(buffer[1]);
      if (buffer[2] != '0') {
        result += "-" + digit(buffer[2]);
      }
    } else {
      // not a normal tens, instead in the teens
      result += teen_digit(buffer[2]);
    }
  } else {
    // units only
    if (buffer[2] != '0')
      result += digit(buffer[2]);
  }

  return result;
}


const char* digits[] = {
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

inline string digit(int d) {
  return digits[d - '1'];
}


const char* teen_digits[] = {
  "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

inline string teen_digit(int d) {
  return teen_digits[d - '0'];
}

 
const char* ten_digits[] = {
  "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
};

inline string ten_digit(int d) {
  return ten_digits[d - '2'];
}

