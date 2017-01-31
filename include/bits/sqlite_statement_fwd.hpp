// wrapper around sqlite3

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_BITS_SQLITE_STATEMENT_FWD_HPP
#define DATA_PATTERN_SQLITE_BITS_SQLITE_STATEMENT_FWD_HPP

#include <data_pattern/raw_view.hpp>
#include <string>

namespace data_pattern_sqlite {

/*
 * Throws an exception for an sqlite
 * error code, or returns the code if
 * nothing exceptional happens.
 */
int
sqlite_check_error (int);

class sqlite_statement;

void
step (
  sqlite_statement &
);

bool
is_bind_done (
  sqlite_statement const &
);

bool
is_bind_done (
  sqlite_statement const &
, int
);

bool
has_another_row (
  sqlite_statement const & _stmt
);

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement &
, std::basic_string<char, Traits, Allocator> &&
);

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement &
, std::basic_string<char, Traits, Allocator> &
);

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement &
, std::basic_string<char, Traits, Allocator> const &
);

void
bind (
  sqlite_statement &
, int
);

void
bind (
  sqlite_statement &
, double
);

void
bind (
  sqlite_statement &
, data_pattern::raw_view
);

template <typename Allocator>
void
bind (
  sqlite_statement &
, data_pattern::raw<Allocator> &&
);

// bind null
void
bind (
  sqlite_statement &
);

/* column_int */
int
column_int (
  sqlite_statement &
);

sqlite3_int64
column_sqlite3_int64 (
  sqlite_statement &
);

/* column_double */
double
column_double (
  sqlite_statement &
);

template <
  typename Traits = std::char_traits<unsigned char>
, typename Allocator = std::allocator<unsigned char> >
std::basic_string<unsigned char, Traits, Allocator>
column_string (
  sqlite_statement &
);

data_pattern::raw<>
column_raw (
  sqlite_statement &
);

/* column text 16 * /
const char16_t *
column <const char16_t *> (
  sqlite_statement &
);*/

} /* data_pattern_sqlite */
#endif