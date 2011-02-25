/* Pedantic checking of DWARF files
   Copyright (C) 2008,2009,2010,2011 Red Hat, Inc.
   This file is part of Red Hat elfutils.

   Red Hat elfutils is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 2 of the License.

   Red Hat elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with Red Hat elfutils; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301 USA.

   Red Hat elfutils is an included package of the Open Invention Network.
   An included package of the Open Invention Network is a package for which
   Open Invention Network licensees cross-license their patents.  No patent
   license is granted, either expressly or impliedly, by designation as an
   included package.  Should you wish to participate in the Open Invention
   Network licensing program, please visit www.openinventionnetwork.com
   <http://www.openinventionnetwork.com>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "../src/dwarfstrings.h"
#include "pri.hh"
#include <sstream>
#include "c++/dwarf"

std::ostream &
pri::operator << (std::ostream &os, pri::pribase const &obj)
{
  return os << obj.m_s;
}

pri::locexpr_opcode::locexpr_opcode (int opcode)
  : pribase (dwarf_locexpr_opcode_string (opcode))
{}

std::ostream &
pri::operator << (std::ostream &os, pri::ref const &obj)
{
  std::stringstream ss;
  ss << std::hex << "DIE " << obj.off;
  return os << ss.str ();
}

std::ostream &
pri::operator << (std::ostream &os, pri::hex const &obj)
{
  std::stringstream ss;
  if (obj.pre)
    ss << obj.pre << " ";
  ss << std::hex << "0x" << obj.value;
  return os << ss.str ();
}

std::ostream &
pri::operator << (std::ostream &os, pri::range const &obj)
{
  return os << "[" << pri::addr (obj.start)
	    << ", " << pri::addr (obj.end) << ")";
}
