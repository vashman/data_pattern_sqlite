// data_model sqlite implementation

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_CPP
#define DATA_PATTERN_SQLITE_CPP

#include "../include/sqlite.hpp"

namespace data_pattern_sqlite {

/* sqlite_exception ctor  */
sqlite_exception::sqlite_exception (
  std::string const _what_arg
, int _rv
)
: std::runtime_error (_what_arg)
, err (_what_arg)
, rv (_rv) {
}

/* check for sqlite error */
int
sqlite_check_error (
  int _rv
){
switch (_rv){
  case SQLITE_DONE:
  case SQLITE_ROW:
  case SQLITE_OK: return _rv;

  default:
  throw
  sqlite_exception (std::string(sqlite3_errstr(_rv)), _rv);
}
}

sqlite
open_database (
  char const * _file
){
sqlite3 * temp = NULL;
sqlite_check_error (sqlite3_open(_file, &(temp)));
return sqlite {temp, sqlite3_close};
}

} /* data_pattern_sqlite */
#include "bits/sqlite_statement.cpp"
#endif

