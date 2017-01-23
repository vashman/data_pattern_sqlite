// wrapper around sqlite3

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_BITS_SQLITE_EXCEPTION_HPP
#define DATA_PATTERN_SQLITE_BITS_SQLITE_EXCEPTION_HPP

#include <stdexcept>

namespace data_pattern_sqlite {

/* sqlite exception */
struct sqlite_exception : public std::runtime_error {
  
explicit
sqlite_exception (std::string const, int);
sqlite_exception (sqlite_exception const &) = default;
sqlite_exception (sqlite_exception &&) = default;
~sqlite_exception () noexcept = default;

sqlite_exception &
operator = (sqlite_exception const &) = default;

sqlite_exception &
operator = (sqlite_exception &&) = default;

std::string const err;
int const rv;
}; /* sqlite exception */

} /* data_pattern_sqlite */
#endif

