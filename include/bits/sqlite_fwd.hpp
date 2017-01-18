// wrapper around sqlite3

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_BITS_SQLITE_FWD_HPP
#define DATA_PATTERN_BITS_SQLITE_FWD_HPP

#include <memory>
extern "C"{
#include <sqlite3.h>
}

namespace data_pattern_sqlite {

class sqlite_statement;
class sqlite_exception;

template <typename T>
class sqlite_iterator;

using sqlite = std::shared_ptr<sqlite3>;

sqlite
open_database (
  char const * 
);

/*
 * Throws an exception for an sqlite
 * error code, or returns the code if
 * nothing exceptional happens.
 */
int
sqlite_check_error (
  int
);

} /* data_pattern_sqlite */
#endif

