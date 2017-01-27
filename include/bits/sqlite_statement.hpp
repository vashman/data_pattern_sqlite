//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_SQLITE_STATEMENT_HPP
#define DATA_PATTERN_SQLITE_SQLITE_STATEMENT_HPP

#include <string>
#include <data_pattern/raw.hpp>
#include "sqlite_statement_fwd.hpp"

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
int column_count;
bool stepped; //True when the statement has been stepped.
int bind_parameter_count;

public:

/*
 * Column counter used to keep track of which column in the
 * current table is currently active.
 */
int index;

int
get_column_count() const;

int
get_bind_parameter_count() const;

bool
is_stepped() const;

bool
is_done() const;

int
get_state() const;

/* ctor */
explicit
sqlite_statement (sqlite, char const *);
sqlite_statement () = default;
sqlite_statement (sqlite_statement const &) = delete;
sqlite_statement (sqlite_statement &&) = default;
~sqlite_statement();

sqlite_statement &
operator = (sqlite_statement &&) = default;

sqlite_statement &
operator = (sqlite_statement const &) = delete;

/* bind double */
void
bind (int, double);

/* bind int */
void
bind (int, int);

/* bind void * */
void
bind (int, void const *, int);

/* bind char * and bind null */
void
bind (int, char const *);

int
column_bytes (int);

int
column_bytes16 (int);

int
column_type (int);

sqlite3_value *
column_value (int);

void
step();

/* column_int */
int
column_int (int);

sqlite3_int64
column_sqlite3_int64 (int);

/* column_double */
double
column_double (int);

/* column blob */
const void *
column_const_void_ptr (int);

/* column text */
const unsigned char *
column_const_unsigned_char_ptr (int);

/* column text 16 */
const char16_t *
column_const_char16_t_ptr (int);

}; /* sqlite satemenmt */

} /* data pattern sqlite */
#endif
#include "sqlite_statement.tcc"

