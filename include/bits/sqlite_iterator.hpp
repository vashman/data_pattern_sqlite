//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_ITERATOR_HPP
#define DATA_PATTERN_SQLITE_ITERATOR_HPP

#include <iterator>
#include <memory>

namespace data_pattern_sqlite {

template <typename T>
class sqlite_iterator {

typedef std::input_iterator_tag iterator_catagory;
typedef T value_type;
typedef std::size_t difference_type;
typedef T * pointer;
typedef T & reference;

std::shared_ptr<sqlite_statement> stmt;
T temp;
int var_count;

public:

explicit
sqlite_iterator (
  sqlite_statement & _stmt
);

sqlite_iterator ();

sqlite_iterator (
  sqlite_iterator const &
) = default;

sqlite_iterator (
  sqlite_iterator &&
) = default;

sqlite_iterator &
operator = (
  sqlite_iterator const &
) = default;

sqlite_iterator &
operator = (
  sqlite_iterator &&
) = default;

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
this->stmt->bind(_var, this->stmt->index);
return *this;
}

bool
operator == (
  sqlite_iterator<T> const & _rhs
) const {
  if (_rhs.stmt == nullptr && this->stmt == nullptr)
  return true;
  else if (_rhs.stmt == nullptr)
  return this->stmt->is_done();
  else if (this->stmt == nullptr)
  return _rhs.is_done();
return (this->stmt->is_done() && _rhs.stmt->is_done());
}

bool
operator != (
  sqlite_iterator<T> const & _rhs
) const {
return !(*this == _rhs);
}

T &
operator * (){
this->temp =
  this->stmt->template column <T>
  (this->stmt->index);
return this->temp;
}

T *
operator -> (){
this->temp =
  this->stmt->template column <T>
  (this->stmt->index);
return &this->temp;
}
};

} /* data_pattern_sqlite */
#endif
#include "sqlite_iterator.tcc"

