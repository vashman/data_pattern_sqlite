//

//          Copyright Sundeep S. Sangha 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_ITERATOR_HPP
#define DATA_PATTERN_SQLITE_ITERATOR_HPP

#include <iterator>

namespace data_pattern_sqlite {

template <typename T>
sqlite_iterator;

namespace bits {

template <typename T>
struct sqlite_iterator_base {

typedef T value_type;
typedef 

sqlite_statement * stmt;

sqlite_iterator<T>
operator ++ (int);

sqlite_iterator<T> &
operator ++ ();

sqlite_iterator<T> &
operator = (
  T const &
);

bool
operator == (
  sqlite_statement const &
) const;

T &
operator * ();

T *
operator -> ();

};

bool
operator != (
  sqlite_statement const & _lhs
, sqlite_statement const & _rhs
);

template <>
sqlite_iterator <>

} /* bits */

} /* data_pattern_sqlite */
#endif

