// wrapper around sqlite3

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_BITS_SQLITE_HPP
#define DATA_PATTERN_BITS_SQLITE_HPP

namespace data_pattern_sqlite {

/* sqlite */
class sqlite {
public:

/* 
 * Takes the filepath "char const *" to
 * database location.
 */
explicit
sqlite (
  char const *
);

/* dtor */
~sqlite ();

/* copy ctor */
sqlite (sqlite const &) = delete;

/* operator = */
sqlite &
operator = (sqlite const &) = delete;

/* move ctor */
sqlite (sqlite &&) = default;

/* move operator = */
sqlite &
operator = (sqlite &&) = default;

private:

sqlite3 * db;

// statement needs access to db ptr.
friend sqlite_statement;
}; /* sqlite  */

 } /* data_pattern_sqlite */
#endif

