//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_STATEMENT_HPP
#define DATA_PATTERN_SQLITE_STATEMENT_HPP

namespace data_pattern_sqlite {

/*
 * Wraps an sqlite statement and does book keeping.
 */
class sqlite_statement {

sqlite3_stmt * stmt;
int state;
sqlite db;

/* 
 * When a statement runs, set this to
 * result of sqlite3_column_count.
 */
int max_col;
bool stepped; //True when the statement has been stepped.
int var_count;

void
step_if();

void
step_if_input();

public:

/*
 * Column counter used to keep track
 * of which column in the current
 * table is currently active.
 */
int index;

int
get_max_col() const;

int
get_var_count() const;

bool
is_stepped() const;

bool
is_done() const;

/* ctor */
explicit
sqlite_statement (
  sqlite
, char const * // query
);

/* ctor */
explicit
sqlite_statement () = default;

/* ctor copy */
sqlite_statement (
  sqlite_statement const &
) = delete;

/* ctor move */
sqlite_statement (
  sqlite_statement &&
) = default;

/* operator = */
sqlite_statement &
operator = (
  sqlite_statement &&
) = default;

/* operator = */
sqlite_statement &
operator = (
  sqlite_statement const &
) = delete;

/* dtor */
~sqlite_statement();

/* bind double */
void
bind (
  int
, double
);

/* bind int */
void
bind (
  int
, int
);

/* bind void * */
void
bind (
  int
, void const *
, int
);

/* bind char * and bind null */
void
bind (
  int
, char const *
);

void
bind (
  char const *
);

void
bind (
  int
);

void
bind (
  double
);

void
bind (
  void const *
, int
);

void
bind ();

template <typename T>
T
column ();

template <typename T>
T
column (
  int
);

int
column_bytes (
  int
);

int
column_bytes16 (
  int
);

int
column_type (
  int
);

sqlite3_value *
column_value (
  int
);

void
step();

}; /* sqlite satemenmt */

namespace helper {

template <typename T>
T column (
  int
, sqlite3_stmt *
);

/* column_int */
template <>
int
column <int> (
  int
, sqlite3_stmt *
);

template <>
sqlite3_int64
column <sqlite3_int64> (
  int
, sqlite3_stmt *
);

/* column_double */
template <>
double
column <double> (
 int
, sqlite3_stmt *
);

/* column blob */
template <>
const void *
column <const void *> (
  int
, sqlite3_stmt *
);

/* column text */
template <>
const unsigned char *
column <const unsigned char *> (
  int
, sqlite3_stmt *
);

/* column text 16 */
template <>
const char16_t *
column <const char16_t *> (
  int
, sqlite3_stmt *
);

} /* helper */ } /* data pattern sqlite */
#endif
#include "sqlite_statement.tcc"

