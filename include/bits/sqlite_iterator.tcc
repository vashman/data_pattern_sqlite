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
sqlite_iterator_input<T>::sqlite_iterator_input (
  sqlite_statement & _stmt
)
: stmt (& _stmt)
, temp ()
, got_var (false)
, index (_stmt.index)
{}

template <typename T>
sqlite_iterator_input<T>::sqlite_iterator_input (
  sqlite_statement & _stmt
, int _index
)
: stmt (& _stmt)
, temp ()
, got_var (false)
, index (_index)
{}

template <typename T>
template <typename U>
sqlite_iterator_input<T>::sqlite_iterator_input (
  sqlite_statement & _stmt
, sqlite_iterator_input<U> const & _stmt2
)
: stmt (& _stmt)
, temp ()
, got_var (false)
, index (_stmt2.index)
{}

template <typename T>
sqlite_iterator_input<T>::sqlite_iterator_input ()
: stmt (nullptr)
, temp ()
, got_var(true)
, index(-1)
{}

sqlite_iterator_output::sqlite_iterator_output (
  sqlite_statement & _stmt
)
: stmt (& _stmt)
, index (1+_stmt.index)
{}

sqlite_iterator_output::sqlite_iterator_output ()
: stmt (nullptr)
, index (-1)
{}

} /* data_pattern_sqlite */
#endif

