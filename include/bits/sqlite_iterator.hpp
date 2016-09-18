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
class sqlite_iterator {

typedef T value_type;
//typedef 

sqlite_statement * stmt;
T temp;
int var_count;

public:

sqlite_iterator (
  sqlite_statement & _stmt
)
: stmt (& _stmt)
, temp ()
, var_count (0)
{
  // Used output or input statment without result set.
  if (_stmt.is_stepped() && (_stmt.get_max_col() <= 0))
  throw "fail";
}

sqlite_iterator (sqlite_iterator<T> const &) = default;
sqlite_iterator (sqlite_iterator<T> &&) = default;

sqlite_iterator<T> &
operator = (sqlite_iterator<T> const &) = default;

sqlite_iterator<T> &
operator = (sqlite_iterator<T> &&) = default;

~sqlite_iterator() = default;

sqlite_iterator<T>
operator ++ (int) {
auto temp_iter (*this);
++this->stmt->index;
return temp_iter;
}

sqlite_iterator<T> &
operator ++ (){
++this->stmt->index;
return *this;
}

sqlite_iterator<T> &
operator = (
  T const & _var
){
this->stmt->bind
  (_var, this->stmt->index);
return *this;
}

bool
operator == (
  sqlite_iterator<T> const &
) const {
return false;
}

T &
operator * (){
this->temp =
  this->stmt.template column <T>
  (this->stmt->index);
return this->temp;
}

T *
operator -> (){
this->temp =
  this->stmt.template column <T>
  (this->stmt->index);
return &this->temp;
}
};

} /* data_pattern_sqlite */
#endif

