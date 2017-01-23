//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_SQLITE_ITERATOR_TCC
#define DATA_PATTERN_SQLITE_SQLITE_ITERATOR_TCC

#include <iterator>
#include <memory>

namespace data_pattern_sqlite {

template <typename T>
sqlite_iterator<T>::sqlite_iterator (
  sqlite_statement & _stmt
)
: stmt (& _stmt, [](sqlite_statement*){})
, temp (stmt)
{}

template <typename T>
sqlite_iterator<T>::sqlite_iterator ()
: stmt (nullptr)
, temp (stmt)
{}

} /* data_pattern_sqlite */
#endif

