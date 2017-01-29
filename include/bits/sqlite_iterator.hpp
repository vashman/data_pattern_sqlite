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
column <int>(sqlite_statement & _stmt, int _index){
return _stmt.column_int(_index);
}

template <>
double
column <double>(sqlite_statement & _stmt, int _index){
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

} /* bits */

template <typename T>
class sqlite_iterator_input {

public:

struct proxy {

T temp;
int index;
sqlite_statement * stmt;

proxy (
  int _index
, sqlite_statement & _stmt
)
: temp ()
, index(_index)
, stmt (& _stmt)
{}

~proxy() = default;
proxy (proxy const &) = default;
proxy (proxy &&) = default;
proxy & operator = (proxy const &) = delete;
proxy & operator = (proxy &&) = default;

operator T(){
this->temp
  = template bits::column<T>(this->stmt, this->index);
return this->temp;
}

T *
operator -> (){
return &this->temp;
}

}; /* proxy */

private:

sqlite_statement * stmt;
proxy temp;
int index;

public:

typedef std::input_iterator_tag iterator_catagory;
typedef proxy value_type;
typedef std::size_t difference_type;
typedef proxy * pointer;
typedef proxy & reference;

explicit
sqlite_iterator_input (sqlite_statement & _stmt);
sqlite_iterator_input ();
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
return temp_iter;
}

sqlite_iterator_input &
operator ++ (){
++this->index;
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

proxy &
operator * (){
return this->temp;
}

proxy *
operator -> (){
return &this->temp;
}
}; /* sqlite iterator output */

template <typename T>
class sqlite_iterator_output {

sqlite_statement * stmt;
proxy temp;
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
sqlite_iterator_output (sqlite_iterator_output const &) = default;
sqlite_iterator_output (sqlite_iterator_output &&) = default;

sqlite_iterator_output &
operator = (sqlite_iterator_output const &) = default;

sqlite_iterator_output &
operator = (sqlite_iterator_output &&) = default;

sqlite_iterator_output &
operator = (
  T const & _var
){
this->stmt->bind(this->index, _var);
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

  else if (this->stmt == nullptr) return _rhs.is_done();

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
#include "sqlite_iterator_input.tcc"

