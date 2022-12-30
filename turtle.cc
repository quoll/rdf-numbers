/*
 * Copyright 2022 Paula Gearon
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

#include <iostream>
#include <string>
#include <signal.h>

#include "labels.h"
#include "mathutils.h"
#include "roman.h"


void print_header();
void print_footer();
void print_description(unsigned long i);
bool squarable(unsigned long i);
void print_factors(unsigned long i);

unsigned long abort_early;

const unsigned long c_max_index = 0xFFFFFFFF;

extern "C" void sig_handler(int s) {
  abort_early = 1;
}

int main(int argc, char** argv) {
  abort_early = 0;
  init_math(0L);
  signal(SIGUSR1, sig_handler);
  print_header();

  unsigned long max;
  if (argc > 1) {
    max = atol(argv[1]);
    if (max <= 0) max = c_max_index;
  } else max = c_max_index;

  unsigned long index;
  for (index = 1; index <= max; index++) {
    print_description(index);
    if (abort_early) break;
  }

  print_footer();

  return 0;
}


void print_header() {
  std::cout << "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>.\n";
  std::cout << "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>.\n";
  std::cout << "@prefix owl: <http://www.w3.org/2002/07/owl#>.\n";
  std::cout << "@prefix dc: <http://purl.org/dc/terms/>.\n";
  std::cout << "@prefix : <http://quoll.gearon.org/data/numbers#>.\n\n";
}



void print_footer() {
  std::cout << "### End of Numbers" << std::endl;
}


void print_description(unsigned long i) {
  std::cout << ":n" << i << " a :NaturalNumber";
  if (perfect(i)) std::cout << ", :PerfectNumber";

  if (triangular(i)) std::cout << ", :TriangularNumber";
  
  if (i != 1 && is_prime(i)) std::cout << ", :PrimeNumber";

  std::cout << ";\n";
  
  std::cout << "  rdf:value " << i << ";\n";

  std::cout << "  rdfs:label \"" << calc_label(i).c_str() << "\"@en";

  if (can_be_roman(i)) std::cout << ";\n  :roman \"" << roman(i).c_str() << "\"";

  if (squarable(i)) std::cout << ";\n  :square :n" << (i * i);

  print_factors(i);
  
  std::cout << ".\n\n";
}


bool squarable(unsigned long i) {
  return i < 65536;
}


void print_factors(unsigned long i) {
  std::cout << ";\n  :primeFactorization (";
  std::vector<unsigned long> fc = factors(i);
  auto start = fc.begin();
  auto end = fc.end();
  for (std::vector<unsigned long>::const_iterator it = fc.begin(); it != end; it++) {
    if (it != start) std::cout << " ";
    std::cout << ":n" << *it;
  }
  std::cout << ")";
}


