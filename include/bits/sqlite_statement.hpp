//

//          Copyright Sundeep S. Sangha 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_STATEMENT_HPP
#define DATA_PATTERN_SQLITE_STATEMENT_HPP

namespace data_pattern_sqlite {

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

} /* helper */

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

template <typename T>
T column ();

template <typename T>
T column (int);

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

template <typename T>
T
sqlite_statement::column (
){
return this->column<T> (this->index++);
}

template <typename T>
T
sqlite_statement::column (
  int _index
){
return helper::column<T>
  (_index, this->stmt);
}

} /* data pattern sqlite */
#endif

