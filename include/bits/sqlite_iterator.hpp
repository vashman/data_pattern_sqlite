//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_BITS_SQLITE_ITERATOR_HPP
#define DATA_PATTERN_SQLITE_BITS_SQLITE_ITERATOR_HPP

#include <iterator>

namespace data_pattern_sqlite {
namespace bits {

template <typename T>
T column (sqlite_statement &, int);

template <>
int
column <int>(
  sqlite_statement & _stmt
, int _index
){
return _stmt.column_int(_index);
}

template <>
double
column <double>(
  sqlite_statement & _stmt
, int _index
){
return _stmt.column_double(_index);
}

template <>
sqlite3_int64
column <sqlite3_int64> (
  sqlite_statement & _stmt
, int _index
){
return _stmt.column_sqlite3_int64(_index);
}

template <>
data_pattern::raw<>
column <data_pattern::raw<>> (
  sqlite_statement & _stmt
, int _index
){
return _stmt.column_raw(_index);
}

template <>
sqlite_statement::string_t
column <sqlite_statement::string_t> (
  sqlite_statement & _stmt
, int _index
){
return _stmt.column_string(_index);
}

} /* bits */

template <typename T>
class sqlite_iterator_input {

sqlite_statement * stmt;
T temp;
bool got_var;
int index;

public:

typedef std::input_iterator_tag iterator_catagory;
typedef T value_type;
typedef std::size_t difference_type;
typedef T * pointer;
typedef T & reference;

explicit
sqlite_iterator_input (sqlite_statement &);
sqlite_iterator_input ();
sqlite_iterator_input (sqlite_statement &, int);

template <typename U>
sqlite_iterator_input (
  sqlite_statement &
, sqlite_iterator_input<U> const &
);

~sqlite_iterator_input() = default;

sqlite_iterator_input (
  sqlite_iterator_input const &
) = default;

sqlite_iterator_input (
  sqlite_iterator_input &&
) = default;

sqlite_iterator_input &
operator = (sqlite_iterator_input const &) = default;

sqlite_iterator_input &
operator = (sqlite_iterator_input &&) = default;

sqlite_iterator_input
operator ++ (int) {
sqlite_iterator_input temp_iter (*this);
++this->index;
this->got_var = false;
return temp_iter;
}

sqlite_iterator_input &
operator ++ (){
++this->index;
this->got_var = false;
return *this;
}

bool
operator == (
  sqlite_iterator_input const & _rhs
) const {
  if (_rhs.stmt == nullptr && this->stmt == nullptr)
  return true;

  else if (_rhs.stmt == nullptr)
  return this->stmt->is_done();

  else if (this->stmt == nullptr) return _rhs.is_done();

return (this->stmt->is_done() && _rhs.stmt->is_done());
}

bool
operator != (
  sqlite_iterator_input const & _rhs
) const {
return !(*this == _rhs);
}

T &
operator * (){
this->get_var();
return this->temp;
}

T *
operator -> (){
this->get_var();
return &this->temp;
}

void
get_var (
){
  if(false == this->got_var){
    if(has_another_row(*this->stmt)
    && this->index >= this->stmt->get_column_count()
    ){
    step(*this->stmt); // Get next row.
    }
  this->temp = bits::column<T>(*this->stmt, this->index);
  this->got_var = true;
  }
}
}; /* sqlite iterator input */

class sqlite_iterator_output {

sqlite_statement * stmt;
int index;

public:

typedef std::output_iterator_tag iterator_catagory;
typedef void value_type;
typedef int difference_type;
typedef void * pointer;
typedef sqlite_iterator_output & reference;

explicit
sqlite_iterator_output (sqlite_statement & _stmt);
sqlite_iterator_output ();
~sqlite_iterator_output() = default;

sqlite_iterator_output (
  sqlite_iterator_output const &
) = default;

sqlite_iterator_output (
  sqlite_iterator_output &&
) = default;

sqlite_iterator_output &
operator = (sqlite_iterator_output const &) = default;

sqlite_iterator_output &
operator = (sqlite_iterator_output &&) = default;

template <typename T>
sqlite_iterator_output &
operator = (
  T const & _var
){
this->stmt->bind(this->index, _var);
  if (is_bind_done(*this->stmt, this->index))
  step(*this->stmt);
return *this;
}

sqlite_iterator_output
operator ++ (int) {
sqlite_iterator_output temp_iter (*this);
++this->index;
return temp_iter;
}

sqlite_iterator_output &
operator ++ (){
++this->index;
return *this;
}

bool
operator == (
  sqlite_iterator_output const & _rhs
) const {
  if (_rhs.stmt == nullptr && this->stmt == nullptr)
  return true;

  else if (_rhs.stmt == nullptr)
  return this->stmt->is_done();

  else if (this->stmt == nullptr)
  return _rhs.stmt->is_done();

return (this->stmt->is_done() && _rhs.stmt->is_done());
}

bool
operator != (
  sqlite_iterator_output const & _rhs
) const {
return !(*this == _rhs);
}

sqlite_iterator_output &
operator * (){
return *this;
}

sqlite_iterator_output *
operator -> (){
return this;
}
}; /* sqlite iterator output */

} /* data_pattern_sqlite */
#endif
#include "sqlite_iterator.tcc"

