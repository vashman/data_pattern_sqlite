// wrapper around sqlite3

//          Copyright Sundeep S. Sangha 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_HPP
#define DATA_PATTERN_SQLITE_HPP

extern "C"{
#include <sqlite3.h>
}
#include <stdexcept>

namespace data_pattern_sqlite {

class sqlite_statement;
class sqlite_exception;
class sqlite;

template <typename T>
class sqlite_iterator;

/* sqlite exception */
struct sqlite_exception
: public std::runtime_error {
  
explicit
sqlite_exception (
  std::string const
, int
);

std::string const err;
int const rv;
}; /* sqlite exception */

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

namespace bits {
/*
 * Throws an exception for an sqlite
 * error code, or returns the code if
 * nothing exceptional happens.
 */
int
check_error (
  int
);

} /* bits */

} /* data_pattern_sqlite */
#include "bits/sqlite_statement.hpp"
#include "bits/sqlite_iterator.hpp"
#endif

