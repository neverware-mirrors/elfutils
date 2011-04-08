/*
   Copyright (C) 2010, 2011 Red Hat, Inc.
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

#ifndef DWARFLINT_CHECKDESCRIPTOR_HH
#define DWARFLINT_CHECKDESCRIPTOR_HH

#include <set>
#include <string>
#include <iosfwd>
#include <vector>

#include "option.hh"

struct checkgroups
  : public std::set<std::string>
{};
std::ostream &operator << (std::ostream &o, checkgroups const &groups);

struct checkdescriptor
{
  class create
  {
    friend class checkdescriptor;
    checkgroups _m_groups;
    char const *const _m_name;
    char const *_m_description;
    bool _m_hidden;
    bool _m_schedule;
    options _m_opts;

  public:
    create (char const *name = NULL);
    create (checkdescriptor const &base); ///< For construction of overrides.
    create &groups (char const *name);

    create &description (char const *d)
    {
      _m_description = d;
      return *this;
    }

    create hidden ()
    {
      _m_hidden = true;
      return *this;
    }

    create option (option_i &opt)
    {
      _m_opts.add (&opt);
      return *this;
    }

    create schedule (bool whether)
    {
      _m_schedule = whether;
      return *this;
    }
  };

  checkdescriptor ();
  checkdescriptor (create const &c);

  char const *name () const { return _m_name; }
  char const *description () const { return _m_description; }

  checkgroups const &groups () const { return _m_groups; }
  bool in_group (std::string const &group) const;

  bool hidden () const { return _m_hidden; }
  bool schedule () const { return _m_schedule; }

  options const &opts () const { return _m_opts; }

  void list (bool verbose) const;

private:
  char const *const _m_name;
  char const *const _m_description;
  checkgroups const _m_groups;
  bool const _m_hidden;
  bool const _m_schedule;
  options const _m_opts;
};

#endif//DWARFLINT_CHECKDESCRIPTOR_HH
