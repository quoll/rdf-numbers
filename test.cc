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
#include <iostream>
#include <stdlib.h>
#include "labels.h"
#include "mathutils.h"
#include "roman.h"

using namespace std;

void callback(unsigned int i) {
  cout << "Primes to: "<< i << endl;
}


int main() {
  try {
    cout << 123456 << ": " << calc_label(123456) << endl;
    cout << 12345 << ": " << calc_label(12345) << endl;
    cout << 1234 << ": " << calc_label(1234) << endl;
    cout << 123 << ": " << calc_label(123) << endl;
    cout << 12 << ": " << calc_label(12) << endl;
    cout << 1 << ": " << calc_label(1) << endl;
    cout << 101 << ": " << calc_label(101) << endl;
    cout << 5011 << ": " << calc_label(5011) << endl;
    cout << 1854614940 << ": " << calc_label(1854614940) << endl;
    cout << 1000000001 << ": " << calc_label(1000000001) << endl;
    cout << endl;
    srand(42);
    for (int i = 0; i < 10; i++) {
      unsigned int x = rand();
      cout << x << ": " << calc_label(x) << endl;
    }
  } catch (exception& e) {
    cerr << "Error: " << e.what() << endl;
  }

  cout << "Triangular numbers:" << endl;
  for (int t = 2; t < 100; t++) {
    if (triangular(t))
      cout << t << " ";
  }
  cout << endl;

  for (int r = 1; r <= 20; r++) {
    cout << r << ": " << roman(r).c_str() << endl;
  }
  cout << 9358 << ": " << roman(9358).c_str() << endl;
  cout << 8000 << ": " << roman(8000).c_str() << endl;
  cout << 4001 << ": " << roman(4001).c_str() << endl;
  cout << 1988 << ": " << roman(1988).c_str() << endl;
  cout << 101 << ": " << roman(101).c_str() << endl;
  
  cout << endl << "Initializing the primes..." << endl;
  init_math(0L);
  cout << "Initialized" << endl;

  cout << "Factors:" << endl;
  for (int x = 6; x < 26; x++) {
    cout << x << ":";
    vector<unsigned long> l = factors(x);
    for (vector<unsigned long>::const_iterator ci = l.begin(); ci != l.end(); ci++)
      cout << " " << *ci;
    cout << endl;
  }

  return 0;
}

