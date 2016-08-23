//

//          Copyright Sundeep S. Sangha 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_STATEMENT_HPP
#define DATA_PATTERN_SQLITE_STATEMENT_HPP

namespace data_pattern_sqlite {

/*
 * query_statement wraps an sqlite
 * statement and does some book keeping.
 */
class sqlite_statement {

sqlite3_stmt * stmt;
int state;

/* 
 * When a statement runs, set this to
 * max column.
 */
int max_col;
bool input_type;
bool stepped;
bool row_on_def;
/*
 * Step the statement if another row is
 * present and the end of the current row
 * is reached, other wise does nothing.
 *
int 
row_step();
*/
public:

/*
 * Column counter used to keep track
 * of which column in the current
 * table is currently active.
 */
int index;

int
get_max_col() const;

/* ctor */
explicit
sqlite_statement (
  sqlite &
, char const * // query
);

/* ctor */
//explicit
//sqlite_statement () = default;

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

void
bind (double);

/* bind int */
void
bind (
  int
, int
);

void bind (int);

/* bind void * */
void
bind (
  int
, void const *
, int
);

void bind (void const *, int);

/* bind char * and bind null */
void
bind (
  int
, char const *
);

void bind (char const *);
void bind ();

/* column_int */
int
column_int (
  int
);

sqlite3_int64
column_int64 (
  int
);

/* column_double */
double
column_double (
 int
);

const void *
column_blob (
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

const unsigned char *
column_text (
  int
);

const void *
column_text16 (
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

/* column_int */
int
column_int ();

sqlite3_int64
column_int64 ();

/* column_double */
double
column_double ();

const void *
column_blob ();

int
column_bytes ();

int
column_bytes16 ();

const unsigned char *
column_text ();

const void *
column_text16 ();

int
column_type ();

sqlite3_value *
column_value ();

void
step();

}; /* sqlite satemenmt */

} /* data pattern sqlite */
#endif

