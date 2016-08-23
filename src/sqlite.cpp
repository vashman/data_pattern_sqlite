// data_model sqlite implementation

//          Copyright Sundeep S. Sangha 2013 - 2014.
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

namespace bits {
/* check for sqlite error */
int
check_error (
  int _rv
){
switch (_rv){
  case SQLITE_DONE:
  case SQLITE_ROW:
  case SQLITE_OK: return _rv;

  default:
    throw sqlite_exception (
     std::string(sqlite3_errstr(_rv))
    , _rv
    );
}
}
} /* bits */

/* sqlite ctor */
sqlite::sqlite (
  char const * _file
)
: db (NULL) {
bits::check_error (
  sqlite3_open(_file, & (this->db)) );
}

sqlite::~sqlite(){
sqlite3_close(db);
}

} /* data_pattern_sqlite */
#include "bits/sqlite_statement.cpp"
#endif

