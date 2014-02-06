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

#ifndef __LABELS_H
#define __LABELS_H

#include <string>
#include <exception>

struct format_exception : public std::exception {
  std::string m_desc;
  format_exception(const std::string& desc) : m_desc(desc) {}
  virtual ~format_exception() throw() {}
  virtual const char* what() { return m_desc.c_str(); }
};

std::string calc_label(unsigned long i) throw (format_exception);

#endif  // __LABELS_H

